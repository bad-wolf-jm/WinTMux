#include "UI.h"

#include <fmt/printf.h>
#include <memory>

UI::UI()
{
    // _workspaces.push_back( std::make_shared<Workspace>( "DEFAULT" ) );
    // _workspaces.push_back( std::make_shared<Workspace>( "WinTMux Source Code" ) );
    // _workspaces.push_back( std::make_shared<Workspace>( "LaTex" ) );
    // _workspaces.push_back( std::make_shared<Workspace>( "SpockEngine" ) );

    // _currentWorkspace = 0;
    // _bgTerminal = std::make_shared<Terminal>("nvim", _framebuffer.Columns(), _framebuffer.Rows());
}

void UI::Start()
{
    _bgTerminal = std::make_shared<PTYProcess>( "py \"C:\\GitLab\\WinTMux\\Scripts\\test_terminal.py\"", _bgTerminalBuffer );
    _fgTerminal = std::make_shared<PTYProcess>( "powershell", _fgTerminalBuffer );
    // _bgTerminal = std::make_shared<PTYProcess>( "nvim", _bgTerminalBuffer );
    //_bgTerminal = std::make_shared<PTYProcess>( "python -m rich", _bgTerminalBuffer );
    _bgTerminalBuffer.BeginFrame();
    _fgTerminalBuffer.BeginFrame();
}

void UI::Stop()
{
    _bgTerminal->WaitForCompletion( 1 );
}

void UI::Resize( uint32_t columns, uint32_t rows )
{
    _framebuffer.Resize( rows, columns );
    _bgTerminalBuffer.Resize( rows, columns );

    _fgTerminalWidth  = static_cast<int32_t>( _framebuffer.Columns() * 0.75f );
    _fgTerminalHeight = static_cast<int32_t>( _framebuffer.Rows() * 0.95f );

    int32_t remainingWidth = _framebuffer.Columns() - _fgTerminalWidth;
    if( ( remainingWidth % 2 ) != 0 )
        _fgTerminalWidth++;

    int32_t remainingHeight = _framebuffer.Rows() - _fgTerminalHeight;
    if( ( remainingHeight % 2 ) != 0 )
        _fgTerminalHeight++;

    // Reduce the size of the terminal framebuffer to allow space for the frame
    _fgTerminalBuffer.Resize( _fgTerminalHeight - 2, _fgTerminalWidth - 2 );
}

framebuffer_t &UI::FrameBuffer()
{
    return _framebuffer;
}

// void UI::ExecuteCurrentCommand()
// {
//     // if( _commandLine->_currentCommand == ":workspaces" )
//     // {
//     //     _displayedOverlay = eOverlayType::WORKSPACE_SELECTOR;
//     //     return;
//     // }

//     // if( _commandLine->_currentCommand == ":terminals" )
//     // {
//     //     _terminalSelectorOverlay->SetWorkspace( _workspaces[_currentWorkspace] );
//     //     _displayedOverlay = eOverlayType::TERMINAL_SELECTOR;
//     //     return;
//     // }
// }

// Workspace &UI::CurrentWorkspace()
// {
//     return *_workspaces[_currentWorkspace];
// }

void UI::OnKeyPress( keycode_t const &keyCode, uint32_t modifiers )
{
    if( _displayTerminal && keyCode.KeyCode == keycode::ESCAPE )
    {
        _displayTerminal = false;
        return;
    }

    if( !_displayTerminal && ( keyCode.KeyCode == keycode::GRAVE_ACCENT ) && ( modifiers & ( 1 << (uint32_t)modifiers::CTRL ) ) )
    {
        _displayTerminal = true;
        return;
    }
    // // Dismiss the overlay on pressing ENTER, if any
    // if( _displayedOverlay != eOverlayType::NONE && keyCode.KeyCode == keycode::ENTER )
    // {
    //     _displayedOverlay = eOverlayType::NONE;

    //     return;
    // }

    // // If there is an overlay present, the key press event is sent to it, and we can return immediately,
    // // Otherwise, the action to take is determined by the current mode we are in.
    // switch( _displayedOverlay )
    // {
    // case eOverlayType::TERMINAL_SELECTOR:
    // {
    //     // _terminalSelectorOverlay->OnKeyPress( keyCode, modifiers );
    //     // CurrentWorkspace().FocusTerminal( _terminalSelectorOverlay->SelectedIndex() );
    //     return;
    // }
    // case eOverlayType::WORKSPACE_SELECTOR:
    // {
    //     // _workspaceSelectorOverlay->OnKeyPress( keyCode, modifiers );
    //     // _currentWorkspace = _workspaceSelectorOverlay->SelectedIndex();

    //     return;
    // }
    // case eOverlayType::NONE:
    // default:
    //     break;
    // }

    // if( !_commandInputMode )
    // {
    //     // Determine whether we should enter command input mode. If so, set the command prompt and return.
    //     // Future key presses will be redirected to the command prompt.
    //     if( ( keyCode.KeyCode == keycode::SEMICOLON ) && ( modifiers & ( 1 << static_cast<uint32_t>( modifiers::SHIFT ) ) ) )
    //     {
    //         Mode = eInputMode::Command;

    //         _commandInputMode = true;

    //         // _commandLine->_cursorPosition = 0;
    //         // _commandLine->_currentCommand = ":";

    //         return;
    //     }

    //     // Build key sequence for processing.
    // }
    // else
    // {
    //     if( keyCode.KeyCode == keycode::ENTER )
    //     {
    //         Mode = eInputMode::Normal;

    //         _commandInputMode = false;

    //         // ExecuteCurrentCommand();

    //         // _commandLine->_cursorPosition = 0;
    //         // _commandLine->_currentCommand.resize( 0 );
    //     }
    //     else
    //     {
    //         // if key is alphanumeric of space, append to the current command
    //         // _commandLine->_currentCommand += keyCode.GetCharacter( modifiers == static_cast<uint32_t>( modifiers::SHIFT ) );
    //     }
    // }
}

void UI::Render()
{
    _bgTerminal->PipeListener();
    _fgTerminal->PipeListener();

    _framebuffer.BeginFrame();

    // Blit the main terminal framebuffer to the output buffer.
    std::copy( _bgTerminalBuffer.DataNC().begin(), _bgTerminalBuffer.DataNC().end(), _framebuffer.DataNC().begin() );

    if( _displayTerminal )
    {
        // Dim the main terminal buffer before displaying the work terminal
        // over it
        for( auto &glyph : _framebuffer.DataNC() )
        {
            uint32_t fg = static_cast<uint32_t>( ( glyph.Attributes >> 24 ) & 0xFFFFFF );
            {
                uint8_t r = ( ( fg & 0xff0000 ) >> 16 ) >> 1;
                uint8_t g = ( ( fg & 0xff00 ) >> 8 ) >> 1;
                uint8_t b = ( fg & 0xff ) >> 1;

                fg = r << 16 | g << 8 | b;
            }

            uint32_t bg = static_cast<uint32_t>( glyph.Attributes & 0xFFFFFF );
            {
                uint8_t r = ( ( bg & 0xff0000 ) >> 16 ) >> 1;
                uint8_t g = ( ( bg & 0xff00 ) >> 8 ) >> 1;
                uint8_t b = ( bg & 0xff ) >> 1;

                bg = r << 16 | g << 8 | b;
            }

            uint32_t attributes = glyph.Attributes >> 48;

            glyph.Attributes =
                static_cast<uint64_t>( attributes ) << 48 | static_cast<uint64_t>( fg ) << 24 | static_cast<uint64_t>( bg );
        }

        int32_t remainingWidth  = _framebuffer.Columns() - _fgTerminalWidth;
        int32_t remainingHeight = _framebuffer.Rows() - _fgTerminalHeight;

        int32_t fgTerminalPositionX = remainingWidth / 2;
        int32_t fgTerminalPositionY = remainingHeight / 2;

        _framebuffer.SetForeground( 200, 200, 200 );
        _framebuffer.SetBackground( 20, 20, 20 );
        _framebuffer.DrawRect( fgTerminalPositionX, fgTerminalPositionY, _fgTerminalWidth, _fgTerminalHeight, u8"\u256D", u8"\u2500",
                               u8"\u256E", u8"\u2502", u8"\u256F", u8"\u2500", u8"\u2570", u8"\u2502" );

        // Paint the foreground terminal framebuffer inside the rectangle
        for( int r = 0; r < _fgTerminalBuffer.Rows(); r++ )
        {
            for( int c = 0; c < _fgTerminalBuffer.Columns(); c++ )
            {
                int position         = r * _fgTerminalBuffer.Columns() + c;
                int positionOnScreen = ( r + fgTerminalPositionY + 1 ) * _framebuffer.Columns() + ( c + fgTerminalPositionX + 1 );

                _framebuffer.DataNC()[positionOnScreen] = _fgTerminalBuffer.DataNC()[position];
            }
        }
    }

    _framebuffer.EndFrame();
}

void UI::RenderHeader()
{
    _framebuffer.SetForeground( 200, 200, 200 );
    _framebuffer.SetBackground( 75, 75, 75 );

    // auto line = fmt::sprintf( " WORKSPACE %d (%s)", _currentWorkspace + 1, _workspaces[_currentWorkspace]->Name().c_str() );
    // _framebuffer.TextLine( 0, 0, line );

    // ImGui::SetNextWindowPos( ImVec2( 0.0f, 0.0f ) );
    // ImGui::SetNextWindowSize( ImVec2( _windowSize.x, _headerHeight ) );
    // ImGui::Begin( "##1", &_windowIsOpen,
    //               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
    // ImGuiWindowFlags_NoScrollbar
    //               );
    // {
    //     float posX = 5.0;
    //     float posY = ( _headerHeight - _fontSize ) * 0.5f;
    //     ImGui::SetCursorPos( ImVec2{ posX, posY } );
    //     ImGui::Text( "WORKSPACE %d (%s)", _currentWorkspace + 1, _workspaces[_currentWorkspace]->Name().c_str() );
    // }
    // ImGui::End();
}

// void UI::RenderWorkspace()
// {
//     if( _currentWorkspace >= 0 && _currentWorkspace < _workspaces.size() )
//     {
//         _workspaces[_currentWorkspace]->Render( _framebuffer );
//     }
// }

// void UI::RenderCommandLine()
// {
//     auto line = fmt::sprintf( " WORKSPACE %d (%s)", _currentWorkspace + 1, _workspaces[_currentWorkspace]->Name().c_str() );
//     _framebuffer.TextLine( 0, _framebuffer.Rows() - 1, line );
//     // ImGui::SetNextWindowPos( ImVec2( 0.0f, _windowSize.y - _commandLineHeight ) );
//     // ImGui::SetNextWindowSize( ImVec2( _windowSize.x, _commandLineHeight ) );
//     // ImGui::Begin( "##3", &_windowIsOpen,
//     //               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
//     ImGuiWindowFlags_NoScrollbar
//     //               );

//     // _commandLine->SetHeight( _commandLineHeight );
//     // _commandLine->Render();

//     // ImGui::End();
// }

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
    // _bgTerminal = std::make_shared<PTYProcess>( "nvim", _bgTerminalBuffer );
    //_bgTerminal = std::make_shared<PTYProcess>( "python -m rich", _bgTerminalBuffer );
    _bgTerminalBuffer.BeginFrame();
}

void UI::Stop()
{
    _bgTerminal->WaitForCompletion( 1 );
}

void UI::Resize( uint32_t columns, uint32_t rows )
{
    _framebuffer.Resize( rows, columns );
    _bgTerminalBuffer.Resize( rows, columns );
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

    _framebuffer.BeginFrame();

    // Blit the main terminal framebuffer to the output buffer.
    std::copy( _bgTerminalBuffer.DataNC().begin(), _bgTerminalBuffer.DataNC().end(), _framebuffer.DataNC().begin() );

    if( _displayTerminal )
    {
        // Dim the main terminal buffer before displaying the work terminal 
        // over it

        int32_t terminalWidth  = static_cast<int32_t>( _framebuffer.Columns() * 0.75f );
        int32_t remainingWidth = _framebuffer.Columns() - terminalWidth;
        if( ( remainingWidth % 2 ) != 0 )
        {
            terminalWidth++;
            remainingWidth--;
        }

        int32_t terminalHeight  = static_cast<int32_t>( _framebuffer.Rows() * 0.95f );
        int32_t remainingHeight = _framebuffer.Rows() - terminalHeight;
        if( ( remainingHeight % 2 ) != 0 )
        {
            terminalHeight++;
            remainingHeight--;
        }

        _framebuffer.SetForeground( 200, 200, 200 );
        _framebuffer.SetBackground( 20, 20, 20 );
        _framebuffer.DrawRect( remainingWidth / 2, remainingHeight / 2, terminalWidth, terminalHeight, u8"\u256D", u8"\u2500",
                               u8"\u256E", u8"\u2502", u8"\u256F", u8"\u2500", u8"\u2570", u8"\u2502" );
    }

    _framebuffer.EndFrame();
    // if( _displayedOverlay != eOverlayType::NONE )
    // {
    //     ImGui::SetNextWindowPos( ImVec2( 0.0f, 0.0f ) );
    //     ImGui::SetNextWindowSize( ImVec2( _windowSize.x, _windowSize.y ) );
    //     ImGui::PushStyleColor( ImGuiCol_WindowBg, IM_COL32( 0, 0, 0, 200 ) );
    //     ImGui::Begin( "##4", &_windowIsOpen,
    //                   ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
    //                       ImGuiWindowFlags_NoScrollbar );
    // }

    // switch( _displayedOverlay )
    // {
    // case eOverlayType::TERMINAL_SELECTOR:
    // {
    //     // _terminalSelectorOverlay->Render();
    //     break;
    // }
    // case eOverlayType::WORKSPACE_SELECTOR:
    // {
    //     // _workspaceSelectorOverlay->Render();
    //     break;
    // }
    // case eOverlayType::NONE:
    // default:
    //     break;
    // }

    // if( _displayedOverlay != eOverlayType::NONE )
    // {
    //     ImGui::End();
    //     ImGui::PopStyleColor();
    // }

    // ImGui::PopStyleVar();
    // ImGui::PopStyleVar();

    // ImGui::Render();
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

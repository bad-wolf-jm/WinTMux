#include "MainWindow.h"
#include <memory>

MainWindow::MainWindow()
    : _commandLine{ std::make_shared<CommandLine>( this ) }
{
    _workspaces.push_back( std::make_shared<Workspace>( "DEFAULT" ) );
    _workspaces.back()->VSplit();
    _workspaces.back()->VSplit();
    _workspaces.back()->HSplit();
    _workspaces.back()->HSplit();

    _workspaces.push_back( std::make_shared<Workspace>( "WinTMux Source Code" ) );
    _workspaces.back()->HSplit();
    _workspaces.back()->HSplit();
    _workspaces.back()->VSplit();

    _workspaces.push_back( std::make_shared<Workspace>( "LaTex" ) );
    _workspaces.back()->VSplit();

    _workspaces.push_back( std::make_shared<Workspace>( "SpockEngine" ) );
    _workspaces.back()->HSplit();
    _currentWorkspace = 0;

    _workspaceSelectorOverlay = std::make_shared<WorkspaceSelectorOverlay>( _workspaces );
    _terminalSelectorOverlay  = std::make_shared<TerminalSelectorOverlay>();
}

void MainWindow::ExecuteCurrentCommand()
{
    if( _commandLine->_currentCommand == ":workspaces" )
    {
        _displayedOverlay = eOverlayType::WORKSPACE_SELECTOR;
        return;
    }

    if( _commandLine->_currentCommand == ":terminals" )
    {
        _terminalSelectorOverlay->SetWorkspace( _workspaces[_currentWorkspace] );
        _displayedOverlay = eOverlayType::TERMINAL_SELECTOR;
        return;
    }
}

Workspace &MainWindow::CurrentWorkspace()
{
    return *_workspaces[_currentWorkspace];
}

void MainWindow::OnKeyPress( KeyCode const &keyCode, uint32_t modifiers )
{
    // Dismiss the overlay on pressing ENTER, if any
    if( _displayedOverlay != eOverlayType::NONE && keyCode.KeyCode == KeyCodes::ENTER )
    {
        _displayedOverlay = eOverlayType::NONE;

        return;
    }

    // If there is an overlay present, the key press event is sent to it, and we can return immediately,
    // Otherwise, the action to take is determined by the current mode we are in.
    switch( _displayedOverlay )
    {
    case eOverlayType::TERMINAL_SELECTOR:
    {
        _terminalSelectorOverlay->OnKeyPress( keyCode, modifiers );
        CurrentWorkspace().FocusTerminal( _terminalSelectorOverlay->SelectedIndex() );
        return;
    }
    case eOverlayType::WORKSPACE_SELECTOR:
    {
        _workspaceSelectorOverlay->OnKeyPress( keyCode, modifiers );
        _currentWorkspace = _workspaceSelectorOverlay->SelectedIndex();

        return;
    }
    case eOverlayType::NONE:
    default:
        break;
    }

    if( !_commandInputMode )
    {
        // Determine whether we should enter command input mode. If so, set the command prompt and return.
        // Future key presses will be redirected to the command prompt.
        if( ( keyCode.KeyCode == KeyCodes::SEMICOLON ) && ( modifiers & ( 1 << static_cast<uint32_t>( Modifiers::SHIFT ) ) ) )
        {
            Mode = eInputMode::Command;

            _commandInputMode = true;

            _commandLine->_cursorPosition = 0;
            _commandLine->_currentCommand = ":";

            return;
        }

        // Build key sequence for processing.
    }
    else
    {
        if( keyCode.KeyCode == KeyCodes::ENTER )
        {
            Mode = eInputMode::Normal;

            _commandInputMode = false;

            ExecuteCurrentCommand();

            _commandLine->_cursorPosition = 0;
            _commandLine->_currentCommand.resize( 0 );
        }
        else
        {
            // if key is alphanumeric of space, append to the current command
            _commandLine->_currentCommand += keyCode.GetCharacter( modifiers == static_cast<uint32_t>( Modifiers::SHIFT ) );
        }
    }
}

void MainWindow::Render()
{
    ImGui::NewFrame();

    _windowSize = ImGui::GetIO().DisplaySize;

    ImGui::PushStyleVar( ImGuiStyleVar_WindowMinSize, ImVec2( _fontSize, _fontSize ) );
    ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0, 0 ) );

    RenderHeader();
    RenderWorkspace();
    RenderCommandLine();

    if( _displayedOverlay != eOverlayType::NONE )
    {
        ImGui::SetNextWindowPos( ImVec2( 0.0f, 0.0f ) );
        ImGui::SetNextWindowSize( ImVec2( _windowSize.x, _windowSize.y ) );
        ImGui::PushStyleColor( ImGuiCol_WindowBg, IM_COL32( 0, 0, 0, 200 ) );
        ImGui::Begin( "##4", &_windowIsOpen,
                      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                          ImGuiWindowFlags_NoScrollbar );
    }

    switch( _displayedOverlay )
    {
    case eOverlayType::TERMINAL_SELECTOR:
    {
        _terminalSelectorOverlay->Render();
        break;
    }
    case eOverlayType::WORKSPACE_SELECTOR:
    {
        _workspaceSelectorOverlay->Render();
        break;
    }
    case eOverlayType::NONE:
    default:
        break;
    }

    if( _displayedOverlay != eOverlayType::NONE )
    {
        ImGui::End();
        ImGui::PopStyleColor();
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleVar();

    ImGui::Render();
}

void MainWindow::RenderHeader()
{
    ImGui::SetNextWindowPos( ImVec2( 0.0f, 0.0f ) );
    ImGui::SetNextWindowSize( ImVec2( _windowSize.x, _headerHeight ) );
    ImGui::Begin( "##1", &_windowIsOpen,
                  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar );
    {
        float posX = 5.0;
        float posY = ( _headerHeight - _fontSize ) * 0.5f;
        ImGui::SetCursorPos( ImVec2{ posX, posY } );
        ImGui::Text( "WORKSPACE %d (%s)", _currentWorkspace + 1, _workspaces[_currentWorkspace]->Name().c_str() );
    }
    ImGui::End();
}

void MainWindow::RenderWorkspace()
{
    if( _currentWorkspace >= 0 && _currentWorkspace < _workspaces.size() )
    {
        ImGui::SetNextWindowPos( ImVec2( 0.0f, _headerHeight ) );
        ImGui::SetNextWindowSize( ImVec2( _windowSize.x, _windowSize.y - _headerHeight - _commandLineHeight ) );
        ImGui::Begin( "##2", &_windowIsOpen,
                      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                          ImGuiWindowFlags_NoScrollbar );
        _workspaces[_currentWorkspace]->Render();
        ImGui::End();
    }
}

void MainWindow::RenderCommandLine()
{
    ImGui::SetNextWindowPos( ImVec2( 0.0f, _windowSize.y - _commandLineHeight ) );
    ImGui::SetNextWindowSize( ImVec2( _windowSize.x, _commandLineHeight ) );
    ImGui::Begin( "##3", &_windowIsOpen,
                  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar );

    _commandLine->SetHeight( _commandLineHeight );
    _commandLine->Render();

    ImGui::End();
}

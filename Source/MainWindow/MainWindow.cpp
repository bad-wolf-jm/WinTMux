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
}

void MainWindow::ExecuteCurrentCommand()
{
}

Workspace &MainWindow::CurrentWorkspace()
{
    return *_workspaces[_currentWorkspace];
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

    //_workspaceSelector->SetWorkspaceList( _workspaces );
    //_terminalSelector->SetTerminalList( _workspaces[_currentWorkspace]->GetConnectedTerminals() );

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
        TerminalSelectorOverlay _overlay( CurrentWorkspace() );
        _overlay.Render();
        break;
    }
    case eOverlayType::WORKSPACE_SELECTOR:
    {
        WorkspaceSelectorOverlay _overlay( _workspaces );
        _overlay.Render();
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

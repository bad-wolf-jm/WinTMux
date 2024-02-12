#include "MainWindow.h"

MainWindow::MainWindow()
    : _commandLine{ CommandLine( this ) }
{
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
        ImGui::Text( "THIS WILL BE THE TITLE" );
    }
    ImGui::End();
}

void MainWindow::RenderWorkspace()
{
}

void MainWindow::RenderCommandLine()
{
    ImGui::SetNextWindowPos( ImVec2( 0.0f, _windowSize.y - _commandLineHeight ) );
    ImGui::SetNextWindowSize( ImVec2( _windowSize.x, _commandLineHeight ) );
    ImGui::Begin( "##2", &_windowIsOpen,
                  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar );

    _commandLine.SetHeight( _commandLineHeight );
    _commandLine.Render();
    
    ImGui::End();
}

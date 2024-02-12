#include "CommandLine.h"
#include "MainWindow.h"
#include "ImGui.h"

CommandLine::CommandLine( MainWindow *parent )
    : _window{ parent }
{
}

void CommandLine::Render()
{
    float posX = 5.0;
    float posY = ( _height - _window->FontSize() ) * 0.5f;
    ImGui::SetCursorPos( ImVec2{ posX, posY } );
    ImGui::TextUnformatted( _currentCommand.c_str() );
}

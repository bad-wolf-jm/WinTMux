#include "CommandLine.h"
#include "Core/Modes.h"
#include "ImGui.h"
#include "MainWindow.h"

CommandLine::CommandLine( MainWindow *parent )
    : _window{ parent }
{
}

void CommandLine::Render()
{
    float posX = 5.0;
    float posY = ( _height - _window->FontSize() ) * 0.5f;
    ImGui::SetCursorPos( ImVec2{ posX, posY } );

    switch( _window->Mode )
    {
    case eInputMode::Normal:
        ImGui::TextUnformatted("-- NORMAL--");
        break;
    case eInputMode::Insert:
        ImGui::TextUnformatted("-- INSERT --");
        break;
    case eInputMode::Visual:
        ImGui::TextUnformatted("-- VISUAL --");
        break;
    case eInputMode::VisualLine:
        ImGui::TextUnformatted("-- VISUAL LINE --");
        break;
    case eInputMode::VisualBlock:
        ImGui::TextUnformatted("-- VISUAL BLOCK --");
        break;
    case eInputMode::Command:
        ImGui::TextUnformatted( _currentCommand.c_str() );
        break;
    }
}

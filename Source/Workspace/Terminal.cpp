#include "Terminal.h"
#include "imgui.h"
#include "imgui_internal.h"

void Terminal::Render()
{
    auto  *drawList    = ImGui::GetWindowDrawList();
    ImVec2 topLeft     = ImGui::GetCursorScreenPos();
    ImVec2 windowSize  = ImGui::GetWindowSize();
    ImVec2 bottomRight = ImVec2{ topLeft.x + windowSize.x, topLeft.y + windowSize.y };
    drawList->AddRect( topLeft, bottomRight, ImColor( 255, 255, 255, 50 ) );

    ImGui::SetCursorPos( ImVec2{ 5.0f, 5.0f } );
    ImGui::Text( "FOOBAR" );
    ImGui::Text( "%f x %f", windowSize.x, windowSize.y );
}

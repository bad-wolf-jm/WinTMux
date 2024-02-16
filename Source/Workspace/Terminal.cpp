#include "Terminal.h"
#include "imgui.h"
#include "imgui_internal.h"

void Terminal::Render()
{
    auto  *drawList             = ImGui::GetWindowDrawList();
    ImVec2 cursorScreenPosition = ImGui::GetCursorScreenPos();

    ImGui::SetCursorPos( ImVec2{ 5.0f, 5.0f } );
    ImGui::Text( "FOOBAR" );

    ImVec2 topLeft     = cursorScreenPosition;
    ImVec2 size        = ImGui::GetWindowSize();
    ImVec2 bottomRight = ImVec2{ topLeft.x + size.x, topLeft.y + size.y };
    drawList->AddRect( topLeft, bottomRight, ImColor( 255, 0, 0, 255 ) );
}

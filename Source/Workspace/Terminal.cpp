#include "Terminal.h"
#include "imgui.h"

void Terminal::Render()
{
    ImGui::SetCursorPos(ImVec2{5.0f, 5.0f});
    ImGui::Text( "FOOBAR" );
}

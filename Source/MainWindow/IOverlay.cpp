#include "IOverlay.h"
#include "imgui.h"
#include <iostream>
#include <ostream>

void IOverlay::Render()
{
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    auto  *drawList   = ImGui::GetWindowDrawList();

    ImVec2 topLeft{(windowSize.x - _frameWidth) * 0.5f, (windowSize.y - _frameHeight) * 0.5f};
    ImVec2 bottomRight{ topLeft.x + _frameWidth, topLeft.y + _frameHeight };

    drawList->AddRectFilled( topLeft, bottomRight, IM_COL32( 255, 0, 0, 255 ) );
    std::cout << "W=" << windowSize.x << " H=" << windowSize.y << std::endl;
}

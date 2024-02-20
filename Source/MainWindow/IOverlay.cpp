#include "IOverlay.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <iostream>
#include <ostream>

void IOverlay::Render()
{
    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    auto  *drawList   = ImGui::GetWindowDrawList();

    ImVec2 topLeft{ ( windowSize.x - _frameWidth ) * 0.5f, ( windowSize.y - _frameHeight ) * 0.5f };
    ImVec2 bottomRight{ topLeft.x + _frameWidth, topLeft.y + _frameHeight };

    auto  titleSize = ImGui::CalcTextSize( _frameTitle.c_str() );
    float titleX    = topLeft.x + ( _frameWidth - titleSize.x ) * 0.5f;
    float titleY    = topLeft.y - titleSize.y * 0.5f;

    float cornerRadius = 5.0f;
    drawList->AddRectFilled( topLeft, bottomRight, IM_COL32( 0, 0, 0, 255 ), cornerRadius );
    drawList->AddRect( topLeft, bottomRight, IM_COL32( 255, 255, 255, 255 ), cornerRadius );
    drawList->AddRectFilled( ImVec2{ titleX - 5.0f, titleY }, ImVec2{ titleX + titleSize.x + 5.0f, titleY + titleSize.y }, IM_COL32( 0, 0, 0, 255 ),
                             cornerRadius );
    ImGui::SetCursorPos( ImVec2{ titleX, titleY } );
    ImGui::TextUnformatted( _frameTitle.c_str() );
}

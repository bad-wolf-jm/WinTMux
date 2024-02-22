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

    ImVec2  titleSize = ImGui::CalcTextSize( _frameTitle.c_str() );
    float titleX    = topLeft.x + ( _frameWidth - titleSize.x ) * 0.5f;
    float titleY    = topLeft.y - titleSize.y * 0.5f;

    float cornerRadius = 5.0f;

    // A rectangle for the list
    drawList->AddRectFilled( topLeft, bottomRight, IM_COL32( 0, 0, 0, 255 ), cornerRadius );

    // The border for the list
    drawList->AddRect( topLeft, bottomRight, IM_COL32( 255, 255, 255, 255 ), cornerRadius );

    // Hide part of the line in order to display the title of the overlay
    drawList->AddRectFilled( ImVec2{ titleX - 5.0f, titleY }, ImVec2{ titleX + titleSize.x + 5.0f, titleY + titleSize.y },
                             IM_COL32( 0, 0, 0, 255 ), cornerRadius );

    // Display the title of the overlay, centered on the top edge
    ImGui::SetCursorPos( ImVec2{ titleX, titleY } );
    ImGui::TextUnformatted( _frameTitle.c_str() );

    // Render the contents of the overlay in a child window
    ImGui::SetCursorPos(ImVec2{topLeft.x + 10.0f, topLeft.y + 15.0f});
    ImGui::BeginChild( "child", ImVec2{_frameWidth - 15.0f, _frameHeight - 20.0f}, ImGuiChildFlags_None );
    RenderOverlayContent();
    ImGui::EndChild();
}

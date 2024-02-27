#include "Workspace.h"
#include <memory>

Workspace::Workspace( string_t name )
    : _name{ name }
{
    _terminals.push_back( std::make_shared<Terminal>() );
    _terminalTree = std::make_shared<Tree>( _terminals.back() );

    _terminals.back()->IsFocused = true;
}

void Workspace::VSplit()
{
    _terminals.push_back( std::make_shared<Terminal>() );
    _terminalTree->VSplit( _terminals.back() );
}

void Workspace::HSplit()
{
    _terminals.push_back( std::make_shared<Terminal>() );
    _terminalTree->HSplit( _terminals.back() );
}

void Workspace::Render()
{
    _terminalTree->SetSize( ImGui::GetContentRegionAvail() );
    for( auto const &terminal : _terminals )
    {
        ImGui::SetCursorPos( terminal->Position );
        ImGui::PushID( (void *)terminal.get() );
        ImGui::BeginChild( "##ChildItem", terminal->Size );
        {
            auto  *drawList    = ImGui::GetWindowDrawList();
            ImVec2 topLeft     = ImGui::GetCursorScreenPos();
            ImVec2 windowSize  = ImGui::GetWindowSize();
            ImVec2 bottomRight = ImVec2{ topLeft.x + windowSize.x, topLeft.y + windowSize.y };

            uint32_t borderColor = terminal->IsFocused ? ImColor( 255, 255, 255, 150 ) : ImColor( 255, 255, 255, 50 );
            drawList->AddRect( topLeft, bottomRight, borderColor );

            ImGui::SetCursorPos( ImVec2{ 5.0f, 5.0f } );
            ImGui::Text( "FOOBAR" );
            ImGui::Text( "%f x %f", windowSize.x, windowSize.y );

            if( !terminal->IsFocused )
            {
                ImVec2 overlayTopLeft     = ImVec2{ topLeft.x + 1, topLeft.y + 1 };
                ImVec2 overlayBottomRight = ImVec2{ bottomRight.x - 1, bottomRight.y - 1 };

                drawList->AddRectFilled( overlayTopLeft, overlayBottomRight, IM_COL32( 0, 0, 0, 200 ) );
            }
            else
            {
                ImVec2   overlayTopLeft     = ImVec2{ topLeft.x + 1, topLeft.y + 1 };
                ImVec2   overlayBottomRight = ImVec2{ bottomRight.x - 1, bottomRight.y - 1 };
                uint32_t borderColor        = ImColor( 255, 55, 255, 200 );

                drawList->AddRect( overlayTopLeft, overlayBottomRight, borderColor );
            }
        }
        ImGui::EndChild();
        ImGui::PopID();
    }
}

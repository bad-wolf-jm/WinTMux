#include "WorkspaceSelectorOverlay.h"

WorkspaceSelectorOverlay::WorkspaceSelectorOverlay( std::vector<std::shared_ptr<Workspace>> &workspaces )
    : _workspaces{ workspaces }
{
    _frameTitle = "WORKSPACES";
}

void WorkspaceSelectorOverlay::RenderOverlayContent()
{
    //Render();
    for( auto const &ws : _workspaces )
    {
       // ImGui::SetCursorPos(ImVec2{})
        ImGui::Text( "%s", ws->Name().c_str() );
    }
}

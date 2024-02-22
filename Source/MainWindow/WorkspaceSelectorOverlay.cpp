#include "WorkspaceSelectorOverlay.h"

WorkspaceSelectorOverlay::WorkspaceSelectorOverlay( std::vector<std::shared_ptr<Workspace>> &workspaces )
    : _workspaces{ workspaces }
{
    _frameTitle = "WORKSPACES";
}

void WorkspaceSelectorOverlay::RenderOverlayContent()
{
    if( _workspaces.size() == 0 )
        return;

    for( auto const &ws : _workspaces )
        ImGui::Text( "%s", ws->Name().c_str() );
}

void WorkspaceSelectorOverlay::OnKeyPress( KeyCode const &keyCode )
{
}

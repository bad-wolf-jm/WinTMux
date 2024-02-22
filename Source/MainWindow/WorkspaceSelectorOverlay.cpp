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

void WorkspaceSelectorOverlay::SetWorkspaceList( std::vector<std::shared_ptr<Workspace>> &workspaces )
{
    _workspaces = workspaces;
}

void WorkspaceSelectorOverlay::OnKeyPress( KeyCode const &keyCode, uint32_t modifiers )
{
    switch( keyCode.KeyCode )
    {
    case KeyCodes::UP:
        _currentSelection -= 1;
        _currentSelection = std::min( _currentSelection, 0 );
        break;
    case KeyCodes::DOWN:
        _currentSelection += 1;
        _currentSelection = std::max( _currentSelection, static_cast<int32_t>( _workspaces.size() - 1 ) );
        break;
    case KeyCodes::ENTER:
        break;
    default:
        break;
    }
}

#include "WorkspaceSelectorOverlay.h"

WorkspaceSelectorOverlay::WorkspaceSelectorOverlay( std::vector<std::shared_ptr<Workspace>> &workspaces )
    : _workspaces{ workspaces }
{
    _frameTitle = "WORKSPACES";
}

int32_t WorkspaceSelectorOverlay::SelectedIndex()
{
    return _currentSelection;
}

void WorkspaceSelectorOverlay::RenderOverlayContent()
{
    if( _workspaces.size() == 0 )
        return;

    for( int i = 0; i < _workspaces.size(); i++ )
    {
        auto const &ws       = _workspaces[i];
        ImVec2      textSize = ImGui::CalcTextSize( ws->Name().c_str() );

        if( i == _currentSelection )
            ImGui::PushStyleColor( ImGuiCol_Text, ImVec4{ 1.0, 1.0, 1.0, 1.0 } );
        else
            ImGui::PushStyleColor( ImGuiCol_Text, ImVec4{ 1.0, 1.0, 1.0, .5 } );
        ImGui::Text( "%s", ws->Name().c_str() );
        ImGui::PopStyleColor();
    }
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
        _currentSelection = std::max( _currentSelection, 0 );
        break;
    case KeyCodes::DOWN:
        _currentSelection += 1;
        _currentSelection = std::min( _currentSelection, static_cast<int32_t>( _workspaces.size() - 1 ) );
        break;
    case KeyCodes::ENTER:
        break;
    default:
        break;
    }
}

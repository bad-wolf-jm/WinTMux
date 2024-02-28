#include "TerminalSelectorOverlay.h"

TerminalSelectorOverlay::TerminalSelectorOverlay()
{
    _frameTitle = "TERMINALS";
}

void TerminalSelectorOverlay::SetWorkspace( std::shared_ptr<Workspace> workspace )
{
    _workspace = workspace;
}

int32_t TerminalSelectorOverlay::SelectedIndex()
{
    return _currentSelection;
}

void TerminalSelectorOverlay::RenderOverlayContent()
{
    if( _workspace == nullptr )
        return;

    if( _workspace->Terminals().size() == 0 )
        return;

    for( int i = 0; i < _workspace->Terminals().size(); i++ )
    {
        auto const &ws       = _workspace->Terminals()[i];
        ImVec2      textSize = ImGui::CalcTextSize( ws->Name().c_str() );

        if( i == _currentSelection )
            ImGui::PushStyleColor( ImGuiCol_Text, ImVec4{ 1.0, 1.0, 1.0, 1.0 } );
        else
            ImGui::PushStyleColor( ImGuiCol_Text, ImVec4{ 1.0, 1.0, 1.0, .5 } );
        ImGui::Text( "%s", ws->Name().c_str() );
        ImGui::PopStyleColor();
    }
}

void TerminalSelectorOverlay::OnKeyPress( KeyCode const &keyCode, uint32_t modifiers )
{
    switch( keyCode.KeyCode )
    {
    case KeyCodes::UP:
        _currentSelection -= 1;
        _currentSelection = std::max( _currentSelection, 0 );
        break;
    case KeyCodes::DOWN:
        _currentSelection += 1;
        _currentSelection = std::min( _currentSelection, static_cast<int32_t>( _workspace->Terminals().size() - 1 ) );
        break;
    case KeyCodes::ENTER:
        break;
    default:
        break;
    }
}

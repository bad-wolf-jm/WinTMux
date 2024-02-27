#include "TerminalSelectorOverlay.h"

TerminalSelectorOverlay::TerminalSelectorOverlay()
{
    _frameTitle = "TERMINALS";
}

void TerminalSelectorOverlay::SetWorkspace( std::shared_ptr<Workspace> workspace )
{
    _workspace = workspace;
}

void TerminalSelectorOverlay::RenderOverlayContent()
{
    if (_workspace == nullptr)
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
}

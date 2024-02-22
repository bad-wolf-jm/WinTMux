#include "TerminalSelectorOverlay.h"

// TerminalSelectorOverlay::TerminalSelectorOverlay( Workspace &workspace )
//     : _workspace{ workspace }
//{
//     _frameTitle = "TERMINALS";
// }

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
    //    IOverlay::Render();
}

void TerminalSelectorOverlay::OnKeyPress( KeyCode const &keyCode, uint32_t modifiers )
{
}

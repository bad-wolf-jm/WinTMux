#include "TerminalSelectorOverlay.h"

TerminalSelectorOverlay::TerminalSelectorOverlay( Workspace &workspace )
    : _workspace{ workspace }
{
    _frameTitle = "TERMINALS";
}

void TerminalSelectorOverlay::Render()
{
    IOverlay::Render();
}

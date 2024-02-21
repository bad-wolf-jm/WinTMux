#include "WorkspaceSelectorOverlay.h"

WorkspaceSelectorOverlay::WorkspaceSelectorOverlay( std::vector<std::shared_ptr<Workspace>> &workspaces )
    : _workspaces{ workspaces }
{
    _frameTitle = "WORKSPACES";
}

void WorkspaceSelectorOverlay::Render()
{
    IOverlay::Render();
}

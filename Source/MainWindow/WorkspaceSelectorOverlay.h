#pragma once

#include "MainWindow/IOverlay.h"
#include "Workspace/Workspace.h"
#include <vector>

class WorkspaceSelectorOverlay : public IOverlay
{
  public:
    WorkspaceSelectorOverlay( std::vector<std::shared_ptr<Workspace>> &workspaces );

  public:
    virtual void OnKeyPress(){};
    virtual void RenderOverlayContent();

  private:
    std::vector<std::shared_ptr<Workspace>> &_workspaces;
};

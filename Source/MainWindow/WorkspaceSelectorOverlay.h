#pragma once

#include "MainWindow/IOverlay.h"
#include "Workspace/Workspace.h"

class WorkspaceSelectorOverlay : public IOverlay
{
  public:
    WorkspaceSelectorOverlay();

  public:
    virtual void OnKeyPress(){};
    virtual void Render();
};

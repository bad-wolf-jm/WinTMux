#pragma once

#include "MainWindow/IOverlay.h"
#include "Workspace/Workspace.h"

class TerminalSelectorOverlay : public IOverlay
{
  public:
    TerminalSelectorOverlay( Workspace &workspace );

  public:
    virtual void OnKeyPress(){};
    virtual void Render();

  private:
    Workspace &_workspace;
};

#pragma once

#include "MainWindow/IOverlay.h"
#include "Workspace/Workspace.h"

class TerminalSelectorOverlay : public IOverlay
{
  public:
    TerminalSelectorOverlay();

    void SetWorkspace( std::shared_ptr<Workspace> workspace );

  public:
    virtual void OnKeyPress( KeyCode const &keyCode, uint32_t modifiers );
    virtual void RenderOverlayContent();
    int32_t      SelectedIndex();

  private:
    int                        _currentSelection = 0;
    std::shared_ptr<Workspace> _workspace;
};

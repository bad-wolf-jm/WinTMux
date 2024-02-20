#pragma once

#include "MainWindow/IOverlay.h"

class WorkspaceSelectorOverlay : public IOverlay
{
  public:
    virtual void OnKeyPress() {};
    virtual void Render();
};

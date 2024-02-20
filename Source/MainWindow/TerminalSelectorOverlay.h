#pragma once

#include "MainWindow/IOverlay.h"

class TerminalSelectorOverlay : public IOverlay
{
  public:
    virtual void OnKeyPress() {};
    virtual void Render() {};
}; 

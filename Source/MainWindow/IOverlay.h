#pragma once

#include "Core/KeyCodes.h"
#include "Core/String.h"

class IOverlay
{
  public:
    virtual void OnKeyPress(KeyCode const &keyCode, uint32_t modifiers) = 0;

    void Render();
    virtual void RenderOverlayContent() = 0;

  protected:
    float _frameWidth  = 600.0f;
    float _frameHeight = 800.0f;

    string_t _frameTitle = "FRAME TITLE";
};

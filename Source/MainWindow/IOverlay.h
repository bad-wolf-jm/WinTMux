#pragma once

#include "Core/String.h"
class IOverlay
{
  public:
    virtual void OnKeyPress() = 0;
    virtual void Render();

  protected:
    float _frameWidth  = 600.0f;
    float _frameHeight = 800.0f;

    string_t _frameTitle = "FRAME TITLE";
};

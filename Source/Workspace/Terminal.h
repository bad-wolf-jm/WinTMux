#pragma once

#include "PseudoConsole/PTYProcess.h"

class Terminal
{
  public:
    Terminal();

    bool IsFocused = true;

  public:
    void Render();

  private:
    std::shared_ptr<PTYProcess> _process = nullptr;
};

#pragma once

class Terminal
{
  public:
    Terminal() = default;

    bool IsFocused = false;

  public:
    void Render();
};

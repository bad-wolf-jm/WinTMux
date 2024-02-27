#pragma once
#include "imgui.h"

class Terminal
{
  public:
    Terminal() = default;

    bool   IsFocused = false;
    ImVec2 Position{};
    ImVec2 Size{};
};

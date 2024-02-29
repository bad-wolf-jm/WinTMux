#pragma once
#include "Core/String.h"
#include "imgui.h"


class Terminal
{
  public:
    Terminal();

  public:
    void      Render();
    string_t &Name();

  public:
    // bool   IsFocused = false;
    ImVec2 Position{};
    ImVec2 Size{};

  private:
    string_t _name = "command.exe";

    //std::shared_ptr<PTYProcess> _process = nullptr;
};

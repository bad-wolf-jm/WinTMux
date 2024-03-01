#pragma once
#include "Core/String.h"
#include "imgui.h"

#include <cstdint>

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
    uint32_t _columns = 0;
    uint32_t _rows    = 0;
};

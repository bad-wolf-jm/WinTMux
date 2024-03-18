#pragma once

#include "Core/KeyCodes.h"
#include "Core/String.h"

// #include "imgui.h"

enum class ShortcutAction
{
    PASTE
};

// struct Shortcut
// {
//     keycode       keysym;
//     modifiers      mask;
//     ShortcutAction action;
//     int            appkey;
//     int            appcursor;
// };

// struct ImGuiKeyMapEntry
// {
//     ImGuiModFlags mask;
//     const char   *string;
//     int           appkey;
//     int           appcursor;
// };
// 
// struct ImGuiKeyMapShortcut
// {
//     ImGuiModFlags  mask;
//     ShortcutAction action;
//     int            appkey;
//     int            appcursor;
// };

class ControlSequences
{
  public:
    ControlSequences();

  private:
    string_t controlSequences[(size_t)keycode::COUNT][(size_t)modifiers::COUNT] = { 0 };
};


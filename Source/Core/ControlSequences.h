#pragma once

#include "Core/KeyCodes.h"
#include "Core/String.h"

#include "imgui.h"

#ifdef HEXE_USING_SDL
#    include <SDL.h>
#endif

struct Key
{
    KeyCodes      keysym;
    Modifiers     mask;
    const char_t *string;
    int           appkey;
    int           appcursor;
};
enum class ShortcutAction
{
    PASTE
};

struct Shortcut
{
    KeyCodes       keysym;
    Modifiers      mask;
    ShortcutAction action;
    int            appkey;
    int            appcursor;
};

struct ImGuiKeyMapEntry
{
    ImGuiModFlags mask;
    const char   *string;
    int           appkey;
    int           appcursor;
};

struct ImGuiKeyMapShortcut
{
    ImGuiModFlags  mask;
    ShortcutAction action;
    int            appkey;
    int            appcursor;
};

class ControlSequences
{
  public:
    ControlSequences();

  private:
    const char *controlSequences[(size_t)KeyCodes::COUNT][(size_t)Modifiers::COUNT] = { 0 };
};


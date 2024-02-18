#pragma once

// #include "Hexe/Terminal/ImGuiTerminal.h"
#include "Core/KeyCodes.h"
#include "imgui.h"
#include <unordered_map>

#ifdef HEXE_USING_SDL
#    include <SDL.h>
#endif

struct Key
{
    KeyCodes    keysym;
    Modifiers   mask;
    const char *string;
    int         appkey;
    int         appcursor;
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

    // std::unordered_map<ImGuiKey, std::vector<ry   m_keyMap;
    // std::unordered_map<ImGuiKey, std::vector<ImGuiKeyMapEntry>>    m_platformKeyMap;
    // std::unordered_map<ImGuiKey, std::vector<ImGuiKeyMapShortcut>> m_shortcuts;
};

//constexpr int MOD_ANY = 0xFFFFFFFF;

// extern ImGuiKeyMap ImGuiTerminalKeyMap;

//
// #if defined( HEXE_USING_SDL )
// static const SDL_Scancode asciiScancodeTable[] = {
//    SDL_SCANCODE_A, SDL_SCANCODE_B, SDL_SCANCODE_C,           SDL_SCANCODE_D,     SDL_SCANCODE_E,           SDL_SCANCODE_F,
//    SDL_SCANCODE_G, SDL_SCANCODE_H, SDL_SCANCODE_I,           SDL_SCANCODE_J,     SDL_SCANCODE_K,           SDL_SCANCODE_L,
//    SDL_SCANCODE_M, SDL_SCANCODE_N, SDL_SCANCODE_O,           SDL_SCANCODE_P,     SDL_SCANCODE_Q,           SDL_SCANCODE_R,
//    SDL_SCANCODE_S, SDL_SCANCODE_T, SDL_SCANCODE_U,           SDL_SCANCODE_V,     SDL_SCANCODE_W,           SDL_SCANCODE_X,
//    SDL_SCANCODE_Y, SDL_SCANCODE_Z, SDL_SCANCODE_LEFTBRACKET, SDL_SCANCODE_SLASH, SDL_SCANCODE_RIGHTBRACKET };
// #endif

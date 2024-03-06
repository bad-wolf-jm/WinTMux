
#pragma once

#include "GLFW/glfw3.h"

#include <cstdint>
enum class KeyCodes : size_t
{
    F1,              // = GLFW_KEY_F1,
    F2,              // = GLFW_KEY_F2,
    F3,              // = GLFW_KEY_F3,
    F4,              // = GLFW_KEY_F4,
    F5,              // = GLFW_KEY_F5,
    F6,              // = GLFW_KEY_F6,
    F7,              // = GLFW_KEY_F7,
    F8,              // = GLFW_KEY_F8,
    F9,              // = GLFW_KEY_F9,
    F10,             // = GLFW_KEY_F10,
    F11,             // = GLFW_KEY_F11,
    F12,             // = GLFW_KEY_F12,
    F13,             // = GLFW_KEY_F13,
    F14,             // = GLFW_KEY_F14,
    F15,             // = GLFW_KEY_F15,
    F16,             // = GLFW_KEY_F16,
    F17,             // = GLFW_KEY_F17,
    F18,             // = GLFW_KEY_F18,
    F19,             // = GLFW_KEY_F19,
    F20,             // = GLFW_KEY_F20,
    F21,             // = GLFW_KEY_F21,
    F22,             // = GLFW_KEY_F22,
    F23,             // = GLFW_KEY_F23,
    F24,             // = GLFW_KEY_F24,
    F25,             // = GLFW_KEY_F25,
    SPACE,           // = GLFW_KEY_SPACE,
    APOSTROPHE,      // = GLFW_KEY_APOSTROPHE,
    COMMA,           // = GLFW_KEY_COMMA,
    MINUS,           // = GLFW_KEY_MINUS,
    PERIOD,          // = GLFW_KEY_PERIOD,
    SLASH,           // = GLFW_KEY_SLASH,
    SEMICOLON,       // = GLFW_KEY_SEMICOLON,
    EQUAL,           // = GLFW_KEY_EQUAL,
    LEFT_BRACKET,    // = GLFW_KEY_LEFT_BRACKET,  /* [*/
    BACKSLASH,       // = GLFW_KEY_BACKSLASH,     /* \*/
    RIGHT_BRACKET,   // = GLFW_KEY_RIGHT_BRACKET, /* ]*/
    GRAVE_ACCENT,    // = GLFW_KEY_GRAVE_ACCENT,  /* `*/
    A,               // = GLFW_KEY_A,
    B,               // = GLFW_KEY_B,
    C,               // = GLFW_KEY_C,
    D,               // = GLFW_KEY_D,
    E,               // = GLFW_KEY_E,
    F,               // = GLFW_KEY_F,
    G,               // = GLFW_KEY_G,
    H,               // = GLFW_KEY_H,
    I,               // = GLFW_KEY_I,
    J,               // = GLFW_KEY_J,
    K,               // = GLFW_KEY_K,
    L,               // = GLFW_KEY_L,
    M,               // = GLFW_KEY_M,
    N,               // = GLFW_KEY_N,
    O,               // = GLFW_KEY_O,
    P,               // = GLFW_KEY_P,
    Q,               // = GLFW_KEY_Q,
    R,               // = GLFW_KEY_R,
    S,               // = GLFW_KEY_S,
    T,               // = GLFW_KEY_T,
    U,               // = GLFW_KEY_U,
    V,               // = GLFW_KEY_V,
    W,               // = GLFW_KEY_W,
    X,               // = GLFW_KEY_X,
    Y,               // = GLFW_KEY_Y,
    Z,               // = GLFW_KEY_Z,
    KEY_0,           // = GLFW_KEY_0,
    KEY_1,           // = GLFW_KEY_1,
    KEY_2,           // = GLFW_KEY_2,
    KEY_3,           // = GLFW_KEY_3,
    KEY_4,           // = GLFW_KEY_4,
    KEY_5,           // = GLFW_KEY_5,
    KEY_6,           // = GLFW_KEY_6,
    KEY_7,           // = GLFW_KEY_7,
    KEY_8,           // = GLFW_KEY_8,
    KEY_9,           // = GLFW_KEY_9,
    KEYPAD_0,        // = GLFW_KEY_KP_0,
    KEYPAD_1,        // = GLFW_KEY_KP_1,
    KEYPAD_2,        // = GLFW_KEY_KP_2,
    KEYPAD_3,        // = GLFW_KEY_KP_3,
    KEYPAD_4,        // = GLFW_KEY_KP_4,
    KEYPAD_5,        // = GLFW_KEY_KP_5,
    KEYPAD_6,        // = GLFW_KEY_KP_6,
    KEYPAD_7,        // = GLFW_KEY_KP_7,
    KEYPAD_8,        // = GLFW_KEY_KP_8,
    KEYPAD_9,        // = GLFW_KEY_KP_9,
    KEYPAD_DECIMAL,  // = GLFW_KEY_KP_DECIMAL,
    KEYPAD_DIVIDE,   // = GLFW_KEY_KP_DIVIDE,
    KEYPAD_MULTIPLY, // = GLFW_KEY_KP_MULTIPLY,
    KEYPAD_SUBTRACT, // = GLFW_KEY_KP_SUBTRACT,
    KEYPAD_ADD,      // = GLFW_KEY_KP_ADD,
    BACKSPACE,       // = GLFW_KEY_BACKSPACE,
    DELETE_K,          // = GLFW_KEY_DELETE,
    ESCAPE,          // = GLFW_KEY_ESCAPE,
    ENTER,           // = GLFW_KEY_ENTER,
    TAB,             // = GLFW_KEY_TAB,
    INSERT,          // = GLFW_KEY_INSERT,
    RIGHT,           // = GLFW_KEY_RIGHT,
    LEFT,            // = GLFW_KEY_LEFT,
    DOWN,            // = GLFW_KEY_DOWN,
    UP,              // = GLFW_KEY_UP,
    PAGE_UP,         // = GLFW_KEY_PAGE_UP,
    PAGE_DOWN,       // = GLFW_KEY_PAGE_DOWN,
    HOME,            // = GLFW_KEY_HOME,
    END,             // = GLFW_KEY_END,
    CAPS_LOCK,       // = GLFW_KEY_CAPS_LOCK,
    SCROLL_LOCK,     // = GLFW_KEY_SCROLL_LOCK,
    NUM_LOCK,        // = GLFW_KEY_NUM_LOCK,
    PRINT_SCREEN,    // = GLFW_KEY_PRINT_SCREEN,
    PAUSE,           // = GLFW_KEY_PAUSE,
    KEYPAD_ENTER,    // = GLFW_KEY_KP_ENTER,
    KEYPAD_EQUAL,    // = GLFW_KEY_KP_EQUAL,
    LEFT_SHIFT,      // = GLFW_KEY_LEFT_SHIFT,
    LEFT_CONTROL,    // = GLFW_KEY_LEFT_CONTROL,
    LEFT_ALT,        // = GLFW_KEY_LEFT_ALT,
    LEFT_SUPER,      // = GLFW_KEY_LEFT_SUPER,
    RIGHT_SHIFT,     // = GLFW_KEY_RIGHT_SHIFT,
    RIGHT_CONTROL,   // = GLFW_KEY_RIGHT_CONTROL,
    RIGHT_ALT,       // = GLFW_KEY_RIGHT_ALT,
    RIGHT_SUPER,     // = GLFW_KEY_RIGHT_SUPER,
    MENU,            // = GLFW_KEY_MENU,
    COUNT
};

enum class Modifiers : size_t
{
    NONE,           //= 0;
    SHIFT,          //= 1 << 0;
    CTRL,           //= 1 << 1;
    ALT,            //= 1 << 2;
    SUPER,          //= 1 << 3;
    ALT_SHIFT,      //= MOD_SHIFT | MOD_ALT;
    CTRL_SHIFT,     //= MOD_SHIFT | MOD_CTRL;
    CTRL_ALT,       //= MOD_ALT | MOD_CTRL;
    CTRL_ALT_SHIFT, //= MOD_CTRL | MOD_ALT | MOD_SHIFT;
    COUNT,
    ANY = COUNT
};

struct KeyCode
{
    KeyCodes KeyCode;
    char     Symbol;
    char     ShiftedSymbol;

    char GetCharacter( bool isShifted ) const;
};

class KeyboardHandler
{
  public:
    KeyboardHandler();

  public:
    bool IsPrintable( KeyCodes key );

    KeyCode const &GetKeyCode( int keycode );
    uint32_t       GetModifierState( int mods );

  private:
    KeyCode Keys[GLFW_KEY_LAST + 1];
    void    InitKeyCodes();
};

#include "KeyCodes.h"
#include "GLFW/glfw3.h"

//KeyCode Keys[GLFW_KEY_LAST];
char keycode_t::GetCharacter(bool isShifted) const
{
    return !isShifted ? Symbol : ShiftedSymbol;
}

KeyboardHandler::KeyboardHandler()
{
    InitKeyCodes();
}

keycode_t const &KeyboardHandler::GetKeyCode( int keycode )
{
    return Keys[keycode];
}

void KeyboardHandler::InitKeyCodes()
{
    int controlKeyID = 0;
    Keys[GLFW_KEY_DELETE]        = { keycode::DELETE_K, glfwGetKeyScancode( GLFW_KEY_DELETE ), '\0', '\0' };
    Keys[GLFW_KEY_ESCAPE]        = { keycode::ESCAPE, glfwGetKeyScancode( GLFW_KEY_ESCAPE ), '\0', '\0' };
    Keys[GLFW_KEY_INSERT]        = { keycode::INSERT, glfwGetKeyScancode( GLFW_KEY_INSERT ), '\0', '\0' };
    Keys[GLFW_KEY_PAGE_UP]       = { keycode::PAGE_UP, glfwGetKeyScancode( GLFW_KEY_PAGE_UP ), '\0', '\0' };
    Keys[GLFW_KEY_PAGE_DOWN]     = { keycode::PAGE_DOWN, glfwGetKeyScancode( GLFW_KEY_PAGE_DOWN ), '\0', '\0' };
    Keys[GLFW_KEY_HOME]          = { keycode::HOME, glfwGetKeyScancode( GLFW_KEY_HOME ), '\0', '\0' };
    Keys[GLFW_KEY_END]           = { keycode::END, glfwGetKeyScancode( GLFW_KEY_END ), '\0', '\0' };
    Keys[GLFW_KEY_F1]            = { keycode::F1, glfwGetKeyScancode( GLFW_KEY_F1 ), '\0', '\0' };
    Keys[GLFW_KEY_F2]            = { keycode::F2, glfwGetKeyScancode( GLFW_KEY_F2 ), '\0', '\0' };
    Keys[GLFW_KEY_F3]            = { keycode::F3, glfwGetKeyScancode( GLFW_KEY_F3 ), '\0', '\0' };
    Keys[GLFW_KEY_F4]            = { keycode::F4, glfwGetKeyScancode( GLFW_KEY_F4 ), '\0', '\0' };
    Keys[GLFW_KEY_F5]            = { keycode::F5, glfwGetKeyScancode( GLFW_KEY_F5 ), '\0', '\0' };
    Keys[GLFW_KEY_F6]            = { keycode::F6, glfwGetKeyScancode( GLFW_KEY_F6 ), '\0', '\0' };
    Keys[GLFW_KEY_F7]            = { keycode::F7, glfwGetKeyScancode( GLFW_KEY_F7 ), '\0', '\0' };
    Keys[GLFW_KEY_F8]            = { keycode::F8, glfwGetKeyScancode( GLFW_KEY_F8 ), '\0', '\0' };
    Keys[GLFW_KEY_F9]            = { keycode::F9, glfwGetKeyScancode( GLFW_KEY_F9 ), '\0', '\0' };
    Keys[GLFW_KEY_F10]           = { keycode::F10, glfwGetKeyScancode( GLFW_KEY_F10 ), '\0', '\0' };
    Keys[GLFW_KEY_F11]           = { keycode::F11, glfwGetKeyScancode( GLFW_KEY_F11 ), '\0', '\0' };
    Keys[GLFW_KEY_F12]           = { keycode::F12, glfwGetKeyScancode( GLFW_KEY_F12 ), '\0', '\0' };
    Keys[GLFW_KEY_F13]           = { keycode::F13, glfwGetKeyScancode( GLFW_KEY_F13 ), '\0', '\0' };
    Keys[GLFW_KEY_F14]           = { keycode::F14, glfwGetKeyScancode( GLFW_KEY_F14 ), '\0', '\0' };
    Keys[GLFW_KEY_F15]           = { keycode::F15, glfwGetKeyScancode( GLFW_KEY_F15 ), '\0', '\0' };
    Keys[GLFW_KEY_F16]           = { keycode::F16, glfwGetKeyScancode( GLFW_KEY_F16 ), '\0', '\0' };
    Keys[GLFW_KEY_F17]           = { keycode::F17, glfwGetKeyScancode( GLFW_KEY_F17 ), '\0', '\0' };
    Keys[GLFW_KEY_F18]           = { keycode::F18, glfwGetKeyScancode( GLFW_KEY_F18 ), '\0', '\0' };
    Keys[GLFW_KEY_F19]           = { keycode::F19, glfwGetKeyScancode( GLFW_KEY_F19 ), '\0', '\0' };
    Keys[GLFW_KEY_F20]           = { keycode::F20, glfwGetKeyScancode( GLFW_KEY_F20 ), '\0', '\0' };
    Keys[GLFW_KEY_F21]           = { keycode::F21, glfwGetKeyScancode( GLFW_KEY_F21 ), '\0', '\0' };
    Keys[GLFW_KEY_F22]           = { keycode::F22, glfwGetKeyScancode( GLFW_KEY_F22 ), '\0', '\0' };
    Keys[GLFW_KEY_F23]           = { keycode::F23, glfwGetKeyScancode( GLFW_KEY_F23 ), '\0', '\0' };
    Keys[GLFW_KEY_F24]           = { keycode::F24, glfwGetKeyScancode( GLFW_KEY_F24 ), '\0', '\0' };
    Keys[GLFW_KEY_F25]           = { keycode::F25, glfwGetKeyScancode( GLFW_KEY_F25 ), '\0', '\0' };
    Keys[GLFW_KEY_SPACE]         = { keycode::SPACE, glfwGetKeyScancode( GLFW_KEY_SPACE ), ' ', ' ' };
    Keys[GLFW_KEY_APOSTROPHE]    = { keycode::APOSTROPHE, glfwGetKeyScancode( GLFW_KEY_APOSTROPHE ), '\'', '"' };
    Keys[GLFW_KEY_COMMA]         = { keycode::COMMA, glfwGetKeyScancode( GLFW_KEY_COMMA ), ',', '<' };
    Keys[GLFW_KEY_MINUS]         = { keycode::MINUS, glfwGetKeyScancode( GLFW_KEY_MINUS ), '-', '_' };
    Keys[GLFW_KEY_PERIOD]        = { keycode::PERIOD, glfwGetKeyScancode( GLFW_KEY_PERIOD ), '.', '>' };
    Keys[GLFW_KEY_SLASH]         = { keycode::SLASH, glfwGetKeyScancode( GLFW_KEY_SLASH ), '/', '?' };
    Keys[GLFW_KEY_SEMICOLON]     = { keycode::SEMICOLON, glfwGetKeyScancode( GLFW_KEY_SEMICOLON ), ';', ':' };
    Keys[GLFW_KEY_EQUAL]         = { keycode::EQUAL, glfwGetKeyScancode( GLFW_KEY_EQUAL ), '=', '+' };
    Keys[GLFW_KEY_LEFT_BRACKET]  = { keycode::LEFT_BRACKET, glfwGetKeyScancode( GLFW_KEY_LEFT_BRACKET ), '[', '{' };
    Keys[GLFW_KEY_BACKSLASH]     = { keycode::BACKSLASH, glfwGetKeyScancode( GLFW_KEY_BACKSLASH ), '\\', '|' };
    Keys[GLFW_KEY_RIGHT_BRACKET] = { keycode::RIGHT_BRACKET, glfwGetKeyScancode( GLFW_KEY_RIGHT_BRACKET ), ']', '}' };
    Keys[GLFW_KEY_GRAVE_ACCENT]  = { keycode::GRAVE_ACCENT, glfwGetKeyScancode( GLFW_KEY_GRAVE_ACCENT ), '`', '~' };
    Keys[GLFW_KEY_A]             = { keycode::A, glfwGetKeyScancode( GLFW_KEY_A ), 'a', 'A' };
    Keys[GLFW_KEY_B]             = { keycode::B, glfwGetKeyScancode( GLFW_KEY_B ), 'b', 'B' };
    Keys[GLFW_KEY_C]             = { keycode::C, glfwGetKeyScancode( GLFW_KEY_C ), 'c', 'C' };
    Keys[GLFW_KEY_D]             = { keycode::D, glfwGetKeyScancode( GLFW_KEY_D ), 'd', 'D' };
    Keys[GLFW_KEY_E]             = { keycode::E, glfwGetKeyScancode( GLFW_KEY_E ), 'e', 'E' };
    Keys[GLFW_KEY_F]             = { keycode::F, glfwGetKeyScancode( GLFW_KEY_F ), 'f', 'F' };
    Keys[GLFW_KEY_G]             = { keycode::G, glfwGetKeyScancode( GLFW_KEY_G ), 'g', 'G' };
    Keys[GLFW_KEY_H]             = { keycode::H, glfwGetKeyScancode( GLFW_KEY_H ), 'h', 'H' };
    Keys[GLFW_KEY_I]             = { keycode::I, glfwGetKeyScancode( GLFW_KEY_I ), 'i', 'I' };
    Keys[GLFW_KEY_J]             = { keycode::J, glfwGetKeyScancode( GLFW_KEY_J ), 'j', 'J' };
    Keys[GLFW_KEY_K]             = { keycode::K, glfwGetKeyScancode( GLFW_KEY_K ), 'k', 'K' };
    Keys[GLFW_KEY_L]             = { keycode::L, glfwGetKeyScancode( GLFW_KEY_L ), 'l', 'L' };
    Keys[GLFW_KEY_M]             = { keycode::M, glfwGetKeyScancode( GLFW_KEY_M ), 'm', 'M' };
    Keys[GLFW_KEY_N]             = { keycode::N, glfwGetKeyScancode( GLFW_KEY_N ), 'n', 'N' };
    Keys[GLFW_KEY_O]             = { keycode::O, glfwGetKeyScancode( GLFW_KEY_O ), 'o', 'O' };
    Keys[GLFW_KEY_P]             = { keycode::P, glfwGetKeyScancode( GLFW_KEY_P ), 'p', 'P' };
    Keys[GLFW_KEY_Q]             = { keycode::Q, glfwGetKeyScancode( GLFW_KEY_Q ), 'q', 'Q' };
    Keys[GLFW_KEY_R]             = { keycode::R, glfwGetKeyScancode( GLFW_KEY_R ), 'r', 'R' };
    Keys[GLFW_KEY_S]             = { keycode::S, glfwGetKeyScancode( GLFW_KEY_S ), 's', 'S' };
    Keys[GLFW_KEY_T]             = { keycode::T, glfwGetKeyScancode( GLFW_KEY_T ), 't', 'T' };
    Keys[GLFW_KEY_U]             = { keycode::U, glfwGetKeyScancode( GLFW_KEY_U ), 'u', 'U' };
    Keys[GLFW_KEY_V]             = { keycode::V, glfwGetKeyScancode( GLFW_KEY_V ), 'v', 'V' };
    Keys[GLFW_KEY_W]             = { keycode::W, glfwGetKeyScancode( GLFW_KEY_W ), 'w', 'W' };
    Keys[GLFW_KEY_X]             = { keycode::X, glfwGetKeyScancode( GLFW_KEY_X ), 'x', 'X' };
    Keys[GLFW_KEY_Y]             = { keycode::Y, glfwGetKeyScancode( GLFW_KEY_Y ), 'y', 'Y' };
    Keys[GLFW_KEY_Z]             = { keycode::Z, glfwGetKeyScancode( GLFW_KEY_Z ), 'z', 'Z' };
    Keys[GLFW_KEY_0]             = { keycode::KEY_0, glfwGetKeyScancode( GLFW_KEY_0 ), '0', ')' };
    Keys[GLFW_KEY_1]             = { keycode::KEY_1, glfwGetKeyScancode( GLFW_KEY_1 ), '1', '!' };
    Keys[GLFW_KEY_2]             = { keycode::KEY_2, glfwGetKeyScancode( GLFW_KEY_2 ), '2', '@' };
    Keys[GLFW_KEY_3]             = { keycode::KEY_3, glfwGetKeyScancode( GLFW_KEY_3 ), '3', '#' };
    Keys[GLFW_KEY_4]             = { keycode::KEY_4, glfwGetKeyScancode( GLFW_KEY_4 ), '4', '$' };
    Keys[GLFW_KEY_5]             = { keycode::KEY_5, glfwGetKeyScancode( GLFW_KEY_5 ), '5', '%' };
    Keys[GLFW_KEY_6]             = { keycode::KEY_6, glfwGetKeyScancode( GLFW_KEY_6 ), '6', '^' };
    Keys[GLFW_KEY_7]             = { keycode::KEY_7, glfwGetKeyScancode( GLFW_KEY_7 ), '7', '&' };
    Keys[GLFW_KEY_8]             = { keycode::KEY_8, glfwGetKeyScancode( GLFW_KEY_8 ), '8', '*' };
    Keys[GLFW_KEY_9]             = { keycode::KEY_9, glfwGetKeyScancode( GLFW_KEY_9 ), '9', '(' };
    Keys[GLFW_KEY_KP_0]          = { keycode::KEYPAD_0, glfwGetKeyScancode( GLFW_KEY_KP_0 ), '0', '0' };
    Keys[GLFW_KEY_KP_1]          = { keycode::KEYPAD_1, glfwGetKeyScancode( GLFW_KEY_KP_1 ), '1', '1' };
    Keys[GLFW_KEY_KP_2]          = { keycode::KEYPAD_2, glfwGetKeyScancode( GLFW_KEY_KP_2 ), '2', '2' };
    Keys[GLFW_KEY_KP_3]          = { keycode::KEYPAD_3, glfwGetKeyScancode( GLFW_KEY_KP_3 ), '3', '3' };
    Keys[GLFW_KEY_KP_4]          = { keycode::KEYPAD_4, glfwGetKeyScancode( GLFW_KEY_KP_4 ), '4', '4' };
    Keys[GLFW_KEY_KP_5]          = { keycode::KEYPAD_5, glfwGetKeyScancode( GLFW_KEY_KP_5 ), '5', '5' };
    Keys[GLFW_KEY_KP_6]          = { keycode::KEYPAD_6, glfwGetKeyScancode( GLFW_KEY_KP_6 ), '6', '6' };
    Keys[GLFW_KEY_KP_7]          = { keycode::KEYPAD_7, glfwGetKeyScancode( GLFW_KEY_KP_7 ), '7', '7' };
    Keys[GLFW_KEY_KP_8]          = { keycode::KEYPAD_8, glfwGetKeyScancode( GLFW_KEY_KP_8 ), '8', '8' };
    Keys[GLFW_KEY_KP_9]          = { keycode::KEYPAD_9, glfwGetKeyScancode( GLFW_KEY_KP_9 ), '9', '9' };
    Keys[GLFW_KEY_KP_DECIMAL]    = { keycode::KEYPAD_DECIMAL, glfwGetKeyScancode( GLFW_KEY_KP_DECIMAL ), '.', '.' };
    Keys[GLFW_KEY_KP_DIVIDE]     = { keycode::KEYPAD_DIVIDE, glfwGetKeyScancode( GLFW_KEY_KP_DIVIDE ), '/', '/' };
    Keys[GLFW_KEY_KP_MULTIPLY]   = { keycode::KEYPAD_MULTIPLY, glfwGetKeyScancode( GLFW_KEY_KP_MULTIPLY ), '*', '*' };
    Keys[GLFW_KEY_KP_SUBTRACT]   = { keycode::KEYPAD_SUBTRACT, glfwGetKeyScancode( GLFW_KEY_KP_SUBTRACT ), '-', '-' };
    Keys[GLFW_KEY_KP_ADD]        = { keycode::KEYPAD_ADD, glfwGetKeyScancode( GLFW_KEY_KP_ADD ), '+', '+' };
    Keys[GLFW_KEY_KP_EQUAL]      = { keycode::KEYPAD_EQUAL, glfwGetKeyScancode( GLFW_KEY_KP_EQUAL ), '=', '=' };
    Keys[GLFW_KEY_ENTER]         = { keycode::ENTER, glfwGetKeyScancode( GLFW_KEY_ENTER ), '\n', '\0' };
    Keys[GLFW_KEY_TAB]           = { keycode::TAB, glfwGetKeyScancode( GLFW_KEY_TAB ), '\t', '\0' };
    Keys[GLFW_KEY_BACKSPACE]     = { keycode::BACKSPACE, glfwGetKeyScancode( GLFW_KEY_BACKSPACE ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT]         = { keycode::RIGHT, glfwGetKeyScancode( GLFW_KEY_RIGHT ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT]          = { keycode::LEFT, glfwGetKeyScancode( GLFW_KEY_LEFT ), '\0', '\0' };
    Keys[GLFW_KEY_DOWN]          = { keycode::DOWN, glfwGetKeyScancode( GLFW_KEY_DOWN ), '\0', '\0' };
    Keys[GLFW_KEY_UP]            = { keycode::UP, glfwGetKeyScancode( GLFW_KEY_UP ), '\0', '\0' };
    Keys[GLFW_KEY_CAPS_LOCK]     = { keycode::CAPS_LOCK, glfwGetKeyScancode( GLFW_KEY_CAPS_LOCK ), '\0', '\0' };
    Keys[GLFW_KEY_SCROLL_LOCK]   = { keycode::SCROLL_LOCK, glfwGetKeyScancode( GLFW_KEY_SCROLL_LOCK ), '\0', '\0' };
    Keys[GLFW_KEY_NUM_LOCK]      = { keycode::NUM_LOCK, glfwGetKeyScancode( GLFW_KEY_NUM_LOCK ), '\0', '\0' };
    Keys[GLFW_KEY_PRINT_SCREEN]  = { keycode::PRINT_SCREEN, glfwGetKeyScancode( GLFW_KEY_PRINT_SCREEN ), '\0', '\0' };
    Keys[GLFW_KEY_PAUSE]         = { keycode::PAUSE, glfwGetKeyScancode( GLFW_KEY_PAUSE ), '\0', '\0' };
    Keys[GLFW_KEY_KP_ENTER]      = { keycode::KEYPAD_ENTER, glfwGetKeyScancode( GLFW_KEY_KP_ENTER ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_SHIFT]    = { keycode::LEFT_SHIFT, glfwGetKeyScancode( GLFW_KEY_LEFT_SHIFT ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_CONTROL]  = { keycode::LEFT_CONTROL, glfwGetKeyScancode( GLFW_KEY_LEFT_CONTROL ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_ALT]      = { keycode::LEFT_ALT, glfwGetKeyScancode( GLFW_KEY_LEFT_ALT ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_SUPER]    = { keycode::LEFT_SUPER, glfwGetKeyScancode( GLFW_KEY_LEFT_SUPER ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_SHIFT]   = { keycode::RIGHT_SHIFT, glfwGetKeyScancode( GLFW_KEY_RIGHT_SHIFT ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_CONTROL] = { keycode::RIGHT_CONTROL, glfwGetKeyScancode( GLFW_KEY_RIGHT_CONTROL ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_ALT]     = { keycode::RIGHT_ALT, glfwGetKeyScancode( GLFW_KEY_RIGHT_ALT ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_SUPER]   = { keycode::RIGHT_SUPER, glfwGetKeyScancode( GLFW_KEY_RIGHT_SUPER ), '\0', '\0' };
    Keys[GLFW_KEY_MENU]          = { keycode::MENU, glfwGetKeyScancode( GLFW_KEY_MENU ), '\0', '\0' };
    // clang-format off
}

uint32_t KeyboardHandler::GetModifierState(int mods)
{
    uint32_t modifiers = 0;

    if(mods & GLFW_MOD_SHIFT)
        modifiers |= (1 << static_cast<uint32_t>(modifiers::SHIFT));

    if(mods & GLFW_MOD_CONTROL)
        modifiers |= (1 << static_cast<uint32_t>(modifiers::CTRL));

    if(mods & GLFW_MOD_ALT)
        modifiers |= (1 << static_cast<uint32_t>(modifiers::ALT));

    if(mods & GLFW_MOD_SUPER)
        modifiers |= (1 << static_cast<uint32_t>(modifiers::SUPER));

    return modifiers;
}

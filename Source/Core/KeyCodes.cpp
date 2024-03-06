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
    Keys[GLFW_KEY_DELETE]        = { key_codes::DELETE_K, glfwGetKeyScancode( GLFW_KEY_DELETE ), '\0', '\0' };
    Keys[GLFW_KEY_ESCAPE]        = { key_codes::ESCAPE, glfwGetKeyScancode( GLFW_KEY_ESCAPE ), '\0', '\0' };
    Keys[GLFW_KEY_INSERT]        = { key_codes::INSERT, glfwGetKeyScancode( GLFW_KEY_INSERT ), '\0', '\0' };
    Keys[GLFW_KEY_PAGE_UP]       = { key_codes::PAGE_UP, glfwGetKeyScancode( GLFW_KEY_PAGE_UP ), '\0', '\0' };
    Keys[GLFW_KEY_PAGE_DOWN]     = { key_codes::PAGE_DOWN, glfwGetKeyScancode( GLFW_KEY_PAGE_DOWN ), '\0', '\0' };
    Keys[GLFW_KEY_HOME]          = { key_codes::HOME, glfwGetKeyScancode( GLFW_KEY_HOME ), '\0', '\0' };
    Keys[GLFW_KEY_END]           = { key_codes::END, glfwGetKeyScancode( GLFW_KEY_END ), '\0', '\0' };
    Keys[GLFW_KEY_F1]            = { key_codes::F1, glfwGetKeyScancode( GLFW_KEY_F1 ), '\0', '\0' };
    Keys[GLFW_KEY_F2]            = { key_codes::F2, glfwGetKeyScancode( GLFW_KEY_F2 ), '\0', '\0' };
    Keys[GLFW_KEY_F3]            = { key_codes::F3, glfwGetKeyScancode( GLFW_KEY_F3 ), '\0', '\0' };
    Keys[GLFW_KEY_F4]            = { key_codes::F4, glfwGetKeyScancode( GLFW_KEY_F4 ), '\0', '\0' };
    Keys[GLFW_KEY_F5]            = { key_codes::F5, glfwGetKeyScancode( GLFW_KEY_F5 ), '\0', '\0' };
    Keys[GLFW_KEY_F6]            = { key_codes::F6, glfwGetKeyScancode( GLFW_KEY_F6 ), '\0', '\0' };
    Keys[GLFW_KEY_F7]            = { key_codes::F7, glfwGetKeyScancode( GLFW_KEY_F7 ), '\0', '\0' };
    Keys[GLFW_KEY_F8]            = { key_codes::F8, glfwGetKeyScancode( GLFW_KEY_F8 ), '\0', '\0' };
    Keys[GLFW_KEY_F9]            = { key_codes::F9, glfwGetKeyScancode( GLFW_KEY_F9 ), '\0', '\0' };
    Keys[GLFW_KEY_F10]           = { key_codes::F10, glfwGetKeyScancode( GLFW_KEY_F10 ), '\0', '\0' };
    Keys[GLFW_KEY_F11]           = { key_codes::F11, glfwGetKeyScancode( GLFW_KEY_F11 ), '\0', '\0' };
    Keys[GLFW_KEY_F12]           = { key_codes::F12, glfwGetKeyScancode( GLFW_KEY_F12 ), '\0', '\0' };
    Keys[GLFW_KEY_F13]           = { key_codes::F13, glfwGetKeyScancode( GLFW_KEY_F13 ), '\0', '\0' };
    Keys[GLFW_KEY_F14]           = { key_codes::F14, glfwGetKeyScancode( GLFW_KEY_F14 ), '\0', '\0' };
    Keys[GLFW_KEY_F15]           = { key_codes::F15, glfwGetKeyScancode( GLFW_KEY_F15 ), '\0', '\0' };
    Keys[GLFW_KEY_F16]           = { key_codes::F16, glfwGetKeyScancode( GLFW_KEY_F16 ), '\0', '\0' };
    Keys[GLFW_KEY_F17]           = { key_codes::F17, glfwGetKeyScancode( GLFW_KEY_F17 ), '\0', '\0' };
    Keys[GLFW_KEY_F18]           = { key_codes::F18, glfwGetKeyScancode( GLFW_KEY_F18 ), '\0', '\0' };
    Keys[GLFW_KEY_F19]           = { key_codes::F19, glfwGetKeyScancode( GLFW_KEY_F19 ), '\0', '\0' };
    Keys[GLFW_KEY_F20]           = { key_codes::F20, glfwGetKeyScancode( GLFW_KEY_F20 ), '\0', '\0' };
    Keys[GLFW_KEY_F21]           = { key_codes::F21, glfwGetKeyScancode( GLFW_KEY_F21 ), '\0', '\0' };
    Keys[GLFW_KEY_F22]           = { key_codes::F22, glfwGetKeyScancode( GLFW_KEY_F22 ), '\0', '\0' };
    Keys[GLFW_KEY_F23]           = { key_codes::F23, glfwGetKeyScancode( GLFW_KEY_F23 ), '\0', '\0' };
    Keys[GLFW_KEY_F24]           = { key_codes::F24, glfwGetKeyScancode( GLFW_KEY_F24 ), '\0', '\0' };
    Keys[GLFW_KEY_F25]           = { key_codes::F25, glfwGetKeyScancode( GLFW_KEY_F25 ), '\0', '\0' };
    Keys[GLFW_KEY_SPACE]         = { key_codes::SPACE, glfwGetKeyScancode( GLFW_KEY_SPACE ), ' ', ' ' };
    Keys[GLFW_KEY_APOSTROPHE]    = { key_codes::APOSTROPHE, glfwGetKeyScancode( GLFW_KEY_APOSTROPHE ), '\'', '"' };
    Keys[GLFW_KEY_COMMA]         = { key_codes::COMMA, glfwGetKeyScancode( GLFW_KEY_COMMA ), ',', '<' };
    Keys[GLFW_KEY_MINUS]         = { key_codes::MINUS, glfwGetKeyScancode( GLFW_KEY_MINUS ), '-', '_' };
    Keys[GLFW_KEY_PERIOD]        = { key_codes::PERIOD, glfwGetKeyScancode( GLFW_KEY_PERIOD ), '.', '>' };
    Keys[GLFW_KEY_SLASH]         = { key_codes::SLASH, glfwGetKeyScancode( GLFW_KEY_SLASH ), '/', '?' };
    Keys[GLFW_KEY_SEMICOLON]     = { key_codes::SEMICOLON, glfwGetKeyScancode( GLFW_KEY_SEMICOLON ), ';', ':' };
    Keys[GLFW_KEY_EQUAL]         = { key_codes::EQUAL, glfwGetKeyScancode( GLFW_KEY_EQUAL ), '=', '+' };
    Keys[GLFW_KEY_LEFT_BRACKET]  = { key_codes::LEFT_BRACKET, glfwGetKeyScancode( GLFW_KEY_LEFT_BRACKET ), '[', '{' };
    Keys[GLFW_KEY_BACKSLASH]     = { key_codes::BACKSLASH, glfwGetKeyScancode( GLFW_KEY_BACKSLASH ), '\\', '|' };
    Keys[GLFW_KEY_RIGHT_BRACKET] = { key_codes::RIGHT_BRACKET, glfwGetKeyScancode( GLFW_KEY_RIGHT_BRACKET ), ']', '}' };
    Keys[GLFW_KEY_GRAVE_ACCENT]  = { key_codes::GRAVE_ACCENT, glfwGetKeyScancode( GLFW_KEY_GRAVE_ACCENT ), '`', '~' };
    Keys[GLFW_KEY_A]             = { key_codes::A, glfwGetKeyScancode( GLFW_KEY_A ), 'a', 'A' };
    Keys[GLFW_KEY_B]             = { key_codes::B, glfwGetKeyScancode( GLFW_KEY_B ), 'b', 'B' };
    Keys[GLFW_KEY_C]             = { key_codes::C, glfwGetKeyScancode( GLFW_KEY_C ), 'c', 'C' };
    Keys[GLFW_KEY_D]             = { key_codes::D, glfwGetKeyScancode( GLFW_KEY_D ), 'd', 'D' };
    Keys[GLFW_KEY_E]             = { key_codes::E, glfwGetKeyScancode( GLFW_KEY_E ), 'e', 'E' };
    Keys[GLFW_KEY_F]             = { key_codes::F, glfwGetKeyScancode( GLFW_KEY_F ), 'f', 'F' };
    Keys[GLFW_KEY_G]             = { key_codes::G, glfwGetKeyScancode( GLFW_KEY_G ), 'g', 'G' };
    Keys[GLFW_KEY_H]             = { key_codes::H, glfwGetKeyScancode( GLFW_KEY_H ), 'h', 'H' };
    Keys[GLFW_KEY_I]             = { key_codes::I, glfwGetKeyScancode( GLFW_KEY_I ), 'i', 'I' };
    Keys[GLFW_KEY_J]             = { key_codes::J, glfwGetKeyScancode( GLFW_KEY_J ), 'j', 'J' };
    Keys[GLFW_KEY_K]             = { key_codes::K, glfwGetKeyScancode( GLFW_KEY_K ), 'k', 'K' };
    Keys[GLFW_KEY_L]             = { key_codes::L, glfwGetKeyScancode( GLFW_KEY_L ), 'l', 'L' };
    Keys[GLFW_KEY_M]             = { key_codes::M, glfwGetKeyScancode( GLFW_KEY_M ), 'm', 'M' };
    Keys[GLFW_KEY_N]             = { key_codes::N, glfwGetKeyScancode( GLFW_KEY_N ), 'n', 'N' };
    Keys[GLFW_KEY_O]             = { key_codes::O, glfwGetKeyScancode( GLFW_KEY_O ), 'o', 'O' };
    Keys[GLFW_KEY_P]             = { key_codes::P, glfwGetKeyScancode( GLFW_KEY_P ), 'p', 'P' };
    Keys[GLFW_KEY_Q]             = { key_codes::Q, glfwGetKeyScancode( GLFW_KEY_Q ), 'q', 'Q' };
    Keys[GLFW_KEY_R]             = { key_codes::R, glfwGetKeyScancode( GLFW_KEY_R ), 'r', 'R' };
    Keys[GLFW_KEY_S]             = { key_codes::S, glfwGetKeyScancode( GLFW_KEY_S ), 's', 'S' };
    Keys[GLFW_KEY_T]             = { key_codes::T, glfwGetKeyScancode( GLFW_KEY_T ), 't', 'T' };
    Keys[GLFW_KEY_U]             = { key_codes::U, glfwGetKeyScancode( GLFW_KEY_U ), 'u', 'U' };
    Keys[GLFW_KEY_V]             = { key_codes::V, glfwGetKeyScancode( GLFW_KEY_V ), 'v', 'V' };
    Keys[GLFW_KEY_W]             = { key_codes::W, glfwGetKeyScancode( GLFW_KEY_W ), 'w', 'W' };
    Keys[GLFW_KEY_X]             = { key_codes::X, glfwGetKeyScancode( GLFW_KEY_X ), 'x', 'X' };
    Keys[GLFW_KEY_Y]             = { key_codes::Y, glfwGetKeyScancode( GLFW_KEY_Y ), 'y', 'Y' };
    Keys[GLFW_KEY_Z]             = { key_codes::Z, glfwGetKeyScancode( GLFW_KEY_Z ), 'z', 'Z' };
    Keys[GLFW_KEY_0]             = { key_codes::KEY_0, glfwGetKeyScancode( GLFW_KEY_0 ), '0', ')' };
    Keys[GLFW_KEY_1]             = { key_codes::KEY_1, glfwGetKeyScancode( GLFW_KEY_1 ), '1', '!' };
    Keys[GLFW_KEY_2]             = { key_codes::KEY_2, glfwGetKeyScancode( GLFW_KEY_2 ), '2', '@' };
    Keys[GLFW_KEY_3]             = { key_codes::KEY_3, glfwGetKeyScancode( GLFW_KEY_3 ), '3', '#' };
    Keys[GLFW_KEY_4]             = { key_codes::KEY_4, glfwGetKeyScancode( GLFW_KEY_4 ), '4', '$' };
    Keys[GLFW_KEY_5]             = { key_codes::KEY_5, glfwGetKeyScancode( GLFW_KEY_5 ), '5', '%' };
    Keys[GLFW_KEY_6]             = { key_codes::KEY_6, glfwGetKeyScancode( GLFW_KEY_6 ), '6', '^' };
    Keys[GLFW_KEY_7]             = { key_codes::KEY_7, glfwGetKeyScancode( GLFW_KEY_7 ), '7', '&' };
    Keys[GLFW_KEY_8]             = { key_codes::KEY_8, glfwGetKeyScancode( GLFW_KEY_8 ), '8', '*' };
    Keys[GLFW_KEY_9]             = { key_codes::KEY_9, glfwGetKeyScancode( GLFW_KEY_9 ), '9', '(' };
    Keys[GLFW_KEY_KP_0]          = { key_codes::KEYPAD_0, glfwGetKeyScancode( GLFW_KEY_KP_0 ), '0', '0' };
    Keys[GLFW_KEY_KP_1]          = { key_codes::KEYPAD_1, glfwGetKeyScancode( GLFW_KEY_KP_1 ), '1', '1' };
    Keys[GLFW_KEY_KP_2]          = { key_codes::KEYPAD_2, glfwGetKeyScancode( GLFW_KEY_KP_2 ), '2', '2' };
    Keys[GLFW_KEY_KP_3]          = { key_codes::KEYPAD_3, glfwGetKeyScancode( GLFW_KEY_KP_3 ), '3', '3' };
    Keys[GLFW_KEY_KP_4]          = { key_codes::KEYPAD_4, glfwGetKeyScancode( GLFW_KEY_KP_4 ), '4', '4' };
    Keys[GLFW_KEY_KP_5]          = { key_codes::KEYPAD_5, glfwGetKeyScancode( GLFW_KEY_KP_5 ), '5', '5' };
    Keys[GLFW_KEY_KP_6]          = { key_codes::KEYPAD_6, glfwGetKeyScancode( GLFW_KEY_KP_6 ), '6', '6' };
    Keys[GLFW_KEY_KP_7]          = { key_codes::KEYPAD_7, glfwGetKeyScancode( GLFW_KEY_KP_7 ), '7', '7' };
    Keys[GLFW_KEY_KP_8]          = { key_codes::KEYPAD_8, glfwGetKeyScancode( GLFW_KEY_KP_8 ), '8', '8' };
    Keys[GLFW_KEY_KP_9]          = { key_codes::KEYPAD_9, glfwGetKeyScancode( GLFW_KEY_KP_9 ), '9', '9' };
    Keys[GLFW_KEY_KP_DECIMAL]    = { key_codes::KEYPAD_DECIMAL, glfwGetKeyScancode( GLFW_KEY_KP_DECIMAL ), '.', '.' };
    Keys[GLFW_KEY_KP_DIVIDE]     = { key_codes::KEYPAD_DIVIDE, glfwGetKeyScancode( GLFW_KEY_KP_DIVIDE ), '/', '/' };
    Keys[GLFW_KEY_KP_MULTIPLY]   = { key_codes::KEYPAD_MULTIPLY, glfwGetKeyScancode( GLFW_KEY_KP_MULTIPLY ), '*', '*' };
    Keys[GLFW_KEY_KP_SUBTRACT]   = { key_codes::KEYPAD_SUBTRACT, glfwGetKeyScancode( GLFW_KEY_KP_SUBTRACT ), '-', '-' };
    Keys[GLFW_KEY_KP_ADD]        = { key_codes::KEYPAD_ADD, glfwGetKeyScancode( GLFW_KEY_KP_ADD ), '+', '+' };
    Keys[GLFW_KEY_KP_EQUAL]      = { key_codes::KEYPAD_EQUAL, glfwGetKeyScancode( GLFW_KEY_KP_EQUAL ), '=', '=' };
    Keys[GLFW_KEY_ENTER]         = { key_codes::ENTER, glfwGetKeyScancode( GLFW_KEY_ENTER ), '\n', '\0' };
    Keys[GLFW_KEY_TAB]           = { key_codes::TAB, glfwGetKeyScancode( GLFW_KEY_TAB ), '\t', '\0' };
    Keys[GLFW_KEY_BACKSPACE]     = { key_codes::BACKSPACE, glfwGetKeyScancode( GLFW_KEY_BACKSPACE ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT]         = { key_codes::RIGHT, glfwGetKeyScancode( GLFW_KEY_RIGHT ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT]          = { key_codes::LEFT, glfwGetKeyScancode( GLFW_KEY_LEFT ), '\0', '\0' };
    Keys[GLFW_KEY_DOWN]          = { key_codes::DOWN, glfwGetKeyScancode( GLFW_KEY_DOWN ), '\0', '\0' };
    Keys[GLFW_KEY_UP]            = { key_codes::UP, glfwGetKeyScancode( GLFW_KEY_UP ), '\0', '\0' };
    Keys[GLFW_KEY_CAPS_LOCK]     = { key_codes::CAPS_LOCK, glfwGetKeyScancode( GLFW_KEY_CAPS_LOCK ), '\0', '\0' };
    Keys[GLFW_KEY_SCROLL_LOCK]   = { key_codes::SCROLL_LOCK, glfwGetKeyScancode( GLFW_KEY_SCROLL_LOCK ), '\0', '\0' };
    Keys[GLFW_KEY_NUM_LOCK]      = { key_codes::NUM_LOCK, glfwGetKeyScancode( GLFW_KEY_NUM_LOCK ), '\0', '\0' };
    Keys[GLFW_KEY_PRINT_SCREEN]  = { key_codes::PRINT_SCREEN, glfwGetKeyScancode( GLFW_KEY_PRINT_SCREEN ), '\0', '\0' };
    Keys[GLFW_KEY_PAUSE]         = { key_codes::PAUSE, glfwGetKeyScancode( GLFW_KEY_PAUSE ), '\0', '\0' };
    Keys[GLFW_KEY_KP_ENTER]      = { key_codes::KEYPAD_ENTER, glfwGetKeyScancode( GLFW_KEY_KP_ENTER ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_SHIFT]    = { key_codes::LEFT_SHIFT, glfwGetKeyScancode( GLFW_KEY_LEFT_SHIFT ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_CONTROL]  = { key_codes::LEFT_CONTROL, glfwGetKeyScancode( GLFW_KEY_LEFT_CONTROL ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_ALT]      = { key_codes::LEFT_ALT, glfwGetKeyScancode( GLFW_KEY_LEFT_ALT ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_SUPER]    = { key_codes::LEFT_SUPER, glfwGetKeyScancode( GLFW_KEY_LEFT_SUPER ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_SHIFT]   = { key_codes::RIGHT_SHIFT, glfwGetKeyScancode( GLFW_KEY_RIGHT_SHIFT ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_CONTROL] = { key_codes::RIGHT_CONTROL, glfwGetKeyScancode( GLFW_KEY_RIGHT_CONTROL ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_ALT]     = { key_codes::RIGHT_ALT, glfwGetKeyScancode( GLFW_KEY_RIGHT_ALT ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_SUPER]   = { key_codes::RIGHT_SUPER, glfwGetKeyScancode( GLFW_KEY_RIGHT_SUPER ), '\0', '\0' };
    Keys[GLFW_KEY_MENU]          = { key_codes::MENU, glfwGetKeyScancode( GLFW_KEY_MENU ), '\0', '\0' };
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

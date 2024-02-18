#include "KeyCodes.h"
#include "GLFW/glfw3.h"

//KeyCode Keys[GLFW_KEY_LAST];
char KeyCode::GetCharacter(bool isShifted) const
{
    return !isShifted ? Symbol : ShiftedSymbol;
}

KeyboardHandler::KeyboardHandler()
{
    InitKeyCodes();
}

KeyCode const &KeyboardHandler::GetKeyCode( int keycode )
{
    return Keys[keycode];
}

void KeyboardHandler::InitKeyCodes()
{
    int controlKeyID = 0;
    Keys[GLFW_KEY_DELETE]        = { KeyCodes::DELETE, glfwGetKeyScancode( GLFW_KEY_DELETE ), '\0', '\0' };
    Keys[GLFW_KEY_ESCAPE]        = { KeyCodes::ESCAPE, glfwGetKeyScancode( GLFW_KEY_ESCAPE ), '\0', '\0' };
    Keys[GLFW_KEY_INSERT]        = { KeyCodes::INSERT, glfwGetKeyScancode( GLFW_KEY_INSERT ), '\0', '\0' };
    Keys[GLFW_KEY_PAGE_UP]       = { KeyCodes::PAGE_UP, glfwGetKeyScancode( GLFW_KEY_PAGE_UP ), '\0', '\0' };
    Keys[GLFW_KEY_PAGE_DOWN]     = { KeyCodes::PAGE_DOWN, glfwGetKeyScancode( GLFW_KEY_PAGE_DOWN ), '\0', '\0' };
    Keys[GLFW_KEY_HOME]          = { KeyCodes::HOME, glfwGetKeyScancode( GLFW_KEY_HOME ), '\0', '\0' };
    Keys[GLFW_KEY_END]           = { KeyCodes::END, glfwGetKeyScancode( GLFW_KEY_END ), '\0', '\0' };
    Keys[GLFW_KEY_F1]            = { KeyCodes::F1, glfwGetKeyScancode( GLFW_KEY_F1 ), '\0', '\0' };
    Keys[GLFW_KEY_F2]            = { KeyCodes::F2, glfwGetKeyScancode( GLFW_KEY_F2 ), '\0', '\0' };
    Keys[GLFW_KEY_F3]            = { KeyCodes::F3, glfwGetKeyScancode( GLFW_KEY_F3 ), '\0', '\0' };
    Keys[GLFW_KEY_F4]            = { KeyCodes::F4, glfwGetKeyScancode( GLFW_KEY_F4 ), '\0', '\0' };
    Keys[GLFW_KEY_F5]            = { KeyCodes::F5, glfwGetKeyScancode( GLFW_KEY_F5 ), '\0', '\0' };
    Keys[GLFW_KEY_F6]            = { KeyCodes::F6, glfwGetKeyScancode( GLFW_KEY_F6 ), '\0', '\0' };
    Keys[GLFW_KEY_F7]            = { KeyCodes::F7, glfwGetKeyScancode( GLFW_KEY_F7 ), '\0', '\0' };
    Keys[GLFW_KEY_F8]            = { KeyCodes::F8, glfwGetKeyScancode( GLFW_KEY_F8 ), '\0', '\0' };
    Keys[GLFW_KEY_F9]            = { KeyCodes::F9, glfwGetKeyScancode( GLFW_KEY_F9 ), '\0', '\0' };
    Keys[GLFW_KEY_F10]           = { KeyCodes::F10, glfwGetKeyScancode( GLFW_KEY_F10 ), '\0', '\0' };
    Keys[GLFW_KEY_F11]           = { KeyCodes::F11, glfwGetKeyScancode( GLFW_KEY_F11 ), '\0', '\0' };
    Keys[GLFW_KEY_F12]           = { KeyCodes::F12, glfwGetKeyScancode( GLFW_KEY_F12 ), '\0', '\0' };
    Keys[GLFW_KEY_F13]           = { KeyCodes::F13, glfwGetKeyScancode( GLFW_KEY_F13 ), '\0', '\0' };
    Keys[GLFW_KEY_F14]           = { KeyCodes::F14, glfwGetKeyScancode( GLFW_KEY_F14 ), '\0', '\0' };
    Keys[GLFW_KEY_F15]           = { KeyCodes::F15, glfwGetKeyScancode( GLFW_KEY_F15 ), '\0', '\0' };
    Keys[GLFW_KEY_F16]           = { KeyCodes::F16, glfwGetKeyScancode( GLFW_KEY_F16 ), '\0', '\0' };
    Keys[GLFW_KEY_F17]           = { KeyCodes::F17, glfwGetKeyScancode( GLFW_KEY_F17 ), '\0', '\0' };
    Keys[GLFW_KEY_F18]           = { KeyCodes::F18, glfwGetKeyScancode( GLFW_KEY_F18 ), '\0', '\0' };
    Keys[GLFW_KEY_F19]           = { KeyCodes::F19, glfwGetKeyScancode( GLFW_KEY_F19 ), '\0', '\0' };
    Keys[GLFW_KEY_F20]           = { KeyCodes::F20, glfwGetKeyScancode( GLFW_KEY_F20 ), '\0', '\0' };
    Keys[GLFW_KEY_F21]           = { KeyCodes::F21, glfwGetKeyScancode( GLFW_KEY_F21 ), '\0', '\0' };
    Keys[GLFW_KEY_F22]           = { KeyCodes::F22, glfwGetKeyScancode( GLFW_KEY_F22 ), '\0', '\0' };
    Keys[GLFW_KEY_F23]           = { KeyCodes::F23, glfwGetKeyScancode( GLFW_KEY_F23 ), '\0', '\0' };
    Keys[GLFW_KEY_F24]           = { KeyCodes::F24, glfwGetKeyScancode( GLFW_KEY_F24 ), '\0', '\0' };
    Keys[GLFW_KEY_F25]           = { KeyCodes::F25, glfwGetKeyScancode( GLFW_KEY_F25 ), '\0', '\0' };
    Keys[GLFW_KEY_SPACE]         = { KeyCodes::SPACE, glfwGetKeyScancode( GLFW_KEY_SPACE ), ' ', ' ' };
    Keys[GLFW_KEY_APOSTROPHE]    = { KeyCodes::APOSTROPHE, glfwGetKeyScancode( GLFW_KEY_APOSTROPHE ), '\'', '"' };
    Keys[GLFW_KEY_COMMA]         = { KeyCodes::COMMA, glfwGetKeyScancode( GLFW_KEY_COMMA ), ',', '<' };
    Keys[GLFW_KEY_MINUS]         = { KeyCodes::MINUS, glfwGetKeyScancode( GLFW_KEY_MINUS ), '-', '_' };
    Keys[GLFW_KEY_PERIOD]        = { KeyCodes::PERIOD, glfwGetKeyScancode( GLFW_KEY_PERIOD ), '.', '>' };
    Keys[GLFW_KEY_SLASH]         = { KeyCodes::SLASH, glfwGetKeyScancode( GLFW_KEY_SLASH ), '/', '?' };
    Keys[GLFW_KEY_SEMICOLON]     = { KeyCodes::SEMICOLON, glfwGetKeyScancode( GLFW_KEY_SEMICOLON ), ';', ':' };
    Keys[GLFW_KEY_EQUAL]         = { KeyCodes::EQUAL, glfwGetKeyScancode( GLFW_KEY_EQUAL ), '=', '+' };
    Keys[GLFW_KEY_LEFT_BRACKET]  = { KeyCodes::LEFT_BRACKET, glfwGetKeyScancode( GLFW_KEY_LEFT_BRACKET ), '[', '{' };
    Keys[GLFW_KEY_BACKSLASH]     = { KeyCodes::BACKSLASH, glfwGetKeyScancode( GLFW_KEY_BACKSLASH ), '\\', '|' };
    Keys[GLFW_KEY_RIGHT_BRACKET] = { KeyCodes::RIGHT_BRACKET, glfwGetKeyScancode( GLFW_KEY_RIGHT_BRACKET ), ']', '}' };
    Keys[GLFW_KEY_GRAVE_ACCENT]  = { KeyCodes::GRAVE_ACCENT, glfwGetKeyScancode( GLFW_KEY_GRAVE_ACCENT ), '`', '~' };
    Keys[GLFW_KEY_A]             = { KeyCodes::A, glfwGetKeyScancode( GLFW_KEY_A ), 'a', 'A' };
    Keys[GLFW_KEY_B]             = { KeyCodes::B, glfwGetKeyScancode( GLFW_KEY_B ), 'b', 'B' };
    Keys[GLFW_KEY_C]             = { KeyCodes::C, glfwGetKeyScancode( GLFW_KEY_C ), 'c', 'C' };
    Keys[GLFW_KEY_D]             = { KeyCodes::D, glfwGetKeyScancode( GLFW_KEY_D ), 'd', 'D' };
    Keys[GLFW_KEY_E]             = { KeyCodes::E, glfwGetKeyScancode( GLFW_KEY_E ), 'e', 'E' };
    Keys[GLFW_KEY_F]             = { KeyCodes::F, glfwGetKeyScancode( GLFW_KEY_F ), 'f', 'F' };
    Keys[GLFW_KEY_G]             = { KeyCodes::G, glfwGetKeyScancode( GLFW_KEY_G ), 'g', 'G' };
    Keys[GLFW_KEY_H]             = { KeyCodes::H, glfwGetKeyScancode( GLFW_KEY_H ), 'h', 'H' };
    Keys[GLFW_KEY_I]             = { KeyCodes::I, glfwGetKeyScancode( GLFW_KEY_I ), 'i', 'I' };
    Keys[GLFW_KEY_J]             = { KeyCodes::J, glfwGetKeyScancode( GLFW_KEY_J ), 'j', 'J' };
    Keys[GLFW_KEY_K]             = { KeyCodes::K, glfwGetKeyScancode( GLFW_KEY_K ), 'k', 'K' };
    Keys[GLFW_KEY_L]             = { KeyCodes::L, glfwGetKeyScancode( GLFW_KEY_L ), 'l', 'L' };
    Keys[GLFW_KEY_M]             = { KeyCodes::M, glfwGetKeyScancode( GLFW_KEY_M ), 'm', 'M' };
    Keys[GLFW_KEY_N]             = { KeyCodes::N, glfwGetKeyScancode( GLFW_KEY_N ), 'n', 'N' };
    Keys[GLFW_KEY_O]             = { KeyCodes::O, glfwGetKeyScancode( GLFW_KEY_O ), 'o', 'O' };
    Keys[GLFW_KEY_P]             = { KeyCodes::P, glfwGetKeyScancode( GLFW_KEY_P ), 'p', 'P' };
    Keys[GLFW_KEY_Q]             = { KeyCodes::Q, glfwGetKeyScancode( GLFW_KEY_Q ), 'q', 'Q' };
    Keys[GLFW_KEY_R]             = { KeyCodes::R, glfwGetKeyScancode( GLFW_KEY_R ), 'r', 'R' };
    Keys[GLFW_KEY_S]             = { KeyCodes::S, glfwGetKeyScancode( GLFW_KEY_S ), 's', 'S' };
    Keys[GLFW_KEY_T]             = { KeyCodes::T, glfwGetKeyScancode( GLFW_KEY_T ), 't', 'T' };
    Keys[GLFW_KEY_U]             = { KeyCodes::U, glfwGetKeyScancode( GLFW_KEY_U ), 'u', 'U' };
    Keys[GLFW_KEY_V]             = { KeyCodes::V, glfwGetKeyScancode( GLFW_KEY_V ), 'v', 'V' };
    Keys[GLFW_KEY_W]             = { KeyCodes::W, glfwGetKeyScancode( GLFW_KEY_W ), 'w', 'W' };
    Keys[GLFW_KEY_X]             = { KeyCodes::X, glfwGetKeyScancode( GLFW_KEY_X ), 'x', 'X' };
    Keys[GLFW_KEY_Y]             = { KeyCodes::Y, glfwGetKeyScancode( GLFW_KEY_Y ), 'y', 'Y' };
    Keys[GLFW_KEY_Z]             = { KeyCodes::Z, glfwGetKeyScancode( GLFW_KEY_Z ), 'z', 'Z' };
    Keys[GLFW_KEY_0]             = { KeyCodes::KEY_0, glfwGetKeyScancode( GLFW_KEY_0 ), '0', ')' };
    Keys[GLFW_KEY_1]             = { KeyCodes::KEY_1, glfwGetKeyScancode( GLFW_KEY_1 ), '1', '!' };
    Keys[GLFW_KEY_2]             = { KeyCodes::KEY_2, glfwGetKeyScancode( GLFW_KEY_2 ), '2', '@' };
    Keys[GLFW_KEY_3]             = { KeyCodes::KEY_3, glfwGetKeyScancode( GLFW_KEY_3 ), '3', '#' };
    Keys[GLFW_KEY_4]             = { KeyCodes::KEY_4, glfwGetKeyScancode( GLFW_KEY_4 ), '4', '$' };
    Keys[GLFW_KEY_5]             = { KeyCodes::KEY_5, glfwGetKeyScancode( GLFW_KEY_5 ), '5', '%' };
    Keys[GLFW_KEY_6]             = { KeyCodes::KEY_6, glfwGetKeyScancode( GLFW_KEY_6 ), '6', '^' };
    Keys[GLFW_KEY_7]             = { KeyCodes::KEY_7, glfwGetKeyScancode( GLFW_KEY_7 ), '7', '&' };
    Keys[GLFW_KEY_8]             = { KeyCodes::KEY_8, glfwGetKeyScancode( GLFW_KEY_8 ), '8', '*' };
    Keys[GLFW_KEY_9]             = { KeyCodes::KEY_9, glfwGetKeyScancode( GLFW_KEY_9 ), '9', '(' };
    Keys[GLFW_KEY_KP_0]          = { KeyCodes::KEYPAD_0, glfwGetKeyScancode( GLFW_KEY_KP_0 ), '0', '0' };
    Keys[GLFW_KEY_KP_1]          = { KeyCodes::KEYPAD_1, glfwGetKeyScancode( GLFW_KEY_KP_1 ), '1', '1' };
    Keys[GLFW_KEY_KP_2]          = { KeyCodes::KEYPAD_2, glfwGetKeyScancode( GLFW_KEY_KP_2 ), '2', '2' };
    Keys[GLFW_KEY_KP_3]          = { KeyCodes::KEYPAD_3, glfwGetKeyScancode( GLFW_KEY_KP_3 ), '3', '3' };
    Keys[GLFW_KEY_KP_4]          = { KeyCodes::KEYPAD_4, glfwGetKeyScancode( GLFW_KEY_KP_4 ), '4', '4' };
    Keys[GLFW_KEY_KP_5]          = { KeyCodes::KEYPAD_5, glfwGetKeyScancode( GLFW_KEY_KP_5 ), '5', '5' };
    Keys[GLFW_KEY_KP_6]          = { KeyCodes::KEYPAD_6, glfwGetKeyScancode( GLFW_KEY_KP_6 ), '6', '6' };
    Keys[GLFW_KEY_KP_7]          = { KeyCodes::KEYPAD_7, glfwGetKeyScancode( GLFW_KEY_KP_7 ), '7', '7' };
    Keys[GLFW_KEY_KP_8]          = { KeyCodes::KEYPAD_8, glfwGetKeyScancode( GLFW_KEY_KP_8 ), '8', '8' };
    Keys[GLFW_KEY_KP_9]          = { KeyCodes::KEYPAD_9, glfwGetKeyScancode( GLFW_KEY_KP_9 ), '9', '9' };
    Keys[GLFW_KEY_KP_DECIMAL]    = { KeyCodes::KEYPAD_DECIMAL, glfwGetKeyScancode( GLFW_KEY_KP_DECIMAL ), '.', '.' };
    Keys[GLFW_KEY_KP_DIVIDE]     = { KeyCodes::KEYPAD_DIVIDE, glfwGetKeyScancode( GLFW_KEY_KP_DIVIDE ), '/', '/' };
    Keys[GLFW_KEY_KP_MULTIPLY]   = { KeyCodes::KEYPAD_MULTIPLY, glfwGetKeyScancode( GLFW_KEY_KP_MULTIPLY ), '*', '*' };
    Keys[GLFW_KEY_KP_SUBTRACT]   = { KeyCodes::KEYPAD_SUBTRACT, glfwGetKeyScancode( GLFW_KEY_KP_SUBTRACT ), '-', '-' };
    Keys[GLFW_KEY_KP_ADD]        = { KeyCodes::KEYPAD_ADD, glfwGetKeyScancode( GLFW_KEY_KP_ADD ), '+', '+' };
    Keys[GLFW_KEY_KP_EQUAL]      = { KeyCodes::KEYPAD_EQUAL, glfwGetKeyScancode( GLFW_KEY_KP_EQUAL ), '=', '=' };
    Keys[GLFW_KEY_ENTER]         = { KeyCodes::ENTER, glfwGetKeyScancode( GLFW_KEY_ENTER ), '\n', '\0' };
    Keys[GLFW_KEY_TAB]           = { KeyCodes::TAB, glfwGetKeyScancode( GLFW_KEY_TAB ), '\t', '\0' };
    Keys[GLFW_KEY_BACKSPACE]     = { KeyCodes::BACKSPACE, glfwGetKeyScancode( GLFW_KEY_BACKSPACE ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT]         = { KeyCodes::RIGHT, glfwGetKeyScancode( GLFW_KEY_RIGHT ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT]          = { KeyCodes::LEFT, glfwGetKeyScancode( GLFW_KEY_LEFT ), '\0', '\0' };
    Keys[GLFW_KEY_DOWN]          = { KeyCodes::DOWN, glfwGetKeyScancode( GLFW_KEY_DOWN ), '\0', '\0' };
    Keys[GLFW_KEY_UP]            = { KeyCodes::UP, glfwGetKeyScancode( GLFW_KEY_UP ), '\0', '\0' };
    Keys[GLFW_KEY_CAPS_LOCK]     = { KeyCodes::CAPS_LOCK, glfwGetKeyScancode( GLFW_KEY_CAPS_LOCK ), '\0', '\0' };
    Keys[GLFW_KEY_SCROLL_LOCK]   = { KeyCodes::SCROLL_LOCK, glfwGetKeyScancode( GLFW_KEY_SCROLL_LOCK ), '\0', '\0' };
    Keys[GLFW_KEY_NUM_LOCK]      = { KeyCodes::NUM_LOCK, glfwGetKeyScancode( GLFW_KEY_NUM_LOCK ), '\0', '\0' };
    Keys[GLFW_KEY_PRINT_SCREEN]  = { KeyCodes::PRINT_SCREEN, glfwGetKeyScancode( GLFW_KEY_PRINT_SCREEN ), '\0', '\0' };
    Keys[GLFW_KEY_PAUSE]         = { KeyCodes::PAUSE, glfwGetKeyScancode( GLFW_KEY_PAUSE ), '\0', '\0' };
    Keys[GLFW_KEY_KP_ENTER]      = { KeyCodes::KEYPAD_ENTER, glfwGetKeyScancode( GLFW_KEY_KP_ENTER ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_SHIFT]    = { KeyCodes::LEFT_SHIFT, glfwGetKeyScancode( GLFW_KEY_LEFT_SHIFT ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_CONTROL]  = { KeyCodes::LEFT_CONTROL, glfwGetKeyScancode( GLFW_KEY_LEFT_CONTROL ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_ALT]      = { KeyCodes::LEFT_ALT, glfwGetKeyScancode( GLFW_KEY_LEFT_ALT ), '\0', '\0' };
    Keys[GLFW_KEY_LEFT_SUPER]    = { KeyCodes::LEFT_SUPER, glfwGetKeyScancode( GLFW_KEY_LEFT_SUPER ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_SHIFT]   = { KeyCodes::RIGHT_SHIFT, glfwGetKeyScancode( GLFW_KEY_RIGHT_SHIFT ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_CONTROL] = { KeyCodes::RIGHT_CONTROL, glfwGetKeyScancode( GLFW_KEY_RIGHT_CONTROL ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_ALT]     = { KeyCodes::RIGHT_ALT, glfwGetKeyScancode( GLFW_KEY_RIGHT_ALT ), '\0', '\0' };
    Keys[GLFW_KEY_RIGHT_SUPER]   = { KeyCodes::RIGHT_SUPER, glfwGetKeyScancode( GLFW_KEY_RIGHT_SUPER ), '\0', '\0' };
    Keys[GLFW_KEY_MENU]          = { KeyCodes::MENU, glfwGetKeyScancode( GLFW_KEY_MENU ), '\0', '\0' };
    // clang-format off
}


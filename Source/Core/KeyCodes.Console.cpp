#include "KeyCodes.h"

char keycode_t::GetCharacter( bool isShifted ) const
{
    return !isShifted ? Symbol : ShiftedSymbol;
}

KeyboardHandler::KeyboardHandler()
{
    InitKeyCodes();
}

keycode_t const &KeyboardHandler::GetKeyCode( int keycode )
{
    return _keys[keycode];
}

// #if 0
namespace platform::windows
{
    // Source: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    enum keycode
    {
        KEY_LBUTTON          = 0x01, // Left mouse button
        KEY_RBUTTON          = 0x02, // Right mouse button
        KEY_CANCEL           = 0x03, // Control-break processing
        KEY_MBUTTON          = 0x04, // Middle mouse button
        KEY_XBUTTON1         = 0x05, // X1 mouse button
        KEY_XBUTTON2         = 0x06, // X2 mouse button
        KEY_BACKSPACE        = 0x08, // BACKSPACE key
        KEY_TAB              = 0x09, // TAB key
        KEY_CLEAR            = 0x0C, // CLEAR key
        KEY_ENTER            = 0x0D, // ENTER key
        KEY_SHIFT            = 0x10, // SHIFT key
        KEY_CONTROL          = 0x11, // CTRL key
        KEY_MENU             = 0x12, // ALT key
        KEY_PAUSE            = 0x13, // PAUSE key
        KEY_CAPS_LOCK        = 0x14, // CAPS LOCK key
        KEY_ESCAPE           = 0x1B, // ESC key
        KEY_SPACE            = 0x20, // SPACEBAR
        KEY_PAGE_UP          = 0x21, // PAGE UP key
        KEY_PAGE_DOWN        = 0x22, // PAGE DOWN key
        KEY_END              = 0x23, // END key
        KEY_HOME             = 0x24, // HOME key
        KEY_LEFT             = 0x25, // LEFT ARROW key
        KEY_UP               = 0x26, // UP ARROW key
        KEY_RIGHT            = 0x27, // RIGHT ARROW key
        KEY_DOWN             = 0x28, // DOWN ARROW key
        KEY_SELECT           = 0x29, // SELECT key
        KEY_PRINT            = 0x2A, // PRINT key
        KEY_EXECUTE          = 0x2B, // EXECUTE key
        KEY_PRINT_SCREEN     = 0x2C, // PRINT SCREEN key
        KEY_INSERT           = 0x2D, // INS key
        KEY_DELETE           = 0x2E, // DEL key
        KEY_HELP             = 0x2F, // HELP key
        KEY_0                = 0x30, // 0 key
        KEY_1                = 0x31, // 1 key
        KEY_2                = 0x32, // 2 key
        KEY_3                = 0x33, // 3 key
        KEY_4                = 0x34, // 4 key
        KEY_5                = 0x35, // 5 key
        KEY_6                = 0x36, // 6 key
        KEY_7                = 0x37, // 7 key
        KEY_8                = 0x38, // 8 key
        KEY_9                = 0x39, // 9 key
        KEY_A                = 0x41, // A key
        KEY_B                = 0x42, // B key
        KEY_C                = 0x43, // C key
        KEY_D                = 0x44, // D key
        KEY_E                = 0x45, // E key
        KEY_F                = 0x46, // F key
        KEY_G                = 0x47, // G key
        KEY_H                = 0x48, // H key
        KEY_I                = 0x49, // I key
        KEY_J                = 0x4A, // J key
        KEY_K                = 0x4B, // K key
        KEY_L                = 0x4C, // L key
        KEY_M                = 0x4D, // M key
        KEY_N                = 0x4E, // N key
        KEY_O                = 0x4F, // O key
        KEY_P                = 0x50, // P key
        KEY_Q                = 0x51, // Q key
        KEY_R                = 0x52, // R key
        KEY_S                = 0x53, // S key
        KEY_T                = 0x54, // T key
        KEY_U                = 0x55, // U key
        KEY_V                = 0x56, // V key
        KEY_W                = 0x57, // W key
        KEY_X                = 0x58, // X key
        KEY_Y                = 0x59, // Y key
        KEY_Z                = 0x5A, // Z key
        KEY_LEFT_SUPER       = 0x5B, // Left Windows key
        KEY_RIGHT_SUPER      = 0x5C, // Right Windows key
        KEY_APPS             = 0x5D, // Applications key
        KEY_SLEEP            = 0x5F, // Computer Sleep key
        KEY_NUMPAD_0         = 0x60, // Numeric keypad 0 key
        KEY_NUMPAD_1         = 0x61, // Numeric keypad 1 key
        KEY_NUMPAD_2         = 0x62, // Numeric keypad 2 key
        KEY_NUMPAD_3         = 0x63, // Numeric keypad 3 key
        KEY_NUMPAD_4         = 0x64, // Numeric keypad 4 key
        KEY_NUMPAD_5         = 0x65, // Numeric keypad 5 key
        KEY_NUMPAD_6         = 0x66, // Numeric keypad 6 key
        KEY_NUMPAD_7         = 0x67, // Numeric keypad 7 key
        KEY_NUMPAD_8         = 0x68, // Numeric keypad 8 key
        KEY_NUMPAD_9         = 0x69, // Numeric keypad 9 key
        KEY_NUMPAD_MULTIPLY  = 0x6A, // Multiply key
        KEY_NUMPAD_ADD       = 0x6B, // Add key
        KEY_NUMPAD_SEPARATOR = 0x6C, // Separator key
        KEY_NUMPAD_SUBTRACT  = 0x6D, // Subtract key
        KEY_NUMPAD_DECIMAL   = 0x6E, // Decimal key
        KEY_NUMPAD_DIVIDE    = 0x6F, // Divide key
        KEY_F1               = 0x70, // F1 key
        KEY_F2               = 0x71, // F2 key
        KEY_F3               = 0x72, // F3 key
        KEY_F4               = 0x73, // F4 key
        KEY_F5               = 0x74, // F5 key
        KEY_F6               = 0x75, // F6 key
        KEY_F7               = 0x76, // F7 key
        KEY_F8               = 0x77, // F8 key
        KEY_F9               = 0x78, // F9 key
        KEY_F10              = 0x79, // F10 key
        KEY_F11              = 0x7A, // F11 key
        KEY_F12              = 0x7B, // F12 key
        KEY_F13              = 0x7C, // F13 key
        KEY_F14              = 0x7D, // F14 key
        KEY_F15              = 0x7E, // F15 key
        KEY_F16              = 0x7F, // F16 key
        KEY_F17              = 0x80, // F17 key
        KEY_F18              = 0x81, // F18 key
        KEY_F19              = 0x82, // F19 key
        KEY_F20              = 0x83, // F20 key
        KEY_F21              = 0x84, // F21 key
        KEY_F22              = 0x85, // F22 key
        KEY_F23              = 0x86, // F23 key
        KEY_F24              = 0x87, // F24 key
        KEY_NUM_LOCK         = 0x90, // NUM LOCK key
        KEY_SCROLL_LOCK      = 0x91, // SCROLL LOCK key
        KEY_LEFT_SHIFT       = 0xA0, // Left SHIFT key
        KEY_RIGHT_SHIFT      = 0xA1, // Right SHIFT key
        KEY_LEFT_CONTROL     = 0xA2, // Left CONTROL key
        KEY_RIGHT_CONTROL    = 0xA3, // Right CONTROL key
        KEY_LEFT_ALT         = 0xA4, // Left ALT key
        KEY_RIGHT_ALT        = 0xA5, // Right ALT key
        KEY_SEMICOLON        = 0xBA, // Used for miscellaneous characters; For the US standard keyboard, the ;: key
        KEY_EQUAL            = 0xBB, // For any country/region, the + key
        KEY_COMMA            = 0xBC, // For any country/region, the , key
        KEY_MINUS            = 0xBD, // For any country/region, the - key
        KEY_PERIOD           = 0xBE, // For any country/region, the . key
        KEY_SLASH            = 0xBF, // Used for miscellaneous characters; For the US standard keyboard, the /? key
        KEY_GRAVE_ACCENT     = 0xC0, // Used for miscellaneous characters; For the US standard keyboard, the `~ key
        KEY_LEFT_BRACKET     = 0xDB, // Used for miscellaneous characters; For the US standard keyboard, the [{ key
        KEY_BACKSLASH        = 0xDC, // Used for miscellaneous characters; For the US standard keyboard, the \\| key
        KEY_RIGHT_BRACKET    = 0xDD, // Used for miscellaneous characters; For the US standard keyboard, the ]} key
        KEY_APOSTROPHE       = 0xDE, // Used for miscellaneous characters; For the US standard keyboard, the '" key
        COUNT
    };
} // namespace platform
// #endif

void KeyboardHandler::InitKeyCodes()
{
    int controlKeyID = 0;

    using platform_keycode = platform::windows::keycode;

    _keys[platform_keycode::KEY_DELETE]          = { keycode::DELETE_K, '\0', '\0' };
    _keys[platform_keycode::KEY_ESCAPE]          = { keycode::ESCAPE, '\0', '\0' };
    _keys[platform_keycode::KEY_INSERT]          = { keycode::INSERT, '\0', '\0' };
    _keys[platform_keycode::KEY_PAGE_UP]         = { keycode::PAGE_UP, '\0', '\0' };
    _keys[platform_keycode::KEY_PAGE_DOWN]       = { keycode::PAGE_DOWN, '\0', '\0' };
    _keys[platform_keycode::KEY_HOME]            = { keycode::HOME, '\0', '\0' };
    _keys[platform_keycode::KEY_END]             = { keycode::END, '\0', '\0' };
    _keys[platform_keycode::KEY_F1]              = { keycode::F1, '\0', '\0' };
    _keys[platform_keycode::KEY_F2]              = { keycode::F2, '\0', '\0' };
    _keys[platform_keycode::KEY_F3]              = { keycode::F3, '\0', '\0' };
    _keys[platform_keycode::KEY_F4]              = { keycode::F4, '\0', '\0' };
    _keys[platform_keycode::KEY_F5]              = { keycode::F5, '\0', '\0' };
    _keys[platform_keycode::KEY_F6]              = { keycode::F6, '\0', '\0' };
    _keys[platform_keycode::KEY_F7]              = { keycode::F7, '\0', '\0' };
    _keys[platform_keycode::KEY_F8]              = { keycode::F8, '\0', '\0' };
    _keys[platform_keycode::KEY_F9]              = { keycode::F9, '\0', '\0' };
    _keys[platform_keycode::KEY_F10]             = { keycode::F10, '\0', '\0' };
    _keys[platform_keycode::KEY_F11]             = { keycode::F11, '\0', '\0' };
    _keys[platform_keycode::KEY_F12]             = { keycode::F12, '\0', '\0' };
    _keys[platform_keycode::KEY_F13]             = { keycode::F13, '\0', '\0' };
    _keys[platform_keycode::KEY_F14]             = { keycode::F14, '\0', '\0' };
    _keys[platform_keycode::KEY_F15]             = { keycode::F15, '\0', '\0' };
    _keys[platform_keycode::KEY_F16]             = { keycode::F16, '\0', '\0' };
    _keys[platform_keycode::KEY_F17]             = { keycode::F17, '\0', '\0' };
    _keys[platform_keycode::KEY_F18]             = { keycode::F18, '\0', '\0' };
    _keys[platform_keycode::KEY_F19]             = { keycode::F19, '\0', '\0' };
    _keys[platform_keycode::KEY_F20]             = { keycode::F20, '\0', '\0' };
    _keys[platform_keycode::KEY_F21]             = { keycode::F21, '\0', '\0' };
    _keys[platform_keycode::KEY_F22]             = { keycode::F22, '\0', '\0' };
    _keys[platform_keycode::KEY_F23]             = { keycode::F23, '\0', '\0' };
    _keys[platform_keycode::KEY_F24]             = { keycode::F24, '\0', '\0' };
    _keys[platform_keycode::KEY_SPACE]           = { keycode::SPACE, ' ', ' ' };
    _keys[platform_keycode::KEY_APOSTROPHE]      = { keycode::APOSTROPHE, '\'', '"' };
    _keys[platform_keycode::KEY_COMMA]           = { keycode::COMMA, ',', '<' };
    _keys[platform_keycode::KEY_MINUS]           = { keycode::MINUS, '-', '_' };
    _keys[platform_keycode::KEY_PERIOD]          = { keycode::PERIOD, '.', '>' };
    _keys[platform_keycode::KEY_SLASH]           = { keycode::SLASH, '/', '?' };
    _keys[platform_keycode::KEY_SEMICOLON]       = { keycode::SEMICOLON, ';', ':' };
    _keys[platform_keycode::KEY_EQUAL]           = { keycode::EQUAL, '=', '+' };
    _keys[platform_keycode::KEY_LEFT_BRACKET]    = { keycode::LEFT_BRACKET, '[', '{' };
    _keys[platform_keycode::KEY_BACKSLASH]       = { keycode::BACKSLASH, '\\', '|' };
    _keys[platform_keycode::KEY_RIGHT_BRACKET]   = { keycode::RIGHT_BRACKET, ']', '}' };
    _keys[platform_keycode::KEY_GRAVE_ACCENT]    = { keycode::GRAVE_ACCENT, '`', '~' };
    _keys[platform_keycode::KEY_A]               = { keycode::A, 'a', 'A' };
    _keys[platform_keycode::KEY_B]               = { keycode::B, 'b', 'B' };
    _keys[platform_keycode::KEY_C]               = { keycode::C, 'c', 'C' };
    _keys[platform_keycode::KEY_D]               = { keycode::D, 'd', 'D' };
    _keys[platform_keycode::KEY_E]               = { keycode::E, 'e', 'E' };
    _keys[platform_keycode::KEY_F]               = { keycode::F, 'f', 'F' };
    _keys[platform_keycode::KEY_G]               = { keycode::G, 'g', 'G' };
    _keys[platform_keycode::KEY_H]               = { keycode::H, 'h', 'H' };
    _keys[platform_keycode::KEY_I]               = { keycode::I, 'i', 'I' };
    _keys[platform_keycode::KEY_J]               = { keycode::J, 'j', 'J' };
    _keys[platform_keycode::KEY_K]               = { keycode::K, 'k', 'K' };
    _keys[platform_keycode::KEY_L]               = { keycode::L, 'l', 'L' };
    _keys[platform_keycode::KEY_M]               = { keycode::M, 'm', 'M' };
    _keys[platform_keycode::KEY_N]               = { keycode::N, 'n', 'N' };
    _keys[platform_keycode::KEY_O]               = { keycode::O, 'o', 'O' };
    _keys[platform_keycode::KEY_P]               = { keycode::P, 'p', 'P' };
    _keys[platform_keycode::KEY_Q]               = { keycode::Q, 'q', 'Q' };
    _keys[platform_keycode::KEY_R]               = { keycode::R, 'r', 'R' };
    _keys[platform_keycode::KEY_S]               = { keycode::S, 's', 'S' };
    _keys[platform_keycode::KEY_T]               = { keycode::T, 't', 'T' };
    _keys[platform_keycode::KEY_U]               = { keycode::U, 'u', 'U' };
    _keys[platform_keycode::KEY_V]               = { keycode::V, 'v', 'V' };
    _keys[platform_keycode::KEY_W]               = { keycode::W, 'w', 'W' };
    _keys[platform_keycode::KEY_X]               = { keycode::X, 'x', 'X' };
    _keys[platform_keycode::KEY_Y]               = { keycode::Y, 'y', 'Y' };
    _keys[platform_keycode::KEY_Z]               = { keycode::Z, 'z', 'Z' };
    _keys[platform_keycode::KEY_0]               = { keycode::KEY_0, '0', ')' };
    _keys[platform_keycode::KEY_1]               = { keycode::KEY_1, '1', '!' };
    _keys[platform_keycode::KEY_2]               = { keycode::KEY_2, '2', '@' };
    _keys[platform_keycode::KEY_3]               = { keycode::KEY_3, '3', '#' };
    _keys[platform_keycode::KEY_4]               = { keycode::KEY_4, '4', '$' };
    _keys[platform_keycode::KEY_5]               = { keycode::KEY_5, '5', '%' };
    _keys[platform_keycode::KEY_6]               = { keycode::KEY_6, '6', '^' };
    _keys[platform_keycode::KEY_7]               = { keycode::KEY_7, '7', '&' };
    _keys[platform_keycode::KEY_8]               = { keycode::KEY_8, '8', '*' };
    _keys[platform_keycode::KEY_9]               = { keycode::KEY_9, '9', '(' };
    _keys[platform_keycode::KEY_NUMPAD_0]        = { keycode::KEYPAD_0, '0', '0' };
    _keys[platform_keycode::KEY_NUMPAD_1]        = { keycode::KEYPAD_1, '1', '1' };
    _keys[platform_keycode::KEY_NUMPAD_2]        = { keycode::KEYPAD_2, '2', '2' };
    _keys[platform_keycode::KEY_NUMPAD_3]        = { keycode::KEYPAD_3, '3', '3' };
    _keys[platform_keycode::KEY_NUMPAD_4]        = { keycode::KEYPAD_4, '4', '4' };
    _keys[platform_keycode::KEY_NUMPAD_5]        = { keycode::KEYPAD_5, '5', '5' };
    _keys[platform_keycode::KEY_NUMPAD_6]        = { keycode::KEYPAD_6, '6', '6' };
    _keys[platform_keycode::KEY_NUMPAD_7]        = { keycode::KEYPAD_7, '7', '7' };
    _keys[platform_keycode::KEY_NUMPAD_8]        = { keycode::KEYPAD_8, '8', '8' };
    _keys[platform_keycode::KEY_NUMPAD_9]        = { keycode::KEYPAD_9, '9', '9' };
    _keys[platform_keycode::KEY_NUMPAD_DECIMAL]  = { keycode::KEYPAD_DECIMAL, '.', '.' };
    _keys[platform_keycode::KEY_NUMPAD_DIVIDE]   = { keycode::KEYPAD_DIVIDE, '/', '/' };
    _keys[platform_keycode::KEY_NUMPAD_MULTIPLY] = { keycode::KEYPAD_MULTIPLY, '*', '*' };
    _keys[platform_keycode::KEY_NUMPAD_SUBTRACT] = { keycode::KEYPAD_SUBTRACT, '-', '-' };
    _keys[platform_keycode::KEY_NUMPAD_ADD]      = { keycode::KEYPAD_ADD, '+', '+' };
    _keys[platform_keycode::KEY_ENTER]           = { keycode::ENTER, '\n', '\0' };
    _keys[platform_keycode::KEY_TAB]             = { keycode::TAB, '\t', '\0' };
    _keys[platform_keycode::KEY_BACKSPACE]       = { keycode::BACKSPACE, '\0', '\0' };
    _keys[platform_keycode::KEY_RIGHT]           = { keycode::RIGHT, '\0', '\0' };
    _keys[platform_keycode::KEY_LEFT]            = { keycode::LEFT, '\0', '\0' };
    _keys[platform_keycode::KEY_DOWN]            = { keycode::DOWN, '\0', '\0' };
    _keys[platform_keycode::KEY_UP]              = { keycode::UP, '\0', '\0' };
    _keys[platform_keycode::KEY_CAPS_LOCK]       = { keycode::CAPS_LOCK, '\0', '\0' };
    _keys[platform_keycode::KEY_SCROLL_LOCK]     = { keycode::SCROLL_LOCK, '\0', '\0' };
    _keys[platform_keycode::KEY_NUM_LOCK]        = { keycode::NUM_LOCK, '\0', '\0' };
    _keys[platform_keycode::KEY_PRINT_SCREEN]    = { keycode::PRINT_SCREEN, '\0', '\0' };
    _keys[platform_keycode::KEY_PAUSE]           = { keycode::PAUSE, '\0', '\0' };
    _keys[platform_keycode::KEY_LEFT_SHIFT]      = { keycode::LEFT_SHIFT, '\0', '\0' };
    _keys[platform_keycode::KEY_LEFT_CONTROL]    = { keycode::LEFT_CONTROL, '\0', '\0' };
    _keys[platform_keycode::KEY_LEFT_ALT]        = { keycode::LEFT_ALT, '\0', '\0' };
    _keys[platform_keycode::KEY_LEFT_SUPER]      = { keycode::LEFT_SUPER, '\0', '\0' };
    _keys[platform_keycode::KEY_RIGHT_SHIFT]     = { keycode::RIGHT_SHIFT, '\0', '\0' };
    _keys[platform_keycode::KEY_RIGHT_CONTROL]   = { keycode::RIGHT_CONTROL, '\0', '\0' };
    _keys[platform_keycode::KEY_RIGHT_ALT]       = { keycode::RIGHT_ALT, '\0', '\0' };
    _keys[platform_keycode::KEY_RIGHT_SUPER]     = { keycode::RIGHT_SUPER, '\0', '\0' };
    _keys[platform_keycode::KEY_MENU]            = { keycode::MENU, '\0', '\0' };
    // clang-format off
}

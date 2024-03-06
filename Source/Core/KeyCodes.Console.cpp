#include "KeyCodes.h"
#include "GLFW/glfw3.h"

// KeyCode Keys[KEY_LAST];
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
    return Keys[keycode];
}

// #if 0
namespace Platform
{
    // Source: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    enum KeyCodes
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
    };
} // namespace Platform
// #endif

void KeyboardHandler::InitKeyCodes()
{
    int controlKeyID                              = 0;
    Keys[Platform::KeyCodes::KEY_DELETE]          = { key_codes::DELETE_K, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_ESCAPE]          = { key_codes::ESCAPE, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_INSERT]          = { key_codes::INSERT, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_PAGE_UP]         = { key_codes::PAGE_UP, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_PAGE_DOWN]       = { key_codes::PAGE_DOWN, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_HOME]            = { key_codes::HOME, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_END]             = { key_codes::END, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F1]              = { key_codes::F1, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F2]              = { key_codes::F2, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F3]              = { key_codes::F3, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F4]              = { key_codes::F4, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F5]              = { key_codes::F5, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F6]              = { key_codes::F6, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F7]              = { key_codes::F7, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F8]              = { key_codes::F8, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F9]              = { key_codes::F9, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F10]             = { key_codes::F10, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F11]             = { key_codes::F11, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F12]             = { key_codes::F12, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F13]             = { key_codes::F13, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F14]             = { key_codes::F14, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F15]             = { key_codes::F15, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F16]             = { key_codes::F16, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F17]             = { key_codes::F17, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F18]             = { key_codes::F18, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F19]             = { key_codes::F19, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F20]             = { key_codes::F20, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F21]             = { key_codes::F21, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F22]             = { key_codes::F22, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F23]             = { key_codes::F23, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F24]             = { key_codes::F24, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_SPACE]           = { key_codes::SPACE, ' ', ' ' };
    Keys[Platform::KeyCodes::KEY_APOSTROPHE]      = { key_codes::APOSTROPHE, '\'', '"' };
    Keys[Platform::KeyCodes::KEY_COMMA]           = { key_codes::COMMA, ',', '<' };
    Keys[Platform::KeyCodes::KEY_MINUS]           = { key_codes::MINUS, '-', '_' };
    Keys[Platform::KeyCodes::KEY_PERIOD]          = { key_codes::PERIOD, '.', '>' };
    Keys[Platform::KeyCodes::KEY_SLASH]           = { key_codes::SLASH, '/', '?' };
    Keys[Platform::KeyCodes::KEY_SEMICOLON]       = { key_codes::SEMICOLON, ';', ':' };
    Keys[Platform::KeyCodes::KEY_EQUAL]           = { key_codes::EQUAL, '=', '+' };
    Keys[Platform::KeyCodes::KEY_LEFT_BRACKET]    = { key_codes::LEFT_BRACKET, '[', '{' };
    Keys[Platform::KeyCodes::KEY_BACKSLASH]       = { key_codes::BACKSLASH, '\\', '|' };
    Keys[Platform::KeyCodes::KEY_RIGHT_BRACKET]   = { key_codes::RIGHT_BRACKET, ']', '}' };
    Keys[Platform::KeyCodes::KEY_GRAVE_ACCENT]    = { key_codes::GRAVE_ACCENT, '`', '~' };
    Keys[Platform::KeyCodes::KEY_A]               = { key_codes::A, 'a', 'A' };
    Keys[Platform::KeyCodes::KEY_B]               = { key_codes::B, 'b', 'B' };
    Keys[Platform::KeyCodes::KEY_C]               = { key_codes::C, 'c', 'C' };
    Keys[Platform::KeyCodes::KEY_D]               = { key_codes::D, 'd', 'D' };
    Keys[Platform::KeyCodes::KEY_E]               = { key_codes::E, 'e', 'E' };
    Keys[Platform::KeyCodes::KEY_F]               = { key_codes::F, 'f', 'F' };
    Keys[Platform::KeyCodes::KEY_G]               = { key_codes::G, 'g', 'G' };
    Keys[Platform::KeyCodes::KEY_H]               = { key_codes::H, 'h', 'H' };
    Keys[Platform::KeyCodes::KEY_I]               = { key_codes::I, 'i', 'I' };
    Keys[Platform::KeyCodes::KEY_J]               = { key_codes::J, 'j', 'J' };
    Keys[Platform::KeyCodes::KEY_K]               = { key_codes::K, 'k', 'K' };
    Keys[Platform::KeyCodes::KEY_L]               = { key_codes::L, 'l', 'L' };
    Keys[Platform::KeyCodes::KEY_M]               = { key_codes::M, 'm', 'M' };
    Keys[Platform::KeyCodes::KEY_N]               = { key_codes::N, 'n', 'N' };
    Keys[Platform::KeyCodes::KEY_O]               = { key_codes::O, 'o', 'O' };
    Keys[Platform::KeyCodes::KEY_P]               = { key_codes::P, 'p', 'P' };
    Keys[Platform::KeyCodes::KEY_Q]               = { key_codes::Q, 'q', 'Q' };
    Keys[Platform::KeyCodes::KEY_R]               = { key_codes::R, 'r', 'R' };
    Keys[Platform::KeyCodes::KEY_S]               = { key_codes::S, 's', 'S' };
    Keys[Platform::KeyCodes::KEY_T]               = { key_codes::T, 't', 'T' };
    Keys[Platform::KeyCodes::KEY_U]               = { key_codes::U, 'u', 'U' };
    Keys[Platform::KeyCodes::KEY_V]               = { key_codes::V, 'v', 'V' };
    Keys[Platform::KeyCodes::KEY_W]               = { key_codes::W, 'w', 'W' };
    Keys[Platform::KeyCodes::KEY_X]               = { key_codes::X, 'x', 'X' };
    Keys[Platform::KeyCodes::KEY_Y]               = { key_codes::Y, 'y', 'Y' };
    Keys[Platform::KeyCodes::KEY_Z]               = { key_codes::Z, 'z', 'Z' };
    Keys[Platform::KeyCodes::KEY_0]               = { key_codes::KEY_0, '0', ')' };
    Keys[Platform::KeyCodes::KEY_1]               = { key_codes::KEY_1, '1', '!' };
    Keys[Platform::KeyCodes::KEY_2]               = { key_codes::KEY_2, '2', '@' };
    Keys[Platform::KeyCodes::KEY_3]               = { key_codes::KEY_3, '3', '#' };
    Keys[Platform::KeyCodes::KEY_4]               = { key_codes::KEY_4, '4', '$' };
    Keys[Platform::KeyCodes::KEY_5]               = { key_codes::KEY_5, '5', '%' };
    Keys[Platform::KeyCodes::KEY_6]               = { key_codes::KEY_6, '6', '^' };
    Keys[Platform::KeyCodes::KEY_7]               = { key_codes::KEY_7, '7', '&' };
    Keys[Platform::KeyCodes::KEY_8]               = { key_codes::KEY_8, '8', '*' };
    Keys[Platform::KeyCodes::KEY_9]               = { key_codes::KEY_9, '9', '(' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_0]        = { key_codes::KEYPAD_0, '0', '0' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_1]        = { key_codes::KEYPAD_1, '1', '1' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_2]        = { key_codes::KEYPAD_2, '2', '2' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_3]        = { key_codes::KEYPAD_3, '3', '3' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_4]        = { key_codes::KEYPAD_4, '4', '4' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_5]        = { key_codes::KEYPAD_5, '5', '5' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_6]        = { key_codes::KEYPAD_6, '6', '6' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_7]        = { key_codes::KEYPAD_7, '7', '7' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_8]        = { key_codes::KEYPAD_8, '8', '8' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_9]        = { key_codes::KEYPAD_9, '9', '9' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_DECIMAL]  = { key_codes::KEYPAD_DECIMAL, '.', '.' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_DIVIDE]   = { key_codes::KEYPAD_DIVIDE, '/', '/' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_MULTIPLY] = { key_codes::KEYPAD_MULTIPLY, '*', '*' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_SUBTRACT] = { key_codes::KEYPAD_SUBTRACT, '-', '-' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_ADD]      = { key_codes::KEYPAD_ADD, '+', '+' };
    Keys[Platform::KeyCodes::KEY_ENTER]           = { key_codes::ENTER, '\n', '\0' };
    Keys[Platform::KeyCodes::KEY_TAB]             = { key_codes::TAB, '\t', '\0' };
    Keys[Platform::KeyCodes::KEY_BACKSPACE]       = { key_codes::BACKSPACE, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_RIGHT]           = { key_codes::RIGHT, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_LEFT]            = { key_codes::LEFT, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_DOWN]            = { key_codes::DOWN, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_UP]              = { key_codes::UP, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_CAPS_LOCK]       = { key_codes::CAPS_LOCK, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_SCROLL_LOCK]     = { key_codes::SCROLL_LOCK, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_NUM_LOCK]        = { key_codes::NUM_LOCK, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_PRINT_SCREEN]    = { key_codes::PRINT_SCREEN, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_PAUSE]           = { key_codes::PAUSE, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_LEFT_SHIFT]      = { key_codes::LEFT_SHIFT, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_LEFT_CONTROL]    = { key_codes::LEFT_CONTROL, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_LEFT_ALT]        = { key_codes::LEFT_ALT, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_LEFT_SUPER]      = { key_codes::LEFT_SUPER, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_RIGHT_SHIFT]     = { key_codes::RIGHT_SHIFT, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_RIGHT_CONTROL]   = { key_codes::RIGHT_CONTROL, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_RIGHT_ALT]       = { key_codes::RIGHT_ALT, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_RIGHT_SUPER]     = { key_codes::RIGHT_SUPER, '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_MENU]            = { key_codes::MENU, '\0', '\0' };
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

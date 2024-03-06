#include "KeyCodes.h"
#include "GLFW/glfw3.h"

// KeyCode Keys[KEY_LAST];
char KeyCode::GetCharacter( bool isShifted ) const
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

// #if 0
namespace Platform
{
    enum class KeyCodes : uint16_t
    {
        // Source: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
        KEY_LBUTTON             = 0x01, // Left mouse button
        KEY_RBUTTON             = 0x02, // Right mouse button
        KEY_CANCEL              = 0x03, // Control-break processing
        KEY_MBUTTON             = 0x04, // Middle mouse button
        KEY_XBUTTON1            = 0x05, // X1 mouse button
        KEY_XBUTTON2            = 0x06, // X2 mouse button
        KEY_BACKSPACE           = 0x08, // BACKSPACE key
        KEY_TAB                 = 0x09, // TAB key
        KEY_CLEAR               = 0x0C, // CLEAR key
        KEY_ENTER               = 0x0D, // ENTER key
        KEY_SHIFT               = 0x10, // SHIFT key
        KEY_CONTROL             = 0x11, // CTRL key
        KEY_MENU                = 0x12, // ALT key
        KEY_PAUSE               = 0x13, // PAUSE key
        KEY_CAPITAL             = 0x14, // CAPS LOCK key
        KEY_KANA                = 0x15, // IME Kana mode
        KEY_HANGUL              = 0x15, // IME Hangul mode
        KEY_IME_ON              = 0x16, // IME On
        KEY_JUNJA               = 0x17, // IME Junja mode
        KEY_FINAL               = 0x18, // IME final mode
        KEY_HANJA               = 0x19, // IME Hanja mode
        KEY_KANJI               = 0x19, // IME Kanji mode
        KEY_IME_OFF             = 0x1A, // IME Off
        KEY_ESCAPE              = 0x1B, // ESC key
        KEY_CONVERT             = 0x1C, // IME convert
        KEY_NONCONVERT          = 0x1D, // IME nonconvert
        KEY_ACCEPT              = 0x1E, // IME accept
        KEY_MODECHANGE          = 0x1F, // IME mode change request
        KEY_SPACE               = 0x20, // SPACEBAR
        KEY_PRIOR               = 0x21, // PAGE UP key
        KEY_PAGE_UP             = 0x21, // PAGE UP key
        KEY_NEXT                = 0x22, // PAGE DOWN key
        KEY_PAGE_DOWN           = 0x22, // PAGE DOWN key
        KEY_END                 = 0x23, // END key
        KEY_HOME                = 0x24, // HOME key
        KEY_LEFT                = 0x25, // LEFT ARROW key
        KEY_UP                  = 0x26, // UP ARROW key
        KEY_RIGHT               = 0x27, // RIGHT ARROW key
        KEY_DOWN                = 0x28, // DOWN ARROW key
        KEY_SELECT              = 0x29, // SELECT key
        KEY_PRINT               = 0x2A, // PRINT key
        KEY_EXECUTE             = 0x2B, // EXECUTE key
        KEY_SNAPSHOT            = 0x2C, // PRINT SCREEN key
        KEY_INSERT              = 0x2D, // INS key
        KEY_DELETE              = 0x2E, // DEL key
        KEY_HELP                = 0x2F, // HELP key
        KEY_0                   = 0x30, // 0 key
        KEY_1                   = 0x31, // 1 key
        KEY_2                   = 0x32, // 2 key
        KEY_3                   = 0x33, // 3 key
        KEY_4                   = 0x34, // 4 key
        KEY_5                   = 0x35, // 5 key
        KEY_6                   = 0x36, // 6 key
        KEY_7                   = 0x37, // 7 key
        KEY_8                   = 0x38, // 8 key
        KEY_9                   = 0x39, // 9 key
        KEY_A                   = 0x41, // A key
        KEY_B                   = 0x42, // B key
        KEY_C                   = 0x43, // C key
        KEY_D                   = 0x44, // D key
        KEY_E                   = 0x45, // E key
        KEY_F                   = 0x46, // F key
        KEY_G                   = 0x47, // G key
        KEY_H                   = 0x48, // H key
        KEY_I                   = 0x49, // I key
        KEY_J                   = 0x4A, // J key
        KEY_K                   = 0x4B, // K key
        KEY_L                   = 0x4C, // L key
        KEY_M                   = 0x4D, // M key
        KEY_N                   = 0x4E, // N key
        KEY_O                   = 0x4F, // O key
        KEY_P                   = 0x50, // P key
        KEY_Q                   = 0x51, // Q key
        KEY_R                   = 0x52, // R key
        KEY_S                   = 0x53, // S key
        KEY_T                   = 0x54, // T key
        KEY_U                   = 0x55, // U key
        KEY_V                   = 0x56, // V key
        KEY_W                   = 0x57, // W key
        KEY_X                   = 0x58, // X key
        KEY_Y                   = 0x59, // Y key
        KEY_Z                   = 0x5A, // Z key
        KEY_LWIN                = 0x5B, // Left Windows key
        KEY_RWIN                = 0x5C, // Right Windows key
        KEY_APPS                = 0x5D, // Applications key
        KEY_SLEEP               = 0x5F, // Computer Sleep key
        KEY_NUMPAD_0            = 0x60, // Numeric keypad 0 key
        KEY_NUMPAD_1            = 0x61, // Numeric keypad 1 key
        KEY_NUMPAD_2            = 0x62, // Numeric keypad 2 key
        KEY_NUMPAD_3            = 0x63, // Numeric keypad 3 key
        KEY_NUMPAD_4            = 0x64, // Numeric keypad 4 key
        KEY_NUMPAD_5            = 0x65, // Numeric keypad 5 key
        KEY_NUMPAD_6            = 0x66, // Numeric keypad 6 key
        KEY_NUMPAD_7            = 0x67, // Numeric keypad 7 key
        KEY_NUMPAD_8            = 0x68, // Numeric keypad 8 key
        KEY_NUMPAD_9            = 0x69, // Numeric keypad 9 key
        KEY_NUMPAD_MULTIPLY     = 0x6A, // Multiply key
        KEY_NUMPAD_ADD          = 0x6B, // Add key
        KEY_NUMPAD_SEPARATOR    = 0x6C, // Separator key
        KEY_NUMPAD_SUBTRACT     = 0x6D, // Subtract key
        KEY_NUMPAD_DECIMAL      = 0x6E, // Decimal key
        KEY_NUMPAD_DIVIDE       = 0x6F, // Divide key
        KEY_F1                  = 0x70, // F1 key
        KEY_F2                  = 0x71, // F2 key
        KEY_F3                  = 0x72, // F3 key
        KEY_F4                  = 0x73, // F4 key
        KEY_F5                  = 0x74, // F5 key
        KEY_F6                  = 0x75, // F6 key
        KEY_F7                  = 0x76, // F7 key
        KEY_F8                  = 0x77, // F8 key
        KEY_F9                  = 0x78, // F9 key
        KEY_F10                 = 0x79, // F10 key
        KEY_F11                 = 0x7A, // F11 key
        KEY_F12                 = 0x7B, // F12 key
        KEY_F13                 = 0x7C, // F13 key
        KEY_F14                 = 0x7D, // F14 key
        KEY_F15                 = 0x7E, // F15 key
        KEY_F16                 = 0x7F, // F16 key
        KEY_F17                 = 0x80, // F17 key
        KEY_F18                 = 0x81, // F18 key
        KEY_F19                 = 0x82, // F19 key
        KEY_F20                 = 0x83, // F20 key
        KEY_F21                 = 0x84, // F21 key
        KEY_F22                 = 0x85, // F22 key
        KEY_F23                 = 0x86, // F23 key
        KEY_F24                 = 0x87, // F24 key
        KEY_NUM_LOCK            = 0x90, // NUM LOCK key
        KEY_SCROLL_LOCK         = 0x91, // SCROLL LOCK key
        KEY_LEFT_SHIFT          = 0xA0, // Left SHIFT key
        KEY_RIGHT_SHIFT         = 0xA1, // Right SHIFT key
        KEY_LEFT_CONTROL        = 0xA2, // Left CONTROL key
        KEY_RIGHT_CONTROL       = 0xA3, // Right CONTROL key
        KEY_LEFT_ALT            = 0xA4, // Left ALT key
        KEY_RIGHT_ALT           = 0xA5, // Right ALT key
        KEY_BROWSER_BACK        = 0xA6, // Browser Back key
        KEY_BROWSER_FORWARD     = 0xA7, // Browser Forward key
        KEY_BROWSER_REFRESH     = 0xA8, // Browser Refresh key
        KEY_BROWSER_STOP        = 0xA9, // Browser Stop key
        KEY_BROWSER_SEARCH      = 0xAA, // Browser Search key
        KEY_BROWSER_FAVORITES   = 0xAB, // Browser Favorites key
        KEY_BROWSER_HOME        = 0xAC, // Browser Start and Home key
        KEY_VOLUME_MUTE         = 0xAD, // Volume Mute key
        KEY_VOLUME_DOWN         = 0xAE, // Volume Down key
        KEY_VOLUME_UP           = 0xAF, // Volume Up key
        KEY_MEDIA_NEXT_TRACK    = 0xB0, // Next Track key
        KEY_MEDIA_PREV_TRACK    = 0xB1, // Previous Track key
        KEY_MEDIA_STOP          = 0xB2, // Stop Media key
        KEY_MEDIA_PLAY_PAUSE    = 0xB3, // Play/Pause Media key
        KEY_LAUNCH_MAIL         = 0xB4, // Start Mail key
        KEY_LAUNCH_MEDIA_SELECT = 0xB5, // Select Media key
        KEY_LAUNCH_APP1         = 0xB6, // Start Application 1 key
        KEY_LAUNCH_APP2         = 0xB7, // Start Application 2 key
        KEY_OEM_1               = 0xBA, // Used for miscellaneous characters; For the US standard keyboard, the ;: key
        KEY_SEMICOLON           = 0xBA, // Used for miscellaneous characters; For the US standard keyboard, the ;: key
        KEY_OEM_PLUS            = 0xBB, // For any country/region, the + key
        KEY_EQUAL               = 0xBB, // For any country/region, the + key
        KEY_OEM_COMMA           = 0xBC, // For any country/region, the , key
        KEY_COMMA               = 0xBC, // For any country/region, the , key
        KEY_OEM_MINUS           = 0xBD, // For any country/region, the - key
        KEY_MINUS               = 0xBD, // For any country/region, the - key
        KEY_OEM_PERIOD          = 0xBE, // For any country/region, the . key
        KEY_PERIOD              = 0xBE, // For any country/region, the . key
        KEY_OEM_2               = 0xBF, // Used for miscellaneous characters; For the US standard keyboard, the /? key
        KEY_SLASH               = 0xBF, // Used for miscellaneous characters; For the US standard keyboard, the /? key
        KEY_OEM_3               = 0xC0, // Used for miscellaneous characters; For the US standard keyboard, the `~ key
        KEY_GRAVE_ACCENT        = 0xC0, // Used for miscellaneous characters; For the US standard keyboard, the `~ key
        KEY_OEM_4               = 0xDB, // Used for miscellaneous characters; For the US standard keyboard, the [{ key
        KEY_LEFT_BRACKET        = 0xDB, // Used for miscellaneous characters; For the US standard keyboard, the [{ key
        KEY_OEM_5               = 0xDC, // Used for miscellaneous characters; For the US standard keyboard, the \\| key
        KEY_BACKSLASH           = 0xDC, // Used for miscellaneous characters; For the US standard keyboard, the \\| key
        KEY_OEM_6               = 0xDD, // Used for miscellaneous characters; For the US standard keyboard, the ]} key
        KEY_RIGHT_BRACKET       = 0xDD, // Used for miscellaneous characters; For the US standard keyboard, the ]} key
        KEY_OEM_7               = 0xDE, // Used for miscellaneous characters; For the US standard keyboard, the '" key
        KEY_APOSTROPHE          = 0xDE, // Used for miscellaneous characters; For the US standard keyboard, the '" key
        KEY_OEM_8               = 0xDF, // Used for miscellaneous characters; it can vary by keyboard.
        KEY_OEM_102             = 0xE2, // The <> keys on the US standard keyboard, or the \\| key on the non-US 102-key keyboard
        KEY_PROCESSKEY          = 0xE5, // IME PROCESS key
        KEY_PACKET = 0xE7,    // Used to pass Unicode characters as if they were keystrokes. The KEY_PACKET key is the low word of a
                              // 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in
                              // KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
        KEY_ATTN      = 0xF6, // Attn key
        KEY_CRSEL     = 0xF7, // CrSel key
        KEY_EXSEL     = 0xF8, // ExSel key
        KEY_EREOF     = 0xF9, // Erase EOF key
        KEY_PLAY      = 0xFA, // Play key
        KEY_ZOOM      = 0xFB, // Zoom key
        KEY_NONAME    = 0xFC, // Reserved
        KEY_PA1       = 0xFD, // PA1 key
        KEY_OEM_CLEAR = 0xFE, // Clear key
    }
}
// #endif

void KeyboardHandler::InitKeyCodes()
{
    int controlKeyID                        = 0;
    Keys[Platform::KeyCodes::KEY_DELETE]    = { KeyCodes::DELETE_K, glfwGetKeyScancode( KEY_DELETE ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_ESCAPE]    = { KeyCodes::ESCAPE, glfwGetKeyScancode( KEY_ESCAPE ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_INSERT]    = { KeyCodes::INSERT, glfwGetKeyScancode( KEY_INSERT ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_PAGE_UP]   = { KeyCodes::PAGE_UP, glfwGetKeyScancode( KEY_PAGE_UP ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_PAGE_DOWN] = { KeyCodes::PAGE_DOWN, glfwGetKeyScancode( KEY_PAGE_DOWN ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_HOME]      = { KeyCodes::HOME, glfwGetKeyScancode( KEY_HOME ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_END]       = { KeyCodes::END, glfwGetKeyScancode( KEY_END ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F1]        = { KeyCodes::F1, glfwGetKeyScancode( KEY_F1 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F2]        = { KeyCodes::F2, glfwGetKeyScancode( KEY_F2 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F3]        = { KeyCodes::F3, glfwGetKeyScancode( KEY_F3 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F4]        = { KeyCodes::F4, glfwGetKeyScancode( KEY_F4 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F5]        = { KeyCodes::F5, glfwGetKeyScancode( KEY_F5 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F6]        = { KeyCodes::F6, glfwGetKeyScancode( KEY_F6 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F7]        = { KeyCodes::F7, glfwGetKeyScancode( KEY_F7 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F8]        = { KeyCodes::F8, glfwGetKeyScancode( KEY_F8 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F9]        = { KeyCodes::F9, glfwGetKeyScancode( KEY_F9 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F10]       = { KeyCodes::F10, glfwGetKeyScancode( KEY_F10 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F11]       = { KeyCodes::F11, glfwGetKeyScancode( KEY_F11 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F12]       = { KeyCodes::F12, glfwGetKeyScancode( KEY_F12 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F13]       = { KeyCodes::F13, glfwGetKeyScancode( KEY_F13 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F14]       = { KeyCodes::F14, glfwGetKeyScancode( KEY_F14 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F15]       = { KeyCodes::F15, glfwGetKeyScancode( KEY_F15 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F16]       = { KeyCodes::F16, glfwGetKeyScancode( KEY_F16 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F17]       = { KeyCodes::F17, glfwGetKeyScancode( KEY_F17 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F18]       = { KeyCodes::F18, glfwGetKeyScancode( KEY_F18 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F19]       = { KeyCodes::F19, glfwGetKeyScancode( KEY_F19 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F20]       = { KeyCodes::F20, glfwGetKeyScancode( KEY_F20 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F21]       = { KeyCodes::F21, glfwGetKeyScancode( KEY_F21 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F22]       = { KeyCodes::F22, glfwGetKeyScancode( KEY_F22 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F23]       = { KeyCodes::F23, glfwGetKeyScancode( KEY_F23 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_F24]       = { KeyCodes::F24, glfwGetKeyScancode( KEY_F24 ), '\0', '\0' };
    // Keys[Platform::KeyCodes::KEY_F25]           = { KeyCodes::F25, glfwGetKeyScancode( KEY_F25 ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_SPACE]           = { KeyCodes::SPACE, glfwGetKeyScancode( KEY_SPACE ), ' ', ' ' };
    Keys[Platform::KeyCodes::KEY_APOSTROPHE]      = { KeyCodes::APOSTROPHE, glfwGetKeyScancode( KEY_APOSTROPHE ), '\'', '"' };
    Keys[Platform::KeyCodes::KEY_COMMA]           = { KeyCodes::COMMA, glfwGetKeyScancode( KEY_COMMA ), ',', '<' };
    Keys[Platform::KeyCodes::KEY_MINUS]           = { KeyCodes::MINUS, glfwGetKeyScancode( KEY_MINUS ), '-', '_' };
    Keys[Platform::KeyCodes::KEY_PERIOD]          = { KeyCodes::PERIOD, glfwGetKeyScancode( KEY_PERIOD ), '.', '>' };
    Keys[Platform::KeyCodes::KEY_SLASH]           = { KeyCodes::SLASH, glfwGetKeyScancode( KEY_SLASH ), '/', '?' };
    Keys[Platform::KeyCodes::KEY_SEMICOLON]       = { KeyCodes::SEMICOLON, glfwGetKeyScancode( KEY_SEMICOLON ), ';', ':' };
    Keys[Platform::KeyCodes::KEY_EQUAL]           = { KeyCodes::EQUAL, glfwGetKeyScancode( KEY_EQUAL ), '=', '+' };
    Keys[Platform::KeyCodes::KEY_LEFT_BRACKET]    = { KeyCodes::LEFT_BRACKET, glfwGetKeyScancode( KEY_LEFT_BRACKET ), '[', '{' };
    Keys[Platform::KeyCodes::KEY_BACKSLASH]       = { KeyCodes::BACKSLASH, glfwGetKeyScancode( KEY_BACKSLASH ), '\\', '|' };
    Keys[Platform::KeyCodes::KEY_RIGHT_BRACKET]   = { KeyCodes::RIGHT_BRACKET, glfwGetKeyScancode( KEY_RIGHT_BRACKET ), ']', '}' };
    Keys[Platform::KeyCodes::KEY_GRAVE_ACCENT]    = { KeyCodes::GRAVE_ACCENT, glfwGetKeyScancode( KEY_GRAVE_ACCENT ), '`', '~' };
    Keys[Platform::KeyCodes::KEY_A]               = { KeyCodes::A, glfwGetKeyScancode( KEY_A ), 'a', 'A' };
    Keys[Platform::KeyCodes::KEY_B]               = { KeyCodes::B, glfwGetKeyScancode( KEY_B ), 'b', 'B' };
    Keys[Platform::KeyCodes::KEY_C]               = { KeyCodes::C, glfwGetKeyScancode( KEY_C ), 'c', 'C' };
    Keys[Platform::KeyCodes::KEY_D]               = { KeyCodes::D, glfwGetKeyScancode( KEY_D ), 'd', 'D' };
    Keys[Platform::KeyCodes::KEY_E]               = { KeyCodes::E, glfwGetKeyScancode( KEY_E ), 'e', 'E' };
    Keys[Platform::KeyCodes::KEY_F]               = { KeyCodes::F, glfwGetKeyScancode( KEY_F ), 'f', 'F' };
    Keys[Platform::KeyCodes::KEY_G]               = { KeyCodes::G, glfwGetKeyScancode( KEY_G ), 'g', 'G' };
    Keys[Platform::KeyCodes::KEY_H]               = { KeyCodes::H, glfwGetKeyScancode( KEY_H ), 'h', 'H' };
    Keys[Platform::KeyCodes::KEY_I]               = { KeyCodes::I, glfwGetKeyScancode( KEY_I ), 'i', 'I' };
    Keys[Platform::KeyCodes::KEY_J]               = { KeyCodes::J, glfwGetKeyScancode( KEY_J ), 'j', 'J' };
    Keys[Platform::KeyCodes::KEY_K]               = { KeyCodes::K, glfwGetKeyScancode( KEY_K ), 'k', 'K' };
    Keys[Platform::KeyCodes::KEY_L]               = { KeyCodes::L, glfwGetKeyScancode( KEY_L ), 'l', 'L' };
    Keys[Platform::KeyCodes::KEY_M]               = { KeyCodes::M, glfwGetKeyScancode( KEY_M ), 'm', 'M' };
    Keys[Platform::KeyCodes::KEY_N]               = { KeyCodes::N, glfwGetKeyScancode( KEY_N ), 'n', 'N' };
    Keys[Platform::KeyCodes::KEY_O]               = { KeyCodes::O, glfwGetKeyScancode( KEY_O ), 'o', 'O' };
    Keys[Platform::KeyCodes::KEY_P]               = { KeyCodes::P, glfwGetKeyScancode( KEY_P ), 'p', 'P' };
    Keys[Platform::KeyCodes::KEY_Q]               = { KeyCodes::Q, glfwGetKeyScancode( KEY_Q ), 'q', 'Q' };
    Keys[Platform::KeyCodes::KEY_R]               = { KeyCodes::R, glfwGetKeyScancode( KEY_R ), 'r', 'R' };
    Keys[Platform::KeyCodes::KEY_S]               = { KeyCodes::S, glfwGetKeyScancode( KEY_S ), 's', 'S' };
    Keys[Platform::KeyCodes::KEY_T]               = { KeyCodes::T, glfwGetKeyScancode( KEY_T ), 't', 'T' };
    Keys[Platform::KeyCodes::KEY_U]               = { KeyCodes::U, glfwGetKeyScancode( KEY_U ), 'u', 'U' };
    Keys[Platform::KeyCodes::KEY_V]               = { KeyCodes::V, glfwGetKeyScancode( KEY_V ), 'v', 'V' };
    Keys[Platform::KeyCodes::KEY_W]               = { KeyCodes::W, glfwGetKeyScancode( KEY_W ), 'w', 'W' };
    Keys[Platform::KeyCodes::KEY_X]               = { KeyCodes::X, glfwGetKeyScancode( KEY_X ), 'x', 'X' };
    Keys[Platform::KeyCodes::KEY_Y]               = { KeyCodes::Y, glfwGetKeyScancode( KEY_Y ), 'y', 'Y' };
    Keys[Platform::KeyCodes::KEY_Z]               = { KeyCodes::Z, glfwGetKeyScancode( KEY_Z ), 'z', 'Z' };
    Keys[Platform::KeyCodes::KEY_0]               = { KeyCodes::KEY_0, glfwGetKeyScancode( KEY_0 ), '0', ')' };
    Keys[Platform::KeyCodes::KEY_1]               = { KeyCodes::KEY_1, glfwGetKeyScancode( KEY_1 ), '1', '!' };
    Keys[Platform::KeyCodes::KEY_2]               = { KeyCodes::KEY_2, glfwGetKeyScancode( KEY_2 ), '2', '@' };
    Keys[Platform::KeyCodes::KEY_3]               = { KeyCodes::KEY_3, glfwGetKeyScancode( KEY_3 ), '3', '#' };
    Keys[Platform::KeyCodes::KEY_4]               = { KeyCodes::KEY_4, glfwGetKeyScancode( KEY_4 ), '4', '$' };
    Keys[Platform::KeyCodes::KEY_5]               = { KeyCodes::KEY_5, glfwGetKeyScancode( KEY_5 ), '5', '%' };
    Keys[Platform::KeyCodes::KEY_6]               = { KeyCodes::KEY_6, glfwGetKeyScancode( KEY_6 ), '6', '^' };
    Keys[Platform::KeyCodes::KEY_7]               = { KeyCodes::KEY_7, glfwGetKeyScancode( KEY_7 ), '7', '&' };
    Keys[Platform::KeyCodes::KEY_8]               = { KeyCodes::KEY_8, glfwGetKeyScancode( KEY_8 ), '8', '*' };
    Keys[Platform::KeyCodes::KEY_9]               = { KeyCodes::KEY_9, glfwGetKeyScancode( KEY_9 ), '9', '(' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_0]        = { KeyCodes::KEYPAD_0, glfwGetKeyScancode( KEY_KP_0 ), '0', '0' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_1]        = { KeyCodes::KEYPAD_1, glfwGetKeyScancode( KEY_KP_1 ), '1', '1' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_2]        = { KeyCodes::KEYPAD_2, glfwGetKeyScancode( KEY_KP_2 ), '2', '2' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_3]        = { KeyCodes::KEYPAD_3, glfwGetKeyScancode( KEY_KP_3 ), '3', '3' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_4]        = { KeyCodes::KEYPAD_4, glfwGetKeyScancode( KEY_KP_4 ), '4', '4' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_5]        = { KeyCodes::KEYPAD_5, glfwGetKeyScancode( KEY_KP_5 ), '5', '5' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_6]        = { KeyCodes::KEYPAD_6, glfwGetKeyScancode( KEY_KP_6 ), '6', '6' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_7]        = { KeyCodes::KEYPAD_7, glfwGetKeyScancode( KEY_KP_7 ), '7', '7' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_8]        = { KeyCodes::KEYPAD_8, glfwGetKeyScancode( KEY_KP_8 ), '8', '8' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_9]        = { KeyCodes::KEYPAD_9, glfwGetKeyScancode( KEY_KP_9 ), '9', '9' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_DECIMAL]  = { KeyCodes::KEYPAD_DECIMAL, glfwGetKeyScancode( KEY_KP_DECIMAL ), '.', '.' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_DIVIDE]   = { KeyCodes::KEYPAD_DIVIDE, glfwGetKeyScancode( KEY_KP_DIVIDE ), '/', '/' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_MULTIPLY] = { KeyCodes::KEYPAD_MULTIPLY, glfwGetKeyScancode( KEY_KP_MULTIPLY ), '*', '*' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_SUBTRACT] = { KeyCodes::KEYPAD_SUBTRACT, glfwGetKeyScancode( KEY_KP_SUBTRACT ), '-', '-' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_ADD]      = { KeyCodes::KEYPAD_ADD, glfwGetKeyScancode( KEY_KP_ADD ), '+', '+' };
    Keys[Platform::KeyCodes::KEY_NUMPAD_EQUAL]    = { KeyCodes::KEYPAD_EQUAL, glfwGetKeyScancode( KEY_KP_EQUAL ), '=', '=' };
    Keys[Platform::KeyCodes::KEY_ENTER]           = { KeyCodes::ENTER, glfwGetKeyScancode( KEY_ENTER ), '\n', '\0' };
    Keys[Platform::KeyCodes::KEY_TAB]             = { KeyCodes::TAB, glfwGetKeyScancode( KEY_TAB ), '\t', '\0' };
    Keys[Platform::KeyCodes::KEY_BACKSPACE]       = { KeyCodes::BACKSPACE, glfwGetKeyScancode( KEY_BACKSPACE ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_RIGHT]           = { KeyCodes::RIGHT, glfwGetKeyScancode( KEY_RIGHT ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_LEFT]            = { KeyCodes::LEFT, glfwGetKeyScancode( KEY_LEFT ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_DOWN]            = { KeyCodes::DOWN, glfwGetKeyScancode( KEY_DOWN ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_UP]              = { KeyCodes::UP, glfwGetKeyScancode( KEY_UP ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_CAPS_LOCK]       = { KeyCodes::CAPS_LOCK, glfwGetKeyScancode( KEY_CAPS_LOCK ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_SCROLL_LOCK]     = { KeyCodes::SCROLL_LOCK, glfwGetKeyScancode( KEY_SCROLL_LOCK ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_NUM_LOCK]        = { KeyCodes::NUM_LOCK, glfwGetKeyScancode( KEY_NUM_LOCK ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_PRINT_SCREEN]    = { KeyCodes::PRINT_SCREEN, glfwGetKeyScancode( KEY_PRINT_SCREEN ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_PAUSE]           = { KeyCodes::PAUSE, glfwGetKeyScancode( KEY_PAUSE ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_KP_ENTER]        = { KeyCodes::KEYPAD_ENTER, glfwGetKeyScancode( KEY_KP_ENTER ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_LEFT_SHIFT]      = { KeyCodes::LEFT_SHIFT, glfwGetKeyScancode( KEY_LEFT_SHIFT ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_LEFT_CONTROL]    = { KeyCodes::LEFT_CONTROL, glfwGetKeyScancode( KEY_LEFT_CONTROL ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_LEFT_ALT]        = { KeyCodes::LEFT_ALT, glfwGetKeyScancode( KEY_LEFT_ALT ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_LEFT_SUPER]      = { KeyCodes::LEFT_SUPER, glfwGetKeyScancode( KEY_LEFT_SUPER ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_RIGHT_SHIFT]     = { KeyCodes::RIGHT_SHIFT, glfwGetKeyScancode( KEY_RIGHT_SHIFT ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_RIGHT_CONTROL]   = { KeyCodes::RIGHT_CONTROL, glfwGetKeyScancode( KEY_RIGHT_CONTROL ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_RIGHT_ALT]       = { KeyCodes::RIGHT_ALT, glfwGetKeyScancode( KEY_RIGHT_ALT ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_RIGHT_SUPER]     = { KeyCodes::RIGHT_SUPER, glfwGetKeyScancode( KEY_RIGHT_SUPER ), '\0', '\0' };
    Keys[Platform::KeyCodes::KEY_MENU]            = { KeyCodes::MENU, glfwGetKeyScancode( KEY_MENU ), '\0', '\0' };
    // clang-format off
}

uint32_t KeyboardHandler::GetModifierState(int mods)
{
    uint32_t modifiers = 0;

    if(mods & GLFW_MOD_SHIFT)
        modifiers |= (1 << static_cast<uint32_t>(Modifiers::SHIFT));

    if(mods & GLFW_MOD_CONTROL)
        modifiers |= (1 << static_cast<uint32_t>(Modifiers::CTRL));

    if(mods & GLFW_MOD_ALT)
        modifiers |= (1 << static_cast<uint32_t>(Modifiers::ALT));

    if(mods & GLFW_MOD_SUPER)
        modifiers |= (1 << static_cast<uint32_t>(Modifiers::SUPER));

    return modifiers;
}

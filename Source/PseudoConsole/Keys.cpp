// The MIT License (MIT)

// Copyright (c) 2020 Fredrik A. Kristiansen

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

#include "Keys.h"
#include "Core/KeyCodes.h"

ImGuiKeyMap::ImGuiKeyMap( const Key keys[], size_t keysLen, const Key platformKeys[], size_t platformKeysLen,
                          const Shortcut shortcuts[], size_t shortcutsLen )
{
//    for( size_t i = 0; i < keysLen; i++ )
//    {
//        auto &e = m_keyMap[keys[i].keysym];
//        e.push_back( { keys[i].mask, keys[i].string, keys[i].appkey, keys[i].appcursor } );
//    }
//
//    for( size_t i = 0; i < platformKeysLen; i++ )
//    {
//        auto &e = m_platformKeyMap[platformKeys[i].keysym];
//        e.push_back( { platformKeys[i].mask, platformKeys[i].string, platformKeys[i].appkey, platformKeys[i].appcursor } );
//    }
//
//    for( size_t i = 0; i < shortcutsLen; i++ )
//    {
//        auto &e = m_shortcuts[shortcuts[i].keysym];
//        e.push_back( { shortcuts[i].mask, shortcuts[i].action, shortcuts[i].appkey, shortcuts[i].appcursor } );
//    }
}

// using ShortcutAction = Hexe::Terminal::ShortcutAction;

constexpr int MOD_NONE           = 0;
constexpr int MOD_SHIFT          = ImGuiMod_Shift;
constexpr int MOD_ALT_SHIFT      = ImGuiMod_Shift | ImGuiMod_Alt;
constexpr int MOD_ALT            = ImGuiMod_Alt;
constexpr int MOD_SUPER          = ImGuiMod_Super;
constexpr int MOD_CTRL           = ImGuiMod_Ctrl;
constexpr int MOD_CTRL_SHIFT     = ImGuiMod_Shift | ImGuiMod_Ctrl;
constexpr int MOD_CTRL_ALT       = ImGuiMod_Alt | ImGuiMod_Ctrl;
constexpr int MOD_CTRL_ALT_SHIFT = ImGuiMod_Shift | ImGuiMod_Ctrl | ImGuiMod_Alt;

static Shortcut shortcuts[] = { { KeyCodes::INSERT, MOD_SHIFT, ShortcutAction::PASTE, 0, 0 } };
// clang-format off
static Key keys[] = {
    /* keysym               mask                string       appkey appcursor */
    { KeyCodes::KEYPAD_ENTER, MOD_ANY,            "\x1BOM",    +2,  0 },
    { KeyCodes::KEYPAD_ENTER, MOD_ANY,            "\r",        -1,  0 },
    { KeyCodes::UP,           MOD_SHIFT,          "\x1B[1;2A",  0,  0 },
    { KeyCodes::UP,           MOD_ALT,            "\x1B[1;3A",  0,  0 },
    { KeyCodes::UP,           MOD_ALT_SHIFT,      "\x1B[1;4A",  0,  0 },
    { KeyCodes::UP,           MOD_CTRL,           "\x1B[1;5A",  0,  0 },
    { KeyCodes::UP,           MOD_CTRL_SHIFT,     "\x1B[1;6A",  0,  0 },
    { KeyCodes::UP,           MOD_CTRL_ALT,       "\x1B[1;7A",  0,  0 },
    { KeyCodes::UP,           MOD_CTRL_ALT_SHIFT, "\x1B[1;8A",  0,  0 },
    { KeyCodes::UP,           MOD_ANY,            "\x1B[A",     0, -1 },
    { KeyCodes::UP,           MOD_ANY,            "\x1BOA",     0, +1 },
    { KeyCodes::DOWN,         MOD_SHIFT,          "\x1B[1;2B",  0,  0 },
    { KeyCodes::DOWN,         MOD_ALT,            "\x1B[1;3B",  0,  0 },
    { KeyCodes::DOWN,         MOD_ALT_SHIFT,      "\x1B[1;4B",  0,  0 },
    { KeyCodes::DOWN,         MOD_CTRL,           "\x1B[1;5B",  0,  0 },
    { KeyCodes::DOWN,         MOD_CTRL_SHIFT,     "\x1B[1;6B",  0,  0 },
    { KeyCodes::DOWN,         MOD_CTRL_ALT,       "\x1B[1;7B",  0,  0 },
    { KeyCodes::DOWN,         MOD_CTRL_ALT_SHIFT, "\x1B[1;8B",  0,  0 },
    { KeyCodes::DOWN,         MOD_ANY,            "\x1B[B",     0, -1 },
    { KeyCodes::DOWN,         MOD_ANY,            "\x1BOB",     0, +1 },
    { KeyCodes::LEFT,         MOD_SHIFT,          "\x1B[1;2D",  0,  0 },
    { KeyCodes::LEFT,         MOD_ALT,            "\x1B[1;3D",  0,  0 },
    { KeyCodes::LEFT,         MOD_ALT_SHIFT,      "\x1B[1;4D",  0,  0 },
    { KeyCodes::LEFT,         MOD_CTRL,           "\x1B[1;5D",  0,  0 },
    { KeyCodes::LEFT,         MOD_CTRL_SHIFT,     "\x1B[1;6D",  0,  0 },
    { KeyCodes::LEFT,         MOD_CTRL_ALT,       "\x1B[1;7D",  0,  0 },
    { KeyCodes::LEFT,         MOD_CTRL_ALT_SHIFT, "\x1B[1;8D",  0,  0 },
    { KeyCodes::LEFT,         MOD_ANY,            "\x1B[D",     0, -1 },
    { KeyCodes::LEFT,         MOD_ANY,            "\x1BOD",     0, +1 },
    { KeyCodes::RIGHT,        MOD_SHIFT,          "\x1B[1;2C",  0,  0 },
    { KeyCodes::RIGHT,        MOD_ALT,            "\x1B[1;3C",  0,  0 },
    { KeyCodes::RIGHT,        MOD_ALT_SHIFT,      "\x1B[1;4C",  0,  0 },
    { KeyCodes::RIGHT,        MOD_CTRL,           "\x1B[1;5C",  0,  0 },
    { KeyCodes::RIGHT,        MOD_CTRL_SHIFT,     "\x1B[1;6C",  0,  0 },
    { KeyCodes::RIGHT,        MOD_CTRL_ALT,       "\x1B[1;7C",  0,  0 },
    { KeyCodes::RIGHT,        MOD_CTRL_ALT_SHIFT, "\x1B[1;8C",  0,  0 },
    { KeyCodes::RIGHT,        MOD_ANY,            "\x1B[C",     0, -1 },
    { KeyCodes::RIGHT,        MOD_ANY,            "\x1BOC",     0, +1 },
    { KeyCodes::TAB,          MOD_SHIFT,          "\x1B[Z",     0,  0 },
    { KeyCodes::TAB,          MOD_ANY,            "\t",         0,  0 },
    { KeyCodes::ENTER,        MOD_ALT,            "\x1B\r",     0,  0 },
    { KeyCodes::ENTER,        MOD_ANY,            "\r",         0,  0 },
    { KeyCodes::INSERT,       MOD_SHIFT,          "\x1B[4l",   -1,  0 },
    { KeyCodes::INSERT,       MOD_SHIFT,          "\x1B[2;2~", +1,  0 },
    { KeyCodes::INSERT,       MOD_CTRL,           "\x1B[L",    -1,  0 },
    { KeyCodes::INSERT,       MOD_CTRL,           "\x1B[2;5~", +1,  0 },
    { KeyCodes::INSERT,       MOD_ANY,            "\x1B[4h",   -1,  0 },
    { KeyCodes::INSERT,       MOD_ANY,            "\x1B[2~",   +1,  0 },
    { KeyCodes::DELETE,       MOD_CTRL,           "\x1B[M",    -1,  0 },
    { KeyCodes::DELETE,       MOD_CTRL,           "\x1B[3;5~", +1,  0 },
    { KeyCodes::DELETE,       MOD_SHIFT,          "\x1B[2K",   -1,  0 },
    { KeyCodes::DELETE,       MOD_SHIFT,          "\x1B[3;2~", +1,  0 },
    { KeyCodes::DELETE,       MOD_ANY,            "\x1B[P",    -1,  0 },
    { KeyCodes::DELETE,       MOD_ANY,            "\x1B[3~",   +1,  0 },
    { KeyCodes::BACKSPACE,    MOD_NONE,           "\177",       0,  0 },
    { KeyCodes::BACKSPACE,    MOD_ALT,            "\x1B\177",   0,  0 },
    { KeyCodes::HOME,         MOD_SHIFT,          "\x1B[2J",    0, -1 },
    { KeyCodes::HOME,         MOD_SHIFT,          "\x1B[1;2H",  0, +1 },
    { KeyCodes::HOME,         MOD_ANY,            "\x1B[H",     0, -1 },
    { KeyCodes::HOME,         MOD_ANY,            "\x1B[1~",    0, +1 },
    { KeyCodes::END,          MOD_CTRL,           "\x1B[J",    -1,  0 },
    { KeyCodes::END,          MOD_CTRL,           "\x1B[1;5F", +1,  0 },
    { KeyCodes::END,          MOD_SHIFT,          "\x1B[K",    -1,  0 },
    { KeyCodes::END,          MOD_SHIFT,          "\x1B[1;2F", +1,  0 },
    { KeyCodes::END,          MOD_ANY,            "\x1B[4~",    0,  0 },
    { KeyCodes::ESCAPE,       MOD_ANY,            "\x1B",       0,  0 },
    { KeyCodes::PAGE_UP,      MOD_NONE,           "\x1B[5~",    0,  0 },
    { KeyCodes::PAGE_DOWN,    MOD_NONE,           "\x1B[6~",    0,  0 },
};

static Key platformKeys[] = {
    { KeyCodes::PAGE_UP,           MOD_CTRL,     "\x1B[5;5~",  0, 0 },
    { KeyCodes::PAGE_UP,           MOD_CTRL,     "\x1B[5;5~",  0, 0 },
    { KeyCodes::PAGE_UP,           MOD_SHIFT,    "\x1B[5;2~",  0, 0 },
    { KeyCodes::PAGE_UP,           MOD_ANY,      "\x1B[5~",    0, 0 },
    { KeyCodes::BACKSPACE,         MOD_CTRL,     "\x1B[M",    -1, 0 },
    { KeyCodes::BACKSPACE,         MOD_CTRL,     "\x1B[3;5~", +1, 0 },
    { KeyCodes::BACKSPACE,         MOD_SHIFT,    "\x1B[2K",   -1, 0 },
    { KeyCodes::BACKSPACE,         MOD_SHIFT,    "\x1B[3;2~", +1, 0 },
    { KeyCodes::BACKSPACE,         MOD_ANY,      "\x1B[P",    -1, 0 },
    { KeyCodes::BACKSPACE,         MOD_ANY,      "\x1B[3~",   +1, 0 },
    { KeyCodes::KEYPAD_SUBTRACT,   MOD_ANY,      "\x1BOm",    +2, 0 },
    { KeyCodes::KEYPAD_DECIMAL,    MOD_ANY,      "\x1BOn",    +2, 0 },
    { KeyCodes::KEYPAD_DIVIDE,     MOD_ANY,      "\x1BOo",    +2, 0 },
    { KeyCodes::KEYPAD_MULTIPLY,   MOD_ANY,      "\x1BOj",    +2, 0 },
    { KeyCodes::KEYPAD_ADD,        MOD_ANY,      "\x1BOk",    +2, 0 },
    { KeyCodes::F1,                MOD_NONE,     "\x1BOP",     0, 0 },
    { KeyCodes::F1, /* F13 */      MOD_SHIFT,    "\x1B[1;2P",  0, 0 },
    { KeyCodes::F1, /* F25 */      MOD_CTRL,     "\x1B[1;5P",  0, 0 },
    { KeyCodes::F1, /* F37 */      MOD_SUPER,    "\x1B[1;6P",  0, 0 },
    { KeyCodes::F1, /* F49 */      MOD_ALT,      "\x1B[1;3P",  0, 0 },
    { KeyCodes::F1, /* F61 */      MOD_CTRL_ALT, "\x1B[1;4P",  0, 0 },
    { KeyCodes::F2,                MOD_NONE,     "\x1BOQ",     0, 0 },
    { KeyCodes::F2, /* F14 */      MOD_SHIFT,    "\x1B[1;2Q",  0, 0 },
    { KeyCodes::F2, /* F26 */      MOD_CTRL,     "\x1B[1;5Q",  0, 0 },
    { KeyCodes::F2, /* F38 */      MOD_SUPER,    "\x1B[1;6Q",  0, 0 },
    { KeyCodes::F2, /* F50 */      MOD_ALT,      "\x1B[1;3Q",  0, 0 },
    { KeyCodes::F2, /* F62 */      MOD_CTRL_ALT, "\x1B[1;4Q",  0, 0 },
    { KeyCodes::F3,                MOD_NONE,     "\x1BOR",     0, 0 },
    { KeyCodes::F3, /* F15 */      MOD_SHIFT,    "\x1B[1;2R",  0, 0 },
    { KeyCodes::F3, /* F27 */      MOD_CTRL,     "\x1B[1;5R",  0, 0 },
    { KeyCodes::F3, /* F39 */      MOD_SUPER,    "\x1B[1;6R",  0, 0 },
    { KeyCodes::F3, /* F51 */      MOD_ALT,      "\x1B[1;3R",  0, 0 },
    { KeyCodes::F3, /* F63 */      MOD_CTRL_ALT, "\x1B[1;4R",  0, 0 },
    { KeyCodes::F4,                MOD_NONE,     "\x1BOS",     0, 0 },
    { KeyCodes::F4, /* F16 */      MOD_SHIFT,    "\x1B[1;2S",  0, 0 },
    { KeyCodes::F4, /* F28 */      MOD_CTRL,     "\x1B[1;5S",  0, 0 },
    { KeyCodes::F4, /* F40 */      MOD_SUPER,    "\x1B[1;6S",  0, 0 },
    { KeyCodes::F4, /* F52 */      MOD_ALT,      "\x1B[1;3S",  0, 0 },
    { KeyCodes::F5,                MOD_NONE,     "\x1B[15~",   0, 0 },
    { KeyCodes::F5, /* F17 */      MOD_SHIFT,    "\x1B[15;2~", 0, 0 },
    { KeyCodes::F5, /* F29 */      MOD_CTRL,     "\x1B[15;5~", 0, 0 },
    { KeyCodes::F5, /* F41 */      MOD_SUPER,    "\x1B[15;6~", 0, 0 },
    { KeyCodes::F5, /* F53 */      MOD_ALT,      "\x1B[15;3~", 0, 0 },
    { KeyCodes::F6,                MOD_NONE,     "\x1B[17~",   0, 0 },
    { KeyCodes::F6, /* F18 */      MOD_SHIFT,    "\x1B[17;2~", 0, 0 },
    { KeyCodes::F6, /* F30 */      MOD_CTRL,     "\x1B[17;5~", 0, 0 },
    { KeyCodes::F6, /* F42 */      MOD_SUPER,    "\x1B[17;6~", 0, 0 },
    { KeyCodes::F6, /* F54 */      MOD_ALT,      "\x1B[17;3~", 0, 0 },
    { KeyCodes::F7,                MOD_NONE,     "\x1B[18~",   0, 0 },
    { KeyCodes::F7, /* F19 */      MOD_SHIFT,    "\x1B[18;2~", 0, 0 },
    { KeyCodes::F7, /* F31 */      MOD_CTRL,     "\x1B[18;5~", 0, 0 },
    { KeyCodes::F7, /* F43 */      MOD_SUPER,    "\x1B[18;6~", 0, 0 },
    { KeyCodes::F7, /* F55 */      MOD_ALT,      "\x1B[18;3~", 0, 0 },
    { KeyCodes::F8,                MOD_NONE,     "\x1B[19~",   0, 0 },
    { KeyCodes::F8, /* F20 */      MOD_SHIFT,    "\x1B[19;2~", 0, 0 },
    { KeyCodes::F8, /* F32 */      MOD_CTRL,     "\x1B[19;5~", 0, 0 },
    { KeyCodes::F8, /* F44 */      MOD_SUPER,    "\x1B[19;6~", 0, 0 },
    { KeyCodes::F8, /* F56 */      MOD_ALT,      "\x1B[19;3~", 0, 0 },
    { KeyCodes::F9,                MOD_NONE,     "\x1B[20~",   0, 0 },
    { KeyCodes::F9, /* F21 */      MOD_SHIFT,    "\x1B[20;2~", 0, 0 },
    { KeyCodes::F9, /* F33 */      MOD_CTRL,     "\x1B[20;5~", 0, 0 },
    { KeyCodes::F9, /* F45 */      MOD_SUPER,    "\x1B[20;6~", 0, 0 },
    { KeyCodes::F9, /* F57 */      MOD_ALT,      "\x1B[20;3~", 0, 0 },
    { KeyCodes::F10,               MOD_NONE,     "\x1B[21~",   0, 0 },
    { KeyCodes::F10, /* F22 */     MOD_SHIFT,    "\x1B[21;2~", 0, 0 },
    { KeyCodes::F10, /* F34 */     MOD_CTRL,     "\x1B[21;5~", 0, 0 },
    { KeyCodes::F10, /* F46 */     MOD_SUPER,    "\x1B[21;6~", 0, 0 },
    { KeyCodes::F10, /* F58 */     MOD_ALT,      "\x1B[21;3~", 0, 0 },
    { KeyCodes::F11,               MOD_NONE,     "\x1B[23~",   0, 0 },
    { KeyCodes::F11, /* F23 */     MOD_SHIFT,    "\x1B[23;2~", 0, 0 },
    { KeyCodes::F11, /* F35 */     MOD_CTRL,     "\x1B[23;5~", 0, 0 },
    { KeyCodes::F11, /* F47 */     MOD_SUPER,    "\x1B[23;6~", 0, 0 },
    { KeyCodes::F11, /* F59 */     MOD_ALT,      "\x1B[23;3~", 0, 0 },
    { KeyCodes::F12,               MOD_NONE,     "\x1B[24~",   0, 0 },
    { KeyCodes::F12, /* F24 */     MOD_SHIFT,    "\x1B[24;2~", 0, 0 },
    { KeyCodes::F12, /* F36 */     MOD_CTRL,     "\x1B[24;5~", 0, 0 },
    { KeyCodes::F12, /* F48 */     MOD_SUPER,    "\x1B[24;6~", 0, 0 },
    { KeyCodes::F12, /* F60 */     MOD_ALT,      "\x1B[24;3~", 0, 0 },
    { KeyCodes::F13,               MOD_NONE,     "\x1B[1;2P",  0, 0 },
    { KeyCodes::F14,               MOD_NONE,     "\x1B[1;2Q",  0, 0 },
    { KeyCodes::F15,               MOD_NONE,     "\x1B[1;2R",  0, 0 },
    { KeyCodes::F16,               MOD_NONE,     "\x1B[1;2S",  0, 0 },
    { KeyCodes::F17,               MOD_NONE,     "\x1B[15;2~", 0, 0 },
    { KeyCodes::F18,               MOD_NONE,     "\x1B[17;2~", 0, 0 },
    { KeyCodes::F19,               MOD_NONE,     "\x1B[18;2~", 0, 0 },
    { KeyCodes::F20,               MOD_NONE,     "\x1B[19;2~", 0, 0 },
    { KeyCodes::F21,               MOD_NONE,     "\x1B[20;2~", 0, 0 },
    { KeyCodes::F22,               MOD_NONE,     "\x1B[21;2~", 0, 0 },
    { KeyCodes::F23,               MOD_NONE,     "\x1B[23;2~", 0, 0 },
    { KeyCodes::F24,               MOD_NONE,     "\x1B[24;2~", 0, 0 },
    { KeyCodes::KEYPAD_0,          MOD_ANY,      "\x1BOp",    +2, 0 },
    { KeyCodes::KEYPAD_1,          MOD_ANY,      "\x1BOq",    +2, 0 },
    { KeyCodes::KEYPAD_2,          MOD_ANY,      "\x1BOr",    +2, 0 },
    { KeyCodes::KEYPAD_3,          MOD_ANY,      "\x1BOs",    +2, 0 },
    { KeyCodes::KEYPAD_4,          MOD_ANY,      "\x1BOt",    +2, 0 },
    { KeyCodes::KEYPAD_5,          MOD_ANY,      "\x1BOu",    +2, 0 },
    { KeyCodes::KEYPAD_6,          MOD_ANY,      "\x1BOv",    +2, 0 },
    { KeyCodes::KEYPAD_7,          MOD_ANY,      "\x1BOw",    +2, 0 },
    { KeyCodes::KEYPAD_8,          MOD_ANY,      "\x1BOx",    +2, 0 },
    { KeyCodes::KEYPAD_9,          MOD_ANY,      "\x1BOy",    +2, 0 }
};
// clang-format on
//
ImGuiKeyMap ImGuiTerminalKeyMap{ keys,         ( sizeof( keys ) / sizeof( keys[0] ) ),
                                 platformKeys, ( sizeof( platformKeys ) / sizeof( platformKeys[0] ) ),
                                 shortcuts,    ( sizeof( shortcuts ) / sizeof( shortcuts[0] ) ) };

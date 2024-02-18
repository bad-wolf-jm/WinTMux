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

#include "ControlSequences.h"
#include "KeyCodes.h"

// using ShortcutAction = Hexe::Terminal::ShortcutAction;

static Shortcut shortcuts[] = { { KeyCodes::INSERT, Modifiers::SHIFT, ShortcutAction::PASTE, 0, 0 } };
// clang-format off
static Key keys[] = {
    /* keysym               mask                string       appkey appcursor */
    // { KeyCodes::KEYPAD_ENTER,      ANY,            "\x1BOM",    +2,  0 },
    { KeyCodes::KEYPAD_ENTER,      Modifiers::ANY,            "\r",        -1,  0 },
    { KeyCodes::UP,                Modifiers::SHIFT,          "\x1B[1;2A",  0,  0 },
    { KeyCodes::UP,                Modifiers::ALT,            "\x1B[1;3A",  0,  0 },
    { KeyCodes::UP,                Modifiers::ALT_SHIFT,      "\x1B[1;4A",  0,  0 },
    { KeyCodes::UP,                Modifiers::CTRL,           "\x1B[1;5A",  0,  0 },
    { KeyCodes::UP,                Modifiers::CTRL_SHIFT,     "\x1B[1;6A",  0,  0 },
    { KeyCodes::UP,                Modifiers::CTRL_ALT,       "\x1B[1;7A",  0,  0 },
    { KeyCodes::UP,                Modifiers::CTRL_ALT_SHIFT, "\x1B[1;8A",  0,  0 },
    { KeyCodes::UP,                Modifiers::ANY,            "\x1B[A",     0, -1 },
    // { KeyCodes::UP,             Modifiers::   ANY,            "\x1BOA",     0, +1 },
    { KeyCodes::DOWN,              Modifiers::SHIFT,          "\x1B[1;2B",  0,  0 },
    { KeyCodes::DOWN,              Modifiers::ALT,            "\x1B[1;3B",  0,  0 },
    { KeyCodes::DOWN,              Modifiers::ALT_SHIFT,      "\x1B[1;4B",  0,  0 },
    { KeyCodes::DOWN,              Modifiers::CTRL,           "\x1B[1;5B",  0,  0 },
    { KeyCodes::DOWN,              Modifiers::CTRL_SHIFT,     "\x1B[1;6B",  0,  0 },
    { KeyCodes::DOWN,              Modifiers::CTRL_ALT,       "\x1B[1;7B",  0,  0 },
    { KeyCodes::DOWN,              Modifiers::CTRL_ALT_SHIFT, "\x1B[1;8B",  0,  0 },
    { KeyCodes::DOWN,              Modifiers::ANY,            "\x1B[B",     0, -1 },
    // { KeyCodes::DOWN,           Modifiers::   ANY,            "\x1BOB",     0, +1 },
    { KeyCodes::LEFT,              Modifiers::SHIFT,          "\x1B[1;2D",  0,  0 },
    { KeyCodes::LEFT,              Modifiers::ALT,            "\x1B[1;3D",  0,  0 },
    { KeyCodes::LEFT,              Modifiers::ALT_SHIFT,      "\x1B[1;4D",  0,  0 },
    { KeyCodes::LEFT,              Modifiers::CTRL,           "\x1B[1;5D",  0,  0 },
    { KeyCodes::LEFT,              Modifiers::CTRL_SHIFT,     "\x1B[1;6D",  0,  0 },
    { KeyCodes::LEFT,              Modifiers::CTRL_ALT,       "\x1B[1;7D",  0,  0 },
    { KeyCodes::LEFT,              Modifiers::CTRL_ALT_SHIFT, "\x1B[1;8D",  0,  0 },
    { KeyCodes::LEFT,              Modifiers::ANY,            "\x1B[D",     0, -1 },
    // { KeyCodes::LEFT,           Modifiers::   ANY,            "\x1BOD",     0, +1 },
    { KeyCodes::RIGHT,             Modifiers::SHIFT,          "\x1B[1;2C",  0,  0 },
    { KeyCodes::RIGHT,             Modifiers::ALT,            "\x1B[1;3C",  0,  0 },
    { KeyCodes::RIGHT,             Modifiers::ALT_SHIFT,      "\x1B[1;4C",  0,  0 },
    { KeyCodes::RIGHT,             Modifiers::CTRL,           "\x1B[1;5C",  0,  0 },
    { KeyCodes::RIGHT,             Modifiers::CTRL_SHIFT,     "\x1B[1;6C",  0,  0 },
    { KeyCodes::RIGHT,             Modifiers::CTRL_ALT,       "\x1B[1;7C",  0,  0 },
    { KeyCodes::RIGHT,             Modifiers::CTRL_ALT_SHIFT, "\x1B[1;8C",  0,  0 },
    { KeyCodes::RIGHT,             Modifiers::ANY,            "\x1B[C",     0, -1 },
    // { KeyCodes::RIGHT,          Modifiers::   ANY,            "\x1BOC",     0, +1 },
    { KeyCodes::TAB,               Modifiers::SHIFT,          "\x1B[Z",     0,  0 },
    { KeyCodes::TAB,               Modifiers::ANY,            "\t",         0,  0 },
    { KeyCodes::ENTER,             Modifiers::ALT,            "\x1B\r",     0,  0 },
    { KeyCodes::ENTER,             Modifiers::ANY,            "\r",         0,  0 },
    { KeyCodes::INSERT,            Modifiers::SHIFT,          "\x1B[4l",   -1,  0 },
    // { KeyCodes::INSERT,         Modifiers::   SHIFT,          "\x1B[2;2~", +1,  0 },
    { KeyCodes::INSERT,            Modifiers::CTRL,           "\x1B[L",    -1,  0 },
    // { KeyCodes::INSERT,         Modifiers::   CTRL,           "\x1B[2;5~", +1,  0 },
    { KeyCodes::INSERT,            Modifiers::ANY,            "\x1B[4h",   -1,  0 },
    // { KeyCodes::INSERT,         Modifiers::   ANY,            "\x1B[2~",   +1,  0 },
    { KeyCodes::DELETE,            Modifiers::CTRL,           "\x1B[M",    -1,  0 },
    // { KeyCodes::DELETE,         Modifiers::   CTRL,           "\x1B[3;5~", +1,  0 },
    { KeyCodes::DELETE,            Modifiers::SHIFT,          "\x1B[2K",   -1,  0 },
    // { KeyCodes::DELETE,         Modifiers::   SHIFT,          "\x1B[3;2~", +1,  0 },
    { KeyCodes::DELETE,            Modifiers::ANY,            "\x1B[P",    -1,  0 },
    // { KeyCodes::DELETE,         Modifiers::   ANY,            "\x1B[3~",   +1,  0 },
    { KeyCodes::BACKSPACE,         Modifiers::NONE,           "\177",       0,  0 },
    { KeyCodes::BACKSPACE,         Modifiers::ALT,            "\x1B\177",   0,  0 },
    { KeyCodes::HOME,              Modifiers::SHIFT,          "\x1B[2J",    0, -1 },
    // { KeyCodes::HOME,           Modifiers::   SHIFT,          "\x1B[1;2H",  0, +1 },
    { KeyCodes::HOME,              Modifiers::ANY,            "\x1B[H",     0, -1 },
    // { KeyCodes::HOME,           Modifiers::   ANY,            "\x1B[1~",    0, +1 },
    { KeyCodes::END,               Modifiers::CTRL,           "\x1B[J",    -1,  0 },
    // { KeyCodes::END,            Modifiers::   CTRL,           "\x1B[1;5F", +1,  0 },
    { KeyCodes::END,               Modifiers::SHIFT,          "\x1B[K",    -1,  0 },
    // { KeyCodes::END,            Modifiers::   SHIFT,          "\x1B[1;2F", +1,  0 },
    { KeyCodes::END,               Modifiers::ANY,            "\x1B[4~",    0,  0 },
    { KeyCodes::ESCAPE,            Modifiers::ANY,            "\x1B",       0,  0 },
    { KeyCodes::PAGE_UP,           Modifiers::NONE,           "\x1B[5~",    0,  0 },
    { KeyCodes::PAGE_DOWN,         Modifiers::NONE,           "\x1B[6~",    0,  0 },
    { KeyCodes::PAGE_UP,           Modifiers::CTRL,           "\x1B[5;5~",  0, 0 },
    { KeyCodes::PAGE_UP,           Modifiers::CTRL,           "\x1B[5;5~",  0, 0 },
    { KeyCodes::PAGE_UP,           Modifiers::SHIFT,          "\x1B[5;2~",  0, 0 },
    { KeyCodes::PAGE_UP,           Modifiers::ANY,            "\x1B[5~",    0, 0 },
    { KeyCodes::BACKSPACE,         Modifiers::CTRL,           "\x1B[M",    -1, 0 },
    // { KeyCodes::BACKSPACE,      Modifiers::   CTRL,           "\x1B[3;5~", +1, 0 },
    { KeyCodes::BACKSPACE,         Modifiers::SHIFT,          "\x1B[2K",   -1, 0 },
    // { KeyCodes::BACKSPACE,      Modifiers::   SHIFT,          "\x1B[3;2~", +1, 0 },
    { KeyCodes::BACKSPACE,         Modifiers::ANY,            "\x1B[P",    -1, 0 },
    // { KeyCodes::BACKSPACE,      Modifiers::   ANY,            "\x1B[3~",   +1, 0 },
    // { KeyCodes::KEYPAD_SUBTRACT,Modifiers::   ANY,            "\x1BOm",    +2, 0 },
    // { KeyCodes::KEYPAD_DECIMAL, Modifiers::   ANY,            "\x1BOn",    +2, 0 },
    // { KeyCodes::KEYPAD_DIVIDE,  Modifiers::   ANY,            "\x1BOo",    +2, 0 },
    // { KeyCodes::KEYPAD_MULTIPLY,Modifiers::   ANY,            "\x1BOj",    +2, 0 },
    // { KeyCodes::KEYPAD_ADD,     Modifiers::   ANY,            "\x1BOk",    +2, 0 },
    { KeyCodes::F1,                Modifiers::NONE,           "\x1BOP",     0, 0 },
    { KeyCodes::F1, /* F13 */      Modifiers::SHIFT,          "\x1B[1;2P",  0, 0 },
    { KeyCodes::F1, /* F25 */      Modifiers::CTRL,           "\x1B[1;5P",  0, 0 },
    { KeyCodes::F1, /* F37 */      Modifiers::SUPER,          "\x1B[1;6P",  0, 0 },
    { KeyCodes::F1, /* F49 */      Modifiers::ALT,            "\x1B[1;3P",  0, 0 },
    { KeyCodes::F1, /* F61 */      Modifiers::CTRL_ALT,       "\x1B[1;4P",  0, 0 },
    { KeyCodes::F2,                Modifiers::NONE,           "\x1BOQ",     0, 0 },
    { KeyCodes::F2, /* F14 */      Modifiers::SHIFT,          "\x1B[1;2Q",  0, 0 },
    { KeyCodes::F2, /* F26 */      Modifiers::CTRL,           "\x1B[1;5Q",  0, 0 },
    { KeyCodes::F2, /* F38 */      Modifiers::SUPER,          "\x1B[1;6Q",  0, 0 },
    { KeyCodes::F2, /* F50 */      Modifiers::ALT,            "\x1B[1;3Q",  0, 0 },
    { KeyCodes::F2, /* F62 */      Modifiers::CTRL_ALT,       "\x1B[1;4Q",  0, 0 },
    { KeyCodes::F3,                Modifiers::NONE,           "\x1BOR",     0, 0 },
    { KeyCodes::F3, /* F15 */      Modifiers::SHIFT,          "\x1B[1;2R",  0, 0 },
    { KeyCodes::F3, /* F27 */      Modifiers::CTRL,           "\x1B[1;5R",  0, 0 },
    { KeyCodes::F3, /* F39 */      Modifiers::SUPER,          "\x1B[1;6R",  0, 0 },
    { KeyCodes::F3, /* F51 */      Modifiers::ALT,            "\x1B[1;3R",  0, 0 },
    { KeyCodes::F3, /* F63 */      Modifiers::CTRL_ALT,       "\x1B[1;4R",  0, 0 },
    { KeyCodes::F4,                Modifiers::NONE,           "\x1BOS",     0, 0 },
    { KeyCodes::F4, /* F16 */      Modifiers::SHIFT,          "\x1B[1;2S",  0, 0 },
    { KeyCodes::F4, /* F28 */      Modifiers::CTRL,           "\x1B[1;5S",  0, 0 },
    { KeyCodes::F4, /* F40 */      Modifiers::SUPER,          "\x1B[1;6S",  0, 0 },
    { KeyCodes::F4, /* F52 */      Modifiers::ALT,            "\x1B[1;3S",  0, 0 },
    { KeyCodes::F5,                Modifiers::NONE,           "\x1B[15~",   0, 0 },
    { KeyCodes::F5, /* F17 */      Modifiers::SHIFT,          "\x1B[15;2~", 0, 0 },
    { KeyCodes::F5, /* F29 */      Modifiers::CTRL,           "\x1B[15;5~", 0, 0 },
    { KeyCodes::F5, /* F41 */      Modifiers::SUPER,          "\x1B[15;6~", 0, 0 },
    { KeyCodes::F5, /* F53 */      Modifiers::ALT,            "\x1B[15;3~", 0, 0 },
    { KeyCodes::F6,                Modifiers::NONE,           "\x1B[17~",   0, 0 },
    { KeyCodes::F6, /* F18 */      Modifiers::SHIFT,          "\x1B[17;2~", 0, 0 },
    { KeyCodes::F6, /* F30 */      Modifiers::CTRL,           "\x1B[17;5~", 0, 0 },
    { KeyCodes::F6, /* F42 */      Modifiers::SUPER,          "\x1B[17;6~", 0, 0 },
    { KeyCodes::F6, /* F54 */      Modifiers::ALT,            "\x1B[17;3~", 0, 0 },
    { KeyCodes::F7,                Modifiers::NONE,           "\x1B[18~",   0, 0 },
    { KeyCodes::F7, /* F19 */      Modifiers::SHIFT,          "\x1B[18;2~", 0, 0 },
    { KeyCodes::F7, /* F31 */      Modifiers::CTRL,           "\x1B[18;5~", 0, 0 },
    { KeyCodes::F7, /* F43 */      Modifiers::SUPER,          "\x1B[18;6~", 0, 0 },
    { KeyCodes::F7, /* F55 */      Modifiers::ALT,            "\x1B[18;3~", 0, 0 },
    { KeyCodes::F8,                Modifiers::NONE,           "\x1B[19~",   0, 0 },
    { KeyCodes::F8, /* F20 */      Modifiers::SHIFT,          "\x1B[19;2~", 0, 0 },
    { KeyCodes::F8, /* F32 */      Modifiers::CTRL,           "\x1B[19;5~", 0, 0 },
    { KeyCodes::F8, /* F44 */      Modifiers::SUPER,          "\x1B[19;6~", 0, 0 },
    { KeyCodes::F8, /* F56 */      Modifiers::ALT,            "\x1B[19;3~", 0, 0 },
    { KeyCodes::F9,                Modifiers::NONE,           "\x1B[20~",   0, 0 },
    { KeyCodes::F9, /* F21 */      Modifiers::SHIFT,          "\x1B[20;2~", 0, 0 },
    { KeyCodes::F9, /* F33 */      Modifiers::CTRL,           "\x1B[20;5~", 0, 0 },
    { KeyCodes::F9, /* F45 */      Modifiers::SUPER,          "\x1B[20;6~", 0, 0 },
    { KeyCodes::F9, /* F57 */      Modifiers::ALT,            "\x1B[20;3~", 0, 0 },
    { KeyCodes::F10,               Modifiers::NONE,           "\x1B[21~",   0, 0 },
    { KeyCodes::F10, /* F22 */     Modifiers::SHIFT,          "\x1B[21;2~", 0, 0 },
    { KeyCodes::F10, /* F34 */     Modifiers::CTRL,           "\x1B[21;5~", 0, 0 },
    { KeyCodes::F10, /* F46 */     Modifiers::SUPER,          "\x1B[21;6~", 0, 0 },
    { KeyCodes::F10, /* F58 */     Modifiers::ALT,            "\x1B[21;3~", 0, 0 },
    { KeyCodes::F11,               Modifiers::NONE,           "\x1B[23~",   0, 0 },
    { KeyCodes::F11, /* F23 */     Modifiers::SHIFT,          "\x1B[23;2~", 0, 0 },
    { KeyCodes::F11, /* F35 */     Modifiers::CTRL,           "\x1B[23;5~", 0, 0 },
    { KeyCodes::F11, /* F47 */     Modifiers::SUPER,          "\x1B[23;6~", 0, 0 },
    { KeyCodes::F11, /* F59 */     Modifiers::ALT,            "\x1B[23;3~", 0, 0 },
    { KeyCodes::F12,               Modifiers::NONE,           "\x1B[24~",   0, 0 },
    { KeyCodes::F12, /* F24 */     Modifiers::SHIFT,          "\x1B[24;2~", 0, 0 },
    { KeyCodes::F12, /* F36 */     Modifiers::CTRL,           "\x1B[24;5~", 0, 0 },
    { KeyCodes::F12, /* F48 */     Modifiers::SUPER,          "\x1B[24;6~", 0, 0 },
    { KeyCodes::F12, /* F60 */     Modifiers::ALT,            "\x1B[24;3~", 0, 0 },
    { KeyCodes::F13,               Modifiers::NONE,           "\x1B[1;2P",  0, 0 },
    { KeyCodes::F14,               Modifiers::NONE,           "\x1B[1;2Q",  0, 0 },
    { KeyCodes::F15,               Modifiers::NONE,           "\x1B[1;2R",  0, 0 },
    { KeyCodes::F16,               Modifiers::NONE,           "\x1B[1;2S",  0, 0 },
    { KeyCodes::F17,               Modifiers::NONE,           "\x1B[15;2~", 0, 0 },
    { KeyCodes::F18,               Modifiers::NONE,           "\x1B[17;2~", 0, 0 },
    { KeyCodes::F19,               Modifiers::NONE,           "\x1B[18;2~", 0, 0 },
    { KeyCodes::F20,               Modifiers::NONE,           "\x1B[19;2~", 0, 0 },
    { KeyCodes::F21,               Modifiers::NONE,           "\x1B[20;2~", 0, 0 },
    { KeyCodes::F22,               Modifiers::NONE,           "\x1B[21;2~", 0, 0 },
    { KeyCodes::F23,               Modifiers::NONE,           "\x1B[23;2~", 0, 0 },
    { KeyCodes::F24,               Modifiers::NONE,           "\x1B[24;2~", 0, 0 }
    // { KeyCodes::KEYPAD_0,       Modifiers::   ANY,            "\x1BOp",    +2, 0 },
    // { KeyCodes::KEYPAD_1,       Modifiers::   ANY,            "\x1BOq",    +2, 0 },
    // { KeyCodes::KEYPAD_2,       Modifiers::   ANY,            "\x1BOr",    +2, 0 },
    // { KeyCodes::KEYPAD_3,       Modifiers::   ANY,            "\x1BOs",    +2, 0 },
    // { KeyCodes::KEYPAD_4,       Modifiers::   ANY,            "\x1BOt",    +2, 0 },
    // { KeyCodes::KEYPAD_5,       Modifiers::   ANY,            "\x1BOu",    +2, 0 },
    // { KeyCodes::KEYPAD_6,       Modifiers::   ANY,            "\x1BOv",    +2, 0 },
    // { KeyCodes::KEYPAD_7,       Modifiers::   ANY,            "\x1BOw",    +2, 0 },
    // { KeyCodes::KEYPAD_8,       Modifiers::   ANY,            "\x1BOx",    +2, 0 },
    // { KeyCodes::KEYPAD_9,       Modifiers::   ANY,            "\x1BOy",    +2, 0 }
};
// clang-format on
//
// ImGuiKeyMap ImGuiTerminalKeyMap{ keys,         ( sizeof( keys ) / sizeof( keys[0] ) ),
//                                  platformKeys, ( sizeof( platformKeys ) / sizeof( platformKeys[0] ) ),
//
//                                  shortcuts,    ( sizeof( shortcuts ) / sizeof( shortcuts[0] ) ) };

ControlSequences::ControlSequences()
{
    size_t controlSequenceCount = sizeof( keys ) / sizeof( Key );
    for( int i = 0; i < controlSequenceCount; i++ )
    {
        if( keys[i].mask == Modifiers::ANY )
        {
            for( int j = 0; j < (size_t)Modifiers::COUNT; j++ )
                controlSequences[(size_t)keys[i].keysym][j] = keys[i].string;
        }
        else
        {
            controlSequences[(size_t)keys[i].keysym][(size_t)keys[i].mask] = keys[i].string;
        }
    }

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

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

#define ImGuiKeyModFlags_AltGr ImGuiKeyModFlags_Ctrl | ImGuiKeyModFlags_Alt

ImGuiKeyMap::ImGuiKeyMap( const Key keys[], size_t keysLen, const Key platformKeys[], size_t platformKeysLen,
                          const Shortcut shortcuts[], size_t shortcutsLen )
{
    for( size_t i = 0; i < keysLen; i++ )
    {
        auto &e = m_keyMap[keys[i].keysym];
        e.push_back( { keys[i].mask, keys[i].string, keys[i].appkey, keys[i].appcursor } );
    }

    for( size_t i = 0; i < platformKeysLen; i++ )
    {
        auto &e = m_platformKeyMap[platformKeys[i].keysym];
        e.push_back( { platformKeys[i].mask, platformKeys[i].string, platformKeys[i].appkey, platformKeys[i].appcursor } );
    }

    for( size_t i = 0; i < shortcutsLen; i++ )
    {
        auto &e = m_shortcuts[shortcuts[i].keysym];
        e.push_back( { shortcuts[i].mask, shortcuts[i].action, shortcuts[i].appkey, shortcuts[i].appcursor } );
    }
}

// using ShortcutAction = Hexe::Terminal::ShortcutAction;

static Shortcut shortcuts[] = { { ImGuiKey_Insert, ImGuiKeyModFlags_Shift, ShortcutAction::PASTE, 0, 0 } };
// clang-format off
static Key keys[] = {
    /* keysym               mask                                                                   string       appkey appcursor */
    { ImGuiKey_KeypadEnter, ImGuiKeyModFlags_Any,                                                  "\x1BOM",    +2,  0 },
    { ImGuiKey_KeypadEnter, ImGuiKeyModFlags_Any,                                                  "\r",        -1,  0 },

    { ImGuiKey_UpArrow,     ImGuiKeyModFlags_Shift,                                                "\x1B[1;2A",  0,  0 },
    { ImGuiKey_UpArrow,     ImGuiKeyModFlags_Alt,                                                  "\x1B[1;3A",  0,  0 },
    { ImGuiKey_UpArrow,     ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Alt,                         "\x1B[1;4A",  0,  0 },
    { ImGuiKey_UpArrow,     ImGuiKeyModFlags_Ctrl,                                                 "\x1B[1;5A",  0,  0 },
    { ImGuiKey_UpArrow,     ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Ctrl,                        "\x1B[1;6A",  0,  0 },
    { ImGuiKey_UpArrow,     ImGuiKeyModFlags_Ctrl | ImGuiKeyModFlags_Alt,                          "\x1B[1;7A",  0,  0 },
    { ImGuiKey_UpArrow,     ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Ctrl | ImGuiKeyModFlags_Alt, "\x1B[1;8A",  0,  0 },
    { ImGuiKey_UpArrow,     ImGuiKeyModFlags_Any,                                                  "\x1B[A",     0, -1 },
    { ImGuiKey_UpArrow,     ImGuiKeyModFlags_Any,                                                  "\x1BOA",     0, +1 },
    
    { ImGuiKey_DownArrow,   ImGuiKeyModFlags_Shift,                                                "\x1B[1;2B",  0,  0 },
    { ImGuiKey_DownArrow,   ImGuiKeyModFlags_Alt,                                                  "\x1B[1;3B",  0,  0 },
    { ImGuiKey_DownArrow,   ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Alt,                         "\x1B[1;4B",  0,  0 },
    { ImGuiKey_DownArrow,   ImGuiKeyModFlags_Ctrl,                                                 "\x1B[1;5B",  0,  0 },
    { ImGuiKey_DownArrow,   ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Ctrl,                        "\x1B[1;6B",  0,  0 },
    { ImGuiKey_DownArrow,   ImGuiKeyModFlags_Ctrl | ImGuiKeyModFlags_Alt,                          "\x1B[1;7B",  0,  0 },
    { ImGuiKey_DownArrow,   ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Ctrl | ImGuiKeyModFlags_Alt, "\x1B[1;8B",  0,  0 },
    { ImGuiKey_DownArrow,   ImGuiKeyModFlags_Any,                                                  "\x1B[B",     0, -1 },
    { ImGuiKey_DownArrow,   ImGuiKeyModFlags_Any,                                                  "\x1BOB",     0, +1 },
    
    { ImGuiKey_LeftArrow,   ImGuiKeyModFlags_Shift,                                                "\x1B[1;2D",  0,  0 },
    { ImGuiKey_LeftArrow,   ImGuiKeyModFlags_Alt,                                                  "\x1B[1;3D",  0,  0 },
    { ImGuiKey_LeftArrow,   ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Alt,                         "\x1B[1;4D",  0,  0 },
    { ImGuiKey_LeftArrow,   ImGuiKeyModFlags_Ctrl,                                                 "\x1B[1;5D",  0,  0 },
    { ImGuiKey_LeftArrow,   ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Ctrl,                        "\x1B[1;6D",  0,  0 },
    { ImGuiKey_LeftArrow,   ImGuiKeyModFlags_Ctrl | ImGuiKeyModFlags_Alt,                          "\x1B[1;7D",  0,  0 },
    { ImGuiKey_LeftArrow,   ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Ctrl | ImGuiKeyModFlags_Alt, "\x1B[1;8D",  0,  0 },
    { ImGuiKey_LeftArrow,   ImGuiKeyModFlags_Any,                                                  "\x1B[D",     0, -1 },
    { ImGuiKey_LeftArrow,   ImGuiKeyModFlags_Any,                                                  "\x1BOD",     0, +1 },
    
    { ImGuiKey_RightArrow,  ImGuiKeyModFlags_Shift,                                                "\x1B[1;2C",  0,  0 },
    { ImGuiKey_RightArrow,  ImGuiKeyModFlags_Alt,                                                  "\x1B[1;3C",  0,  0 },
    { ImGuiKey_RightArrow,  ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Alt,                         "\x1B[1;4C",  0,  0 },
    { ImGuiKey_RightArrow,  ImGuiKeyModFlags_Ctrl,                                                 "\x1B[1;5C",  0,  0 },
    { ImGuiKey_RightArrow,  ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Ctrl,                        "\x1B[1;6C",  0,  0 },
    { ImGuiKey_RightArrow,  ImGuiKeyModFlags_Ctrl | ImGuiKeyModFlags_Alt,                          "\x1B[1;7C",  0,  0 },
    { ImGuiKey_RightArrow,  ImGuiKeyModFlags_Shift | ImGuiKeyModFlags_Ctrl | ImGuiKeyModFlags_Alt, "\x1B[1;8C",  0,  0 },
    { ImGuiKey_RightArrow,  ImGuiKeyModFlags_Any,                                                  "\x1B[C",     0, -1 },
    { ImGuiKey_RightArrow,  ImGuiKeyModFlags_Any,                                                  "\x1BOC",     0, +1 },
    
    { ImGuiKey_Tab,         ImGuiKeyModFlags_Shift,                                                "\x1B[Z",     0,  0 },
    { ImGuiKey_Tab,         ImGuiKeyModFlags_Any,                                                  "\t",         0,  0 },
    
    { ImGuiKey_Enter,       ImGuiKeyModFlags_Alt,                                                  "\x1B\r",     0,  0 },
    { ImGuiKey_Enter,       ImGuiKeyModFlags_Any,                                                  "\r",         0,  0 },
    
    { ImGuiKey_Insert,      ImGuiKeyModFlags_Shift,                                                "\x1B[4l",   -1,  0 },
    { ImGuiKey_Insert,      ImGuiKeyModFlags_Shift,                                                "\x1B[2;2~", +1,  0 },
    { ImGuiKey_Insert,      ImGuiKeyModFlags_Ctrl,                                                 "\x1B[L",    -1,  0 },
    { ImGuiKey_Insert,      ImGuiKeyModFlags_Ctrl,                                                 "\x1B[2;5~", +1,  0 },
    { ImGuiKey_Insert,      ImGuiKeyModFlags_Any,                                                  "\x1B[4h",   -1,  0 },
    { ImGuiKey_Insert,      ImGuiKeyModFlags_Any,                                                  "\x1B[2~",   +1,  0 },
    
    { ImGuiKey_Delete,      ImGuiKeyModFlags_Ctrl,                                                 "\x1B[M",    -1,  0 },
    { ImGuiKey_Delete,      ImGuiKeyModFlags_Ctrl,                                                 "\x1B[3;5~", +1,  0 },
    { ImGuiKey_Delete,      ImGuiKeyModFlags_Shift,                                                "\x1B[2K",   -1,  0 },
    { ImGuiKey_Delete,      ImGuiKeyModFlags_Shift,                                                "\x1B[3;2~", +1,  0 },
    { ImGuiKey_Delete,      ImGuiKeyModFlags_Any,                                                  "\x1B[P",    -1,  0 },
    { ImGuiKey_Delete,      ImGuiKeyModFlags_Any,                                                  "\x1B[3~",   +1,  0 },
    
    { ImGuiKey_Backspace,   ImGuiKeyModFlags_None,                                                 "\177",       0,  0 },
    { ImGuiKey_Backspace,   ImGuiKeyModFlags_Alt,                                                  "\x1B\177",   0,  0 },
    
    { ImGuiKey_Home,        ImGuiKeyModFlags_Shift,                                                "\x1B[2J",    0, -1 },
    { ImGuiKey_Home,        ImGuiKeyModFlags_Shift,                                                "\x1B[1;2H",  0, +1 },
    { ImGuiKey_Home,        ImGuiKeyModFlags_Any,                                                  "\x1B[H",     0, -1 },
    { ImGuiKey_Home,        ImGuiKeyModFlags_Any,                                                  "\x1B[1~",    0, +1 },
    
    { ImGuiKey_End,         ImGuiKeyModFlags_Ctrl,                                                 "\x1B[J",    -1,  0 },
    { ImGuiKey_End,         ImGuiKeyModFlags_Ctrl,                                                 "\x1B[1;5F", +1,  0 },
    { ImGuiKey_End,         ImGuiKeyModFlags_Shift,                                                "\x1B[K",    -1,  0 },
    { ImGuiKey_End,         ImGuiKeyModFlags_Shift,                                                "\x1B[1;2F", +1,  0 },
    { ImGuiKey_End,         ImGuiKeyModFlags_Any,                                                  "\x1B[4~",    0,  0 },
    
    { ImGuiKey_Escape,      ImGuiKeyModFlags_Any,                                                  "\x1B",       0,  0 },
    
    { ImGuiKey_PageUp,      ImGuiKeyModFlags_None,                                                 "\x1B[5~",    0,  0 },
    
    { ImGuiKey_PageDown,    ImGuiKeyModFlags_None,                                                 "\x1B[6~",    0,  0 },
};
static Key platformKeys[] = {
#if defined( HEXE_USING_SDL )
    { SDL_SCANCODE_PRIOR, ImGuiKeyModFlags_Ctrl, "\x1B[5;5~", 0, 0 },

    { SDL_SCANCODE_PRIOR, ImGuiKeyModFlags_Ctrl, "\x1B[5;5~", 0, 0 },
    { SDL_SCANCODE_PRIOR, ImGuiKeyModFlags_Shift, "\x1B[5;2~", 0, 0 },
    { SDL_SCANCODE_PRIOR, ImGuiKeyModFlags_Any, "\x1B[5~", 0, 0 },

    { SDL_SCANCODE_KP_BACKSPACE, ImGuiKeyModFlags_Ctrl, "\x1B[M", -1, 0 },
    { SDL_SCANCODE_KP_BACKSPACE, ImGuiKeyModFlags_Ctrl, "\x1B[3;5~", +1, 0 },
    { SDL_SCANCODE_KP_BACKSPACE, ImGuiKeyModFlags_Shift, "\x1B[2K", -1, 0 },
    { SDL_SCANCODE_KP_BACKSPACE, ImGuiKeyModFlags_Shift, "\x1B[3;2~", +1, 0 },
    { SDL_SCANCODE_KP_BACKSPACE, ImGuiKeyModFlags_Any, "\x1B[P", -1, 0 },
    { SDL_SCANCODE_KP_BACKSPACE, ImGuiKeyModFlags_Any, "\x1B[3~", +1, 0 },

    { SDL_SCANCODE_KP_MINUS, ImGuiKeyModFlags_Any, "\x1BOm", +2, 0 },
    { SDL_SCANCODE_KP_DECIMAL, ImGuiKeyModFlags_Any, "\x1BOn", +2, 0 },
    { SDL_SCANCODE_KP_DIVIDE, ImGuiKeyModFlags_Any, "\x1BOo", +2, 0 },
    { SDL_SCANCODE_KP_MULTIPLY, ImGuiKeyModFlags_Any, "\x1BOj", +2, 0 },
    { SDL_SCANCODE_KP_PLUS, ImGuiKeyModFlags_Any, "\x1BOk", +2, 0 },

    { SDL_SCANCODE_F1, ImGuiKeyModFlags_None, "\x1BOP", 0, 0 },
    { SDL_SCANCODE_F1, /* F13 */ ImGuiKeyModFlags_Shift, "\x1B[1;2P", 0, 0 },
    { SDL_SCANCODE_F1, /* F25 */ ImGuiKeyModFlags_Ctrl, "\x1B[1;5P", 0, 0 },
    { SDL_SCANCODE_F1, /* F37 */ ImGuiKeyModFlags_Super, "\x1B[1;6P", 0, 0 },
    { SDL_SCANCODE_F1, /* F49 */ ImGuiKeyModFlags_Alt, "\x1B[1;3P", 0, 0 },
    { SDL_SCANCODE_F1, /* F61 */ ImGuiKeyModFlags_AltGr, "\x1B[1;4P", 0, 0 },
    { SDL_SCANCODE_F2, ImGuiKeyModFlags_None, "\x1BOQ", 0, 0 },
    { SDL_SCANCODE_F2, /* F14 */ ImGuiKeyModFlags_Shift, "\x1B[1;2Q", 0, 0 },
    { SDL_SCANCODE_F2, /* F26 */ ImGuiKeyModFlags_Ctrl, "\x1B[1;5Q", 0, 0 },
    { SDL_SCANCODE_F2, /* F38 */ ImGuiKeyModFlags_Super, "\x1B[1;6Q", 0, 0 },
    { SDL_SCANCODE_F2, /* F50 */ ImGuiKeyModFlags_Alt, "\x1B[1;3Q", 0, 0 },
    { SDL_SCANCODE_F2, /* F62 */ ImGuiKeyModFlags_AltGr, "\x1B[1;4Q", 0, 0 },
    { SDL_SCANCODE_F3, ImGuiKeyModFlags_None, "\x1BOR", 0, 0 },
    { SDL_SCANCODE_F3, /* F15 */ ImGuiKeyModFlags_Shift, "\x1B[1;2R", 0, 0 },
    { SDL_SCANCODE_F3, /* F27 */ ImGuiKeyModFlags_Ctrl, "\x1B[1;5R", 0, 0 },
    { SDL_SCANCODE_F3, /* F39 */ ImGuiKeyModFlags_Super, "\x1B[1;6R", 0, 0 },
    { SDL_SCANCODE_F3, /* F51 */ ImGuiKeyModFlags_Alt, "\x1B[1;3R", 0, 0 },
    { SDL_SCANCODE_F3, /* F63 */ ImGuiKeyModFlags_AltGr, "\x1B[1;4R", 0, 0 },
    { SDL_SCANCODE_F4, ImGuiKeyModFlags_None, "\x1BOS", 0, 0 },
    { SDL_SCANCODE_F4, /* F16 */ ImGuiKeyModFlags_Shift, "\x1B[1;2S", 0, 0 },
    { SDL_SCANCODE_F4, /* F28 */ ImGuiKeyModFlags_Ctrl, "\x1B[1;5S", 0, 0 },
    { SDL_SCANCODE_F4, /* F40 */ ImGuiKeyModFlags_Super, "\x1B[1;6S", 0, 0 },
    { SDL_SCANCODE_F4, /* F52 */ ImGuiKeyModFlags_Alt, "\x1B[1;3S", 0, 0 },
    { SDL_SCANCODE_F5, ImGuiKeyModFlags_None, "\x1B[15~", 0, 0 },
    { SDL_SCANCODE_F5, /* F17 */ ImGuiKeyModFlags_Shift, "\x1B[15;2~", 0, 0 },
    { SDL_SCANCODE_F5, /* F29 */ ImGuiKeyModFlags_Ctrl, "\x1B[15;5~", 0, 0 },
    { SDL_SCANCODE_F5, /* F41 */ ImGuiKeyModFlags_Super, "\x1B[15;6~", 0, 0 },
    { SDL_SCANCODE_F5, /* F53 */ ImGuiKeyModFlags_Alt, "\x1B[15;3~", 0, 0 },
    { SDL_SCANCODE_F6, ImGuiKeyModFlags_None, "\x1B[17~", 0, 0 },
    { SDL_SCANCODE_F6, /* F18 */ ImGuiKeyModFlags_Shift, "\x1B[17;2~", 0, 0 },
    { SDL_SCANCODE_F6, /* F30 */ ImGuiKeyModFlags_Ctrl, "\x1B[17;5~", 0, 0 },
    { SDL_SCANCODE_F6, /* F42 */ ImGuiKeyModFlags_Super, "\x1B[17;6~", 0, 0 },
    { SDL_SCANCODE_F6, /* F54 */ ImGuiKeyModFlags_Alt, "\x1B[17;3~", 0, 0 },
    { SDL_SCANCODE_F7, ImGuiKeyModFlags_None, "\x1B[18~", 0, 0 },
    { SDL_SCANCODE_F7, /* F19 */ ImGuiKeyModFlags_Shift, "\x1B[18;2~", 0, 0 },
    { SDL_SCANCODE_F7, /* F31 */ ImGuiKeyModFlags_Ctrl, "\x1B[18;5~", 0, 0 },
    { SDL_SCANCODE_F7, /* F43 */ ImGuiKeyModFlags_Super, "\x1B[18;6~", 0, 0 },
    { SDL_SCANCODE_F7, /* F55 */ ImGuiKeyModFlags_Alt, "\x1B[18;3~", 0, 0 },
    { SDL_SCANCODE_F8, ImGuiKeyModFlags_None, "\x1B[19~", 0, 0 },
    { SDL_SCANCODE_F8, /* F20 */ ImGuiKeyModFlags_Shift, "\x1B[19;2~", 0, 0 },
    { SDL_SCANCODE_F8, /* F32 */ ImGuiKeyModFlags_Ctrl, "\x1B[19;5~", 0, 0 },
    { SDL_SCANCODE_F8, /* F44 */ ImGuiKeyModFlags_Super, "\x1B[19;6~", 0, 0 },
    { SDL_SCANCODE_F8, /* F56 */ ImGuiKeyModFlags_Alt, "\x1B[19;3~", 0, 0 },
    { SDL_SCANCODE_F9, ImGuiKeyModFlags_None, "\x1B[20~", 0, 0 },
    { SDL_SCANCODE_F9, /* F21 */ ImGuiKeyModFlags_Shift, "\x1B[20;2~", 0, 0 },
    { SDL_SCANCODE_F9, /* F33 */ ImGuiKeyModFlags_Ctrl, "\x1B[20;5~", 0, 0 },
    { SDL_SCANCODE_F9, /* F45 */ ImGuiKeyModFlags_Super, "\x1B[20;6~", 0, 0 },
    { SDL_SCANCODE_F9, /* F57 */ ImGuiKeyModFlags_Alt, "\x1B[20;3~", 0, 0 },
    { SDL_SCANCODE_F10, ImGuiKeyModFlags_None, "\x1B[21~", 0, 0 },
    { SDL_SCANCODE_F10, /* F22 */ ImGuiKeyModFlags_Shift, "\x1B[21;2~", 0, 0 },
    { SDL_SCANCODE_F10, /* F34 */ ImGuiKeyModFlags_Ctrl, "\x1B[21;5~", 0, 0 },
    { SDL_SCANCODE_F10, /* F46 */ ImGuiKeyModFlags_Super, "\x1B[21;6~", 0, 0 },
    { SDL_SCANCODE_F10, /* F58 */ ImGuiKeyModFlags_Alt, "\x1B[21;3~", 0, 0 },
    { SDL_SCANCODE_F11, ImGuiKeyModFlags_None, "\x1B[23~", 0, 0 },
    { SDL_SCANCODE_F11, /* F23 */ ImGuiKeyModFlags_Shift, "\x1B[23;2~", 0, 0 },
    { SDL_SCANCODE_F11, /* F35 */ ImGuiKeyModFlags_Ctrl, "\x1B[23;5~", 0, 0 },
    { SDL_SCANCODE_F11, /* F47 */ ImGuiKeyModFlags_Super, "\x1B[23;6~", 0, 0 },
    { SDL_SCANCODE_F11, /* F59 */ ImGuiKeyModFlags_Alt, "\x1B[23;3~", 0, 0 },
    { SDL_SCANCODE_F12, ImGuiKeyModFlags_None, "\x1B[24~", 0, 0 },
    { SDL_SCANCODE_F12, /* F24 */ ImGuiKeyModFlags_Shift, "\x1B[24;2~", 0, 0 },
    { SDL_SCANCODE_F12, /* F36 */ ImGuiKeyModFlags_Ctrl, "\x1B[24;5~", 0, 0 },
    { SDL_SCANCODE_F12, /* F48 */ ImGuiKeyModFlags_Super, "\x1B[24;6~", 0, 0 },
    { SDL_SCANCODE_F12, /* F60 */ ImGuiKeyModFlags_Alt, "\x1B[24;3~", 0, 0 },
    { SDL_SCANCODE_F13, ImGuiKeyModFlags_None, "\x1B[1;2P", 0, 0 },
    { SDL_SCANCODE_F14, ImGuiKeyModFlags_None, "\x1B[1;2Q", 0, 0 },
    { SDL_SCANCODE_F15, ImGuiKeyModFlags_None, "\x1B[1;2R", 0, 0 },
    { SDL_SCANCODE_F16, ImGuiKeyModFlags_None, "\x1B[1;2S", 0, 0 },
    { SDL_SCANCODE_F17, ImGuiKeyModFlags_None, "\x1B[15;2~", 0, 0 },
    { SDL_SCANCODE_F18, ImGuiKeyModFlags_None, "\x1B[17;2~", 0, 0 },
    { SDL_SCANCODE_F19, ImGuiKeyModFlags_None, "\x1B[18;2~", 0, 0 },
    { SDL_SCANCODE_F20, ImGuiKeyModFlags_None, "\x1B[19;2~", 0, 0 },
    { SDL_SCANCODE_F21, ImGuiKeyModFlags_None, "\x1B[20;2~", 0, 0 },
    { SDL_SCANCODE_F22, ImGuiKeyModFlags_None, "\x1B[21;2~", 0, 0 },
    { SDL_SCANCODE_F23, ImGuiKeyModFlags_None, "\x1B[23;2~", 0, 0 },
    { SDL_SCANCODE_F24, ImGuiKeyModFlags_None, "\x1B[24;2~", 0, 0 },

    { SDL_SCANCODE_KP_0, ImGuiKeyModFlags_Any, "\x1BOp", +2, 0 },
    { SDL_SCANCODE_KP_1, ImGuiKeyModFlags_Any, "\x1BOq", +2, 0 },
    { SDL_SCANCODE_KP_2, ImGuiKeyModFlags_Any, "\x1BOr", +2, 0 },
    { SDL_SCANCODE_KP_3, ImGuiKeyModFlags_Any, "\x1BOs", +2, 0 },
    { SDL_SCANCODE_KP_4, ImGuiKeyModFlags_Any, "\x1BOt", +2, 0 },
    { SDL_SCANCODE_KP_5, ImGuiKeyModFlags_Any, "\x1BOu", +2, 0 },
    { SDL_SCANCODE_KP_6, ImGuiKeyModFlags_Any, "\x1BOv", +2, 0 },
    { SDL_SCANCODE_KP_7, ImGuiKeyModFlags_Any, "\x1BOw", +2, 0 },
    { SDL_SCANCODE_KP_8, ImGuiKeyModFlags_Any, "\x1BOx", +2, 0 },
    { SDL_SCANCODE_KP_9, ImGuiKeyModFlags_Any, "\x1BOy", +2, 0 }
#endif
};

ImGuiKeyMap ImGuiTerminalKeyMap{ keys,         ( sizeof( keys ) / sizeof( keys[0] ) ),
                                 platformKeys, ( sizeof( platformKeys ) / sizeof( platformKeys[0] ) ),
                                 shortcuts,    ( sizeof( shortcuts ) / sizeof( shortcuts[0] ) ) };

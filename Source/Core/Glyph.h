#pragma once

#include "Core/String.h"

enum CharacterAttribute : uint32_t
{
    NORMAL        = 0,
    FAINT         = ( 1 << 0 ),
    BOLD          = ( 1 << 1 ),
    ITALIC        = ( 1 << 2 ),
    UNDERLINE     = ( 1 << 3 ),
    STRIKETHROUGH = ( 1 << 4 ),
    DEFAULT_BG    = ( 1 << 5 ),
    DEFAULT_FG    = ( 1 << 6 )
};

struct Glyph
{
    char_t   Character[4];
    uint32_t CharacterSize;
    
    // The attributes member encodes the glyph's character attributes,
    // as well as the foreground and background color:
    //   | CharacterAttributes | Foreground  | Background |
    //   |       16 bits       |   24 bits   |   24 bits  |
    uint64_t Attributes = 0;
};

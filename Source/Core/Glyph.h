#pragma once

#include "Core/String.h"

enum character_attribute : uint32_t
{
    NORMAL        = 0,
    FAINT         = ( 1 << 0 ),
    BOLD          = ( 1 << 1 ),
    ITALIC        = ( 1 << 2 ),
    UNDERLINE     = ( 1 << 3 ),
    STRIKETHROUGH = ( 1 << 4 ),
    REVERSED      = ( 1 << 5 ),
    HIDDEN        = ( 1 << 6 ),
    SLOW_BLINK    = ( 1 << 7 ),
    FAST_BLINK    = ( 1 << 8 ),
    DEFAULT_BG    = ( 1 << 9 ),
    DEFAULT_FG    = ( 1 << 10 )
};

struct glyph_t
{
    char_t   Character[4]  = { 0 };
    uint32_t CharacterSize = 1;

    // The attributes member encodes the glyph's character attributes,
    // as well as the foreground and background color:
    //   | CharacterAttributes | Foreground  | Background |
    //   |       16 bits       |   24 bits   |   24 bits  |
    uint64_t Attributes = 0;
};

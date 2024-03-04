#pragma once

#include <cstdint>

enum CharacterAttribute : uint32_t
{
    NORMAL        = 0,
    FAINT         = 1,
    BOLD          = 2,
    ITALIC        = 3,
    UNDERLINE     = 4,
    STRIKETHROUGH = 5,
    DEFAULT_BG    = 6,
    DEFAULT_FG    = 7
};

struct Glyph
{
    uint32_t Character = 0;

    // The attributes member encodes the glyph's character attributes,
    // as well as the foreground and background color:
    //   | CharacterAttributes | Foreground  | Background |
    //   |       16 bits       |   24 bits   |   24 bits  |
    uint64_t Attributes = 0;
};

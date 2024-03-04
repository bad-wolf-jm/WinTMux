#pragma once

#include <cstdint>

enum CharacterAttribute : uint32_t
{
    NORMAL        = 0,
    BOLD          = 1,
    ITALIC        = 2,
    UNDERLINE     = 3,
    STRIKETHROUGH = 4
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

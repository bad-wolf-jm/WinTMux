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
    uint32_t Character  = 0;
    uint32_t Attributes = 0;
    uint32_t Foreground = 0;
    uint32_t Background = 0;
};

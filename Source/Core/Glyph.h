#pragma once

#include <cstdint>

struct Glyph
{
    uint32_t Character  = 0;
    uint32_t Attributes = 0;
    uint32_t Foreground = 0;
    uint32_t Background = 0;
};

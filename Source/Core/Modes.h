#pragma once
#include <cstdint>

enum class eInputMode : uint8_t
{
    Normal,
    Insert,
    Command,
    Visual,
    VisualLine,
    VisualBlock
};


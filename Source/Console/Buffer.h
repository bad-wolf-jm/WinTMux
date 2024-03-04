#pragma once

#include "Core/Glyph.h"
#include <cstdint>
#include <vector>

struct character_range_t
{
    uint64_t Attributes;
    uint32_t Start;
    uint32_t End;
};

using line_t = std::vector<character_range_t>;

class buffer_t
{
  public:
    buffer_t() = default;

  public:
    void Resize( uint32_t rows, uint32_t columns );
    void Clear();
    void Update();

    size_t                     ByteSize();
    std::vector<line_t> const &Lines();
    std::vector<Glyph> const  &Data();

  private:
    uint32_t _rows{ 0 };
    uint32_t _columns{ 0 };

    std::vector<Glyph>  _data{};
    std::vector<line_t> _lines{};
};

#pragma once

#include "Core/Glyph.h"
#include "Core/String.h"
#include <cstdint>
#include <vector>

struct character_range_t
{
    uint64_t Attributes;
    uint32_t Start;
    uint32_t End;

    uint32_t CharacterAttributes() const;
    void     Fg( uint8_t &r, uint8_t &g, uint8_t &b ) const;
    void     Bg( uint8_t &r, uint8_t &g, uint8_t &b ) const;

    uint32_t     Foreground() const;
    uint32_t     Background() const;
};

using line_t = std::vector<character_range_t>;

class framebuffer_t
{
  public:
    framebuffer_t() = default;

  public:
    void Resize( uint32_t rows, uint32_t columns );
    void BeginFrame();
    void EndFrame();

    void SetTextAttributes( bool bold, bool italic, bool underline, bool strikeThrough, bool faint );
    void SetBackground( uint8_t r, uint8_t g, uint8_t b );
    void SetForeground( uint8_t r, uint8_t g, uint8_t b );

    void HLine(uint32_t y, uint32_t x0, uint32_t x1, string_t c0, string_t c1, string_t cFill );
    void VLine(uint32_t x, uint32_t y0, uint32_t y1, string_t c0, string_t c1, string_t cFill );
    void DrawRect( uint32_t x, uint32_t y, uint32_t w, uint32_t h, string_t tl, string_t t, string_t tr, string_t r, string_t br,
                   string_t b, string_t bl, string_t l );

    void TextLine( uint32_t x, uint32_t y, string_t text );

    size_t                     ByteSize();
    std::vector<line_t> const &Lines() const;
    std::vector<Glyph> const  &Data() const;

  private:
    uint32_t _background;
    uint32_t _foreground;
    uint16_t _attributes;

  private:
    uint32_t _rows{ 0 };
    uint32_t _columns{ 0 };

    std::vector<Glyph>  _data{};
    std::vector<line_t> _lines{};
};

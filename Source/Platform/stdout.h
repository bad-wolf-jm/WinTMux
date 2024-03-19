#pragma once

#include <cstdint>
#include <functional>
#include <vector>

#include "Console/Framebuffer.h"
#include "Core/Glyph.h"
#include "Core/KeyCodes.h"
#include "Core/String.h"

using handle_t = void *;

class stdout_t
{
  public:
    stdout_t();
    ~stdout_t();

    void write( string_t buffer );
    void write( string_t::const_iterator begin, string_t::const_iterator end );
    void write( std::vector<glyph_t>::const_iterator begin, std::vector<glyph_t>::const_iterator end );
    void write( uint32_t attributes, uint32_t bg, uint32_t fg, std::vector<glyph_t>::const_iterator begin,
                std::vector<glyph_t>::const_iterator end );
    void write( character_range_t const &range, std::vector<glyph_t> const &buffer );
    void write( framebuffer_t const &frameBuffer );

    uint32_t Columns() {return _columns;}
    uint32_t Rows() {return _rows;}
    
  private:
    handle_t _stream;

    uint32_t _consoleMode;
    uint32_t _codePage;

    uint32_t _columns = 0;
    uint32_t _rows    = 0;
};

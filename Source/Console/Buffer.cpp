#include "Buffer.h"

void character_range_t::Fg( uint8_t &r, uint8_t &g, uint8_t &b ) const
{
    uint32_t color = static_cast<uint32_t>( ( Attributes >> 24 ) & 0xFFFFFF );

    r = color >> 16;
    g = ( color >> 8 ) & 0xFF;
    b = color & 0xFF;
}

void character_range_t::Bg( uint8_t &r, uint8_t &g, uint8_t &b ) const
{
    uint32_t color = static_cast<uint32_t>( Attributes & 0xFFFFFF );

    r = color >> 16;
    g = ( color >> 8 ) & 0xFF;
    b = color & 0xFF;
}

uint32_t character_range_t::Rendering() const
{
    return Attributes >> 48;
}

void buffer_t::Resize( uint32_t rows, uint32_t columns )
{
    _rows    = rows;
    _columns = columns;

    _data.resize( _rows * _columns );
    _lines.resize( _rows );

    for( auto &l : _lines )
        l.clear();
}

size_t buffer_t::ByteSize()
{
    return _data.size() * sizeof( uint32_t );
}

std::vector<line_t> const &buffer_t::Lines()
{
    return _lines;
}

std::vector<Glyph> const &buffer_t::Data()
{
    return _data;
}

void buffer_t::Clear()
{
    for( auto &g : _data )
    {
        g.Character  = static_cast<uint32_t>( '.' );
        g.Attributes = 0x0000ffffff222222;
    }
    //
    _data[0].Character                = static_cast<uint32_t>( '#' );
    _data[_data.size() - 1].Character = static_cast<uint32_t>( '@' );
}

void buffer_t::Update()
{
    // Clear all formatting from previous frame
    for( auto &l : _lines )
        l.clear();

    // Split lines into ranges of contiguous characters with similat formatting,
    // background color and foreground color.
    for( int r = 0; r < _rows; r++ )
        _lines[r].push_back( character_range_t{ 0x0000ffffff222222, r * _columns, ( r + 1 ) * _columns } );
}

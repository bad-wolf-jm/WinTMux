#include "Buffer.h"

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
        g.Attributes = 0;
    }

    _data[0].Character                = static_cast<uint32_t>( '#' );
    _data[_data.size() - 1].Character = static_cast<uint32_t>( '@' );
}

void buffer_t::Update()
{
    for( int r = 0; r < _rows; r++ )
    {
        _lines[r].push_back( character_range_t{0,  r * _columns, ( r + 1 ) * _columns } );
    }
}

#include "Buffer.h"

void buffer_t::Resize( uint32_t rows, uint32_t columns )
{
    _rows    = rows;
    _columns = columns;

    _data.resize( _rows * _columns );
}

size_t buffer_t::ByteSize()
{
    return _data.size() * sizeof( uint32_t );
}

std::vector<uint32_t> const &buffer_t::Data()
{
    return _data;
}

void buffer_t::Clear()
{
    uint32_t clearCharacter = static_cast<uint32_t>( '.' );
    std::fill( _data.begin(), _data.end(), clearCharacter );
    _data[0]                = static_cast<uint32_t>( '#' );
    _data[_data.size() - 1] = static_cast<uint32_t>( '@' );
}

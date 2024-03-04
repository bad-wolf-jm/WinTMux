#include "Buffer.h"

void buffer_t::Resize( uint32_t rows, uint32_t columns )
{
    _rows    = rows;
    _columns = columns;

    _data.resize( _rows * _columns );
}

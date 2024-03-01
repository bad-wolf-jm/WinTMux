#pragma once

#include <cstdint>

namespace utf8
{
    size_t   decode( const char *, uint32_t *, size_t );
    uint32_t decodebyte( char, size_t * );
    char     encodebyte( uint32_t, size_t );
    size_t   validate( uint32_t *, size_t );
    size_t   encode( uint32_t, char   *);
} // namespace utf8

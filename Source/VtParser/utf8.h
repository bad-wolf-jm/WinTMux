#pragma once

#include <cstdint>

#define UTF_INVALID 0xFFFD
#define UTF_SIZ     4

size_t   utf8decode( const char *, uint32_t *, size_t );
uint32_t utf8decodebyte( char, size_t * );
char     utf8encodebyte( uint32_t, size_t );
size_t   utf8validate( uint32_t *, size_t );
size_t   utf8encode( uint32_t, char   *);

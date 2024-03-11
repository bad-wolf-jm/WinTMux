#include "FrameBuffer.h"
#include "Core/Glyph.h"
#include <iostream>

uint32_t character_range_t::Foreground() const
{
    return static_cast<uint32_t>( ( Attributes >> 24 ) & 0xFFFFFF );
}

uint32_t character_range_t::Background() const
{
    return static_cast<uint32_t>( Attributes & 0xFFFFFF );
}

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

uint32_t character_range_t::CharacterAttributes() const
{
    return Attributes >> 48;
}

void framebuffer_t::Resize( uint32_t rows, uint32_t columns )
{
    _rows    = rows;
    _columns = columns;

    _data.resize( _rows * _columns );
    _lines.resize( _rows );

    for( auto &l : _lines )
        l.clear();
}

void framebuffer_t::SetCursor( uint32_t x, uint32_t y )
{
    // std::cout << "SetCursor( " << x << ", " << y << " )" << std::endl;
    _cursorX = x;
    _cursorY = y;
}
void framebuffer_t::Cursor( uint32_t &x, uint32_t &y )
{
    x = _cursorX;
    y = _cursorY;
}

size_t framebuffer_t::ByteSize()
{
    return _data.size() * sizeof( Glyph );
}

std::vector<line_t> const &framebuffer_t::Lines() const
{
    return _lines;
}

std::vector<Glyph> const &framebuffer_t::Data() const
{
    return _data;
}

std::vector<Glyph> &framebuffer_t::DataNC()
{
    return _data;
}

void framebuffer_t::BeginFrame()
{
    uint64_t characterAttributes = CharacterAttribute::DEFAULT_BG | CharacterAttribute::DEFAULT_FG;
    for( auto &g : _data )
    {
        g.Character[0]  = ' ';
        g.CharacterSize = 1;
        g.Attributes    = characterAttributes << 48;
    }
}

void framebuffer_t::EndFrame()
{
    // Clear all formatting from previous frame
    for( auto &l : _lines )
        l.clear();

    // Split lines into ranges of contiguous characters with similat formatting,
    // background color and foreground color.
    for( int r = 0; r < _rows; r++ )
    {
        uint32_t rowStart = r * _columns;
        uint32_t rowEnd   = rowStart + _columns;

        uint32_t rangeStart       = rowStart;
        uint64_t rangeAttributes  = _data[rowStart].Attributes;
        uint32_t currentCharacter = rowStart;
        while( currentCharacter < rowEnd )
        {
            while( ( currentCharacter < rowEnd ) && _data[currentCharacter].Attributes == rangeAttributes )
                currentCharacter++;

            _lines[r].push_back( character_range_t{ rangeAttributes, rangeStart, currentCharacter } );

            if( currentCharacter < rowEnd )
            {
                rangeAttributes = _data[currentCharacter].Attributes;
                rangeStart      = currentCharacter;
            }
        }
    }
}

void framebuffer_t::SetTextAttributes( bool bold, bool italic, bool underline, bool strikeThrough, bool faint )
{
    _attributes = 0;
    _attributes |= bold ? CharacterAttribute::BOLD : 0;
    _attributes |= italic ? CharacterAttribute::ITALIC : 0;
    _attributes |= underline ? CharacterAttribute::UNDERLINE : 0;
    _attributes |= strikeThrough ? CharacterAttribute::STRIKETHROUGH : 0;
    _attributes |= faint ? CharacterAttribute::FAINT : 0;
}

void framebuffer_t::SetBackground( uint8_t r, uint8_t g, uint8_t b )
{
    _background = r << 16 | g << 8 | b;
    std::cout << "SET_BACKGROUND"
              << " "
              << "0x" << std::setw( 8 ) << std::setfill( '0' ) << std::hex << (uint32_t)_background << std::endl;
    _attributes &= ~( (uint16_t)CharacterAttribute::DEFAULT_BG );
}

void framebuffer_t::SetBackground( uint32_t color )
{
    if( color == 0u )
    {
        _attributes |= ( (uint16_t)CharacterAttribute::DEFAULT_BG );
    }
    else
    {
        _attributes &= ~( (uint16_t)CharacterAttribute::DEFAULT_BG );
    }

    std::cout << "SET_BACKGROUND"
              << " "
              << "0x" << std::setw( 8 ) << std::setfill( '0' ) << std::hex << (uint32_t)color << std::endl;

    _background = color;
}

void framebuffer_t::SetForeground( uint8_t r, uint8_t g, uint8_t b )
{
    _foreground = r << 16 | g << 8 | b;
    std::cout << "SET_FOREGROUND"
              << " "
              << "0x" << std::setw( 8 ) << std::setfill( '0' ) << std::hex << (uint32_t)_foreground << std::endl;
    _attributes &= ~( (uint16_t)CharacterAttribute::DEFAULT_FG );
}

void framebuffer_t::SetForeground( uint32_t color )
{
    if( color == 0u )
    {
        _attributes |= ( (uint16_t)CharacterAttribute::DEFAULT_FG );
    }
    else
    {
        _attributes &= ~( (uint16_t)CharacterAttribute::DEFAULT_BG );
    }

    std::cout << "SET_FOREGROUND"
              << " "
              << "0x" << std::setw( 8 ) << std::setfill( '0' ) << std::hex << (uint32_t)color << std::endl;

    _foreground = color;
}

void framebuffer_t::HLine( uint32_t y, uint32_t x0, uint32_t x1, string_t c0, string_t c1, string_t cFill )
{
    uint32_t position;
    uint64_t attributes =
        _background | ( static_cast<uint64_t>( _foreground ) << 24 ) | ( static_cast<uint64_t>( _attributes ) << 48 );

    position = y * _columns + x0;
    memcpy( _data[position].Character, c0.c_str(), c0.size() );
    _data[position].CharacterSize = c0.size();
    _data[position].Attributes    = attributes;

    int w = x1 - x0;
    for( int c = 1; c < w - 1; c++ )
    {
        position = y * _columns + ( x0 + c );
        memcpy( _data[position].Character, cFill.c_str(), cFill.size() );
        _data[position].CharacterSize = cFill.size();
        _data[position].Attributes    = attributes;
    }
    position = y * _columns + ( x1 - 1 );
    memcpy( _data[position].Character, c1.c_str(), c1.size() );
    _data[position].CharacterSize = c1.size();
    _data[position].Attributes    = attributes;
}

void framebuffer_t::VLine( uint32_t x, uint32_t y0, uint32_t y1, string_t c0, string_t c1, string_t cFill )
{
    uint64_t attributes =
        _background | ( static_cast<uint64_t>( _foreground ) << 24 ) | ( static_cast<uint64_t>( _attributes ) << 48 );

    uint32_t position;

    position = y0 * _columns + x;
    memcpy( _data[position].Character, c0.c_str(), c0.size() );
    _data[position].CharacterSize = c0.size();
    _data[position].Attributes    = attributes;

    int h = y1 - y0;
    for( int c = 1; c < h - 1; c++ )
    {
        position = ( y0 + c ) * _columns + x;
        memcpy( _data[position].Character, cFill.c_str(), cFill.size() );
        _data[position].CharacterSize = cFill.size();
        _data[position].Attributes    = attributes;
    }

    position = ( y1 - 1 ) * _columns + x;
    memcpy( _data[position].Character, c1.c_str(), c1.size() );
    _data[position].CharacterSize = c1.size();
    _data[position].Attributes    = attributes;
}

void framebuffer_t::DrawRect( uint32_t x, uint32_t y, uint32_t w, uint32_t h, string_t tl, string_t t, string_t tr, string_t r,
                              string_t br, string_t b, string_t bl, string_t l )
{
    uint64_t attributes =
        _background | ( static_cast<uint64_t>( _foreground ) << 24 ) | ( static_cast<uint64_t>( _attributes ) << 48 );

    uint32_t position;

    // Top row
    HLine( y, x, x + w, tl, tr, t );

    // Bottom row
    HLine( y + h - 1, x, x + w, bl, br, b );

    // Left side
    VLine( x, y + 1, y + h - 1, l, l, l );

    // Right side
    VLine( x + w - 1, y + 1, y + h - 1, r, r, r );

    for( int i = 1; i < w - 1; i++ )
    {
        for( int j = 1; j < h - 1; j++ )
        {
            position = ( y + j ) * _columns + ( x + i );

            _data[position].Character[0]  = ' ';
            _data[position].CharacterSize = 1;
            _data[position].Attributes    = attributes;
        }
    }
}

void framebuffer_t::TextLine( uint32_t x, uint32_t y, string_t text )
{
    uint32_t position = y * _columns + x;
    uint64_t attributes =
        _background | ( static_cast<uint64_t>( _foreground ) << 24 ) | ( static_cast<uint64_t>( _attributes ) << 48 );

    for( auto &c : text )
    {
        if( position < _rows * _columns )
        {
            _data[position].Character[0] = ( c );
            _data[position].Attributes   = attributes;
            position++;
        }
    }
}

void framebuffer_t::putc( char ch )
{
    // std::cout << ch;
    // std::cout << "putc( " << std::hex << (uint32_t)ch << std::dec << " " << _cursorX << ", " << _cursorY << "   "
    //           << "w=" << _columns << " "
    //           << "h=" << _rows << " )" << std::endl;
    uint32_t position = _cursorY * _columns + _cursorX;
    // _attributes       = CharacterAttribute::DEFAULT_BG | CharacterAttribute::DEFAULT_FG;
    uint64_t attributes =
        _background | ( static_cast<uint64_t>( _foreground ) << 24 ) | ( static_cast<uint64_t>( _attributes ) << 48 );

    _data[position].Character[0] = ( ch );
    // if( ch == '\r' )
    // {
    //     _cursorX = 0;
    //     _cursorY++;

    //     _cursorY = std::min( _cursorY, _rows - 1);
    // }
    _data[position].Attributes = attributes;
    // _data[position].Attributes   = ;

    _cursorX += 1;

    if( _cursorX >= _columns )
    {
        _cursorX = 0;
        _cursorY++;

        _cursorY = std::min( _cursorY, _rows - 1 );
    }
}

void framebuffer_t::ClearCurrentLine()
{
    uint32_t startPos            = _cursorY * _columns;
    uint32_t endPos              = startPos + _columns;
    uint64_t characterAttributes = CharacterAttribute::DEFAULT_BG | CharacterAttribute::DEFAULT_FG;

    for( uint32_t i = startPos; i < endPos; i++ )
    {
        _data[i].Character[0]  = ' ';
        _data[i].CharacterSize = 1;
        _data[i].Attributes    = characterAttributes << 48;
    }
}

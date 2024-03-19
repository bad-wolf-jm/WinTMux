#include "stdout.h"
#include <windows.h>
#include <consoleapi.h>
#include <fmt/printf.h>

stdout_t::stdout_t()
{
    _codePage = GetConsoleOutputCP();
    SetConsoleOutputCP( 65001 );
    _stream = GetStdHandle( STD_OUTPUT_HANDLE );
    if( _stream == INVALID_HANDLE_VALUE )
    {
    }

    // GetConsoleMode( _stream, (LPDWORD)&_consoleMode );
    // HRESULT hr = SetConsoleMode( _stream, _consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING ) ? S_OK : GetLastError();
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    if( GetConsoleScreenBufferInfo( _stream, &csbi ) )
    {
        _columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        _rows    = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    // Push the current state of the terminal so we can restore
    // after the program is done.
    write( "\x1b[?1049h" );
}

stdout_t::~stdout_t()
{
    // Restore the contents of the terminal.
    write( "\x1b[?1049l" );

    SetConsoleOutputCP( _codePage );
    SetConsoleMode( _stream, _consoleMode );
}

void stdout_t::write( string_t buffer )
{
    DWORD dwBytesWritten{};
    WriteFile( _stream, buffer.c_str(), buffer.size() * sizeof( char_t ), &dwBytesWritten, NULL );
}

void stdout_t::write( string_t::const_iterator begin, string_t::const_iterator end )
{
    write( string_t( begin, end ) );
}

void stdout_t::write( std::vector<glyph_t>::const_iterator begin, std::vector<glyph_t>::const_iterator end )
{
    string_t renderedLine;
    renderedLine.resize( std::distance( begin, end ) * 4 );

    int position = 0;
    for( std::vector<glyph_t>::const_iterator gl = begin; gl < end; gl++ )
    {
        auto const *character     = ( *gl ).Character;
        if(character[0] == '\0')
            continue;

        auto const  characterSize = ( *gl ).CharacterSize;

        std::copy( character, character + characterSize, renderedLine.begin() + position );
        position += characterSize;
    }

    write( renderedLine );
}

void stdout_t::write( uint32_t attributes, uint32_t bg, uint32_t fg, std::vector<glyph_t>::const_iterator begin,
                      std::vector<glyph_t>::const_iterator end )
{
    if( !( attributes & character_attribute::DEFAULT_BG ) )
    {
        uint8_t r = ( bg >> 16 ) & 0xFF;
        uint8_t g = ( bg >> 8 ) & 0xFF;
        uint8_t b = ( bg >> 0 ) & 0xFF;

        write( fmt::sprintf( "\x1b[48;2;%d;%d;%dm", r, g, b ) );
    }

    if( !( attributes & character_attribute::DEFAULT_FG ) )
    {
        uint8_t r = ( fg >> 16 ) & 0xFF;
        uint8_t g = ( fg >> 8 ) & 0xFF;
        uint8_t b = ( fg >> 0 ) & 0xFF;

        write( fmt::sprintf( "\x1b[38;2;%d;%d;%dm", r, g, b ) );
    }

    if( attributes & character_attribute::BOLD )
        write( "\x1B[1m" );

    if( attributes & character_attribute::FAINT )
        write( "\x1B[2m" );

    if( attributes & character_attribute::ITALIC )
        write( "\x1B[3m" );

    if( attributes & character_attribute::UNDERLINE )
        write( "\x1B[4m" );

    if( attributes & character_attribute::SLOW_BLINK )
        write( "\x1B[5m" );

    if( attributes & character_attribute::FAST_BLINK )
        write( "\x1B[6m" );

    if( attributes & character_attribute::REVERSED )
        write( "\x1B[7m" );

    if( attributes & character_attribute::HIDDEN )
        write( "\x1B[8m" );

    if( attributes & character_attribute::STRIKETHROUGH )
        write( "\x1B[9m" );

    write( begin, end );
    write( "\x1b[0m" );
}

void stdout_t::write( character_range_t const &range, std::vector<glyph_t> const &buffer )
{
    uint32_t attributes = range.CharacterAttributes();
    uint32_t foreground = range.Foreground();
    uint32_t background = range.Background();

    write( attributes, background, foreground, buffer.begin() + range.Start, buffer.begin() + range.End );
}

void stdout_t::write( framebuffer_t const &frameBuffer )
{
    write( "\x1b[?25l" ); // hide the cursor
    write( "\x1b[H" );    // move to (0,0)

    auto const &lines  = frameBuffer.Lines();
    auto const &buffer = frameBuffer.Data();
    for( auto const &line : lines )
    {
        for( auto const &range : line )
            write( range, buffer );
    }
}

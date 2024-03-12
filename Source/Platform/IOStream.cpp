#include "IOStream.h"
#include <windows.h>
#include <consoleapi.h>
#include <fmt/printf.h>

stdin_t::stdin_t()
{
    _stream = GetStdHandle( STD_INPUT_HANDLE );
    if( _stream == INVALID_HANDLE_VALUE )
    {
    }

    if( !GetConsoleMode( _stream, (LPDWORD)&_consoleMode ) )
    {
    }

    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if( !SetConsoleMode( _stream, fdwMode ) )
    {
    }
}

stdin_t::~stdin_t()
{
    SetConsoleMode( _stream, _consoleMode );
}

void stdin_t::ProcessEvents()
{
    DWORD               _numInputEvents;
    static INPUT_RECORD inputEvents[128];

    // TODO: Check if there are events pending

    GetNumberOfConsoleInputEvents( _stream, &_numInputEvents );
    if( _numInputEvents == 0 )
        return;

    if( !ReadConsoleInput( _stream, inputEvents, 128, &_numInputEvents ) )
    {
    }

    for( int i = 0; i < _numInputEvents; i++ )
    {
        switch( inputEvents[i].EventType )
        {
        case KEY_EVENT:
        {
            auto const &event             = inputEvents[i].Event.KeyEvent;
            auto const &keyCode           = _keyCodes.GetKeyCode( event.wVirtualKeyCode );
            auto const &platformModifiers = event.dwControlKeyState;
            switch( keyCode.KeyCode )
            {
            case keycode::LEFT_SHIFT:
            case keycode::LEFT_CONTROL:
            case keycode::LEFT_ALT:
            case keycode::LEFT_SUPER:
            case keycode::RIGHT_SHIFT:
            case keycode::RIGHT_CONTROL:
            case keycode::RIGHT_ALT:
            case keycode::RIGHT_SUPER:
                continue;
            default:
            {
                uint32_t modifiers = 0;
                if( platformModifiers & ( RIGHT_ALT_PRESSED | LEFT_ALT_PRESSED ) )
                    modifiers |= ( 1 << static_cast<uint32_t>( modifiers::ALT ) );

                if( platformModifiers & ( RIGHT_CTRL_PRESSED | LEFT_CTRL_PRESSED ) )
                    modifiers |= ( 1 << static_cast<uint32_t>( modifiers::CTRL ) );

                if( platformModifiers & ( SHIFT_PRESSED ) )
                    modifiers |= ( 1 << static_cast<uint32_t>( modifiers::SHIFT ) );

                if( OnKeyPress && inputEvents[i].Event.KeyEvent.bKeyDown )
                    OnKeyPress( keyCode, modifiers );
            }
            }
        }
        break;
        case MOUSE_EVENT:
        {
            auto const &event = inputEvents[i].Event.MouseEvent;
        }
        break;
        case WINDOW_BUFFER_SIZE_EVENT:
        {
            auto const &event = inputEvents[i].Event.WindowBufferSizeEvent;

            auto const columns = event.dwSize.X;
            auto const rows    = event.dwSize.Y;

            if( OnConsoleResize )
                OnConsoleResize( columns, rows );
        }
        break;
        case FOCUS_EVENT:
        case MENU_EVENT:
        default:
            break;
        }
    }
}

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

void stdout_t::write( std::vector<Glyph>::const_iterator begin, std::vector<Glyph>::const_iterator end )
{
    string_t renderedLine;
    renderedLine.resize( std::distance( begin, end ) * 4 );

    int position = 0;
    for( std::vector<Glyph>::const_iterator gl = begin; gl < end; gl++ )
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

void stdout_t::write( uint32_t attributes, uint32_t bg, uint32_t fg, std::vector<Glyph>::const_iterator begin,
                      std::vector<Glyph>::const_iterator end )
{
    if( !( attributes & CharacterAttribute::DEFAULT_BG ) )
    {
        uint8_t r = ( bg >> 16 ) & 0xFF;
        uint8_t g = ( bg >> 8 ) & 0xFF;
        uint8_t b = ( bg >> 0 ) & 0xFF;

        write( fmt::sprintf( "\x1b[48;2;%d;%d;%dm", r, g, b ) );
    }

    if( !( attributes & CharacterAttribute::DEFAULT_FG ) )
    {
        uint8_t r = ( fg >> 16 ) & 0xFF;
        uint8_t g = ( fg >> 8 ) & 0xFF;
        uint8_t b = ( fg >> 0 ) & 0xFF;

        write( fmt::sprintf( "\x1b[38;2;%d;%d;%dm", r, g, b ) );
    }

    if( attributes & CharacterAttribute::BOLD )
        write( "\x1B[1m" );

    if( attributes & CharacterAttribute::FAINT )
        write( "\x1B[2m" );

    if( attributes & CharacterAttribute::ITALIC )
        write( "\x1B[3m" );

    if( attributes & CharacterAttribute::UNDERLINE )
        write( "\x1B[4m" );

    if( attributes & CharacterAttribute::REVERSED )
        write( "\x1B[7m" );

    if( attributes & CharacterAttribute::HIDDEN )
        write( "\x1B[8m" );

    if( attributes & CharacterAttribute::STRIKETHROUGH )
        write( "\x1B[9m" );

    write( begin, end );
    write( "\x1b[0m" );
}

void stdout_t::write( character_range_t const &range, std::vector<Glyph> const &buffer )
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

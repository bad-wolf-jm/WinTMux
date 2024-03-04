#include "TerminalWindow.h"

#include <Windows.h>
#include <fmt/printf.h>

terminal_window_t::terminal_window_t()
{
    HRESULT hr{ E_UNEXPECTED };

    _terminal = { GetStdHandle( STD_OUTPUT_HANDLE ) };

    // Enable Console VT Processing
    DWORD consoleMode{};
    GetConsoleMode( _terminal, &consoleMode );
    hr = SetConsoleMode( _terminal, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING ) ? S_OK : GetLastError();

    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    if( GetConsoleScreenBufferInfo( _terminal, &csbi ) )
    {
        _columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        _rows    = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
}

void terminal_window_t::SetForeground( uint8_t r, uint8_t g, uint8_t b )
{
    string_t command = fmt::sprintf( "\x1b[38;2;%d;%d;%dm", r, g, b );
    Write( command );
}

void terminal_window_t::SetBackground( uint8_t r, uint8_t g, uint8_t b )
{
    string_t command = fmt::sprintf( "\x1b[48;2;%d;%d;%dm", r, g, b );
    Write( command );
}

void terminal_window_t::ResetColors()
{
    Write( "\x1b[0m" );
}

void terminal_window_t::HideCursor()
{
    Write( "\x1b[?25l" );
}

void terminal_window_t::Write( string_t buffer )
{
    DWORD dwBytesWritten{};
    WriteFile( _terminal, buffer.c_str(), buffer.size(), &dwBytesWritten, NULL );
}

void terminal_window_t::Render()
{
    HideCursor();
    Write( "\x1b[H" );
    SetBackground( 75, 75, 75 );
    SetForeground( 200, 200, 200 );

    string_t title = "WORSPACE 1 (DEFAULT)";
    Write( title );

    string_t lineFill( _columns - title.size(), ' ' );
    Write( lineFill );
    for( int i = 1; i < _rows - 1; i++ )
    {
        SetBackground( 50,50,50 );
        string_t fill( _columns, ' ' );
        Write( fill );
    }

    SetBackground( 175, 75, 175 );
    string_t footer( _columns, ' ' );
    Write( footer );

    Write( "\x1b[0m" );
}

int16_t terminal_window_t::Columns()
{
    return _columns;
}

int16_t terminal_window_t::Rows()
{
    return _rows;
}

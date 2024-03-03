#include "TerminalWindow.h"

#include <Windows.h>

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

int16_t terminal_window_t::Columns()
{
    return _columns;
}

int16_t terminal_window_t::Rows()
{
    return _rows;
}

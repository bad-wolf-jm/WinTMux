#include "PTYProcess.h"

int main()
{
    wchar_t szCommand[]{ L"cmd" };
    HRESULT hr{ E_UNEXPECTED };
    HANDLE  hConsole = { GetStdHandle( STD_OUTPUT_HANDLE ) };

    // Enable Console VT Processing
    DWORD consoleMode{};
    GetConsoleMode( hConsole, &consoleMode );
    hr = SetConsoleMode( hConsole, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING ) ? S_OK : GetLastError();
    COORD                      consoleSize{};
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    if( GetConsoleScreenBufferInfo( hConsole, &csbi ) )
    {
        consoleSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        consoleSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    auto terminal = PTYProcess( L"nvim", consoleSize.X, consoleSize.Y );
    terminal.WaitForCompletion( 10 * 1000 );

    return S_OK == hr ? EXIT_SUCCESS : EXIT_FAILURE;
}

#include "Console/TerminalWindow.h"
#include <chrono>
#include <thread>

bool running = true;
bool consoleHandler( int signal )
{
    if( signal == CTRL_C_EVENT )
    {
        running = false;
    }

    return true;
}

int main()
{
    SetConsoleCtrlHandler( (PHANDLER_ROUTINE)consoleHandler, TRUE );
    terminal_window_t _window{};

    // Push the current state of the terminal so we can restore
    // after the program is done.
    _window.Write( "\x1b[?1049h" );
    while( running )
    {
        _window.BeginFrame();
        _window.EndFrame();

        std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    }

    // Restore the contents of the terminal.
    _window.Write( "\x1b[?1049l" );
    return EXIT_SUCCESS;
}

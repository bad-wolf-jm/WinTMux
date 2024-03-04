#include "Console/TerminalWindow.h"
#include "PseudoConsole/PTYProcess.h"
#include <chrono>
#include <iostream>
#include <thread>

bool running = true;
bool consoleHandler(int signal) {

    if (signal == CTRL_C_EVENT) {

        running = false;
    }
    return true;
}

int main()
{
    SetConsoleCtrlHandler((PHANDLER_ROUTINE) consoleHandler, TRUE);
    terminal_window_t _window{};

    _window.Write( "\x1b[?1049h" );
    while( running )
    {
        _window.BeginFrame();
        _window.EndFrame();

        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    }

    _window.Write( "\x1b[?1049l" );
    return EXIT_SUCCESS;
}

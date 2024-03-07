#include "Console/TerminalWindow.h"

#include "Platform/Application.h"
#include <chrono>
#include <thread>

int main()
{
    Application::Initialize();

    for(int i=0; i < 10; i++)
    {
        Application::Instance()->Tick();
    }
    // while(Application::Instance()->Tick())
    // {}
    Application::Shutdown();

#if 0
    // Push the current state of the terminal so we can restore
    // after the program is done.
    _window.Write( "\x1b[?1049h" );
    while( running )
    {
        _window.BeginFrame();
        _window.FrameBuffer().SetForeground( 200, 200, 200 );
        _window.FrameBuffer().SetBackground( 75, 75, 75 );
        _window.FrameBuffer().TextLine( 0, 0, "WORKSPACE 1 (DEFAULT)" );
        _window.FrameBuffer().DrawRect( 10, 20, 50, 25, u8"\u256D", u8"\u2500", u8"\u256E", u8"\u2502", u8"\u256F", u8"\u2500", u8"\u2570", u8"\u2502" );
        _window.EndFrame();

        std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    }

    // Restore the contents of the terminal.
    _window.Write( "\x1b[?1049l" );
#endif
    return EXIT_SUCCESS;
}

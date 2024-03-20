// #include "Console/TerminalWindow.h"

#include "Platform/Application.h"
#include <chrono>
#include <thread>

int main()
{
    //while( !::IsDebuggerPresent() )
    //    ::Sleep( 100 ); // to avoid 100% CPU load
                        
    Application::Initialize();

    while( Application::Instance()->Tick() )
    {
    }

    Application::Shutdown();

    return EXIT_SUCCESS;
}

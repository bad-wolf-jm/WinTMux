// #include "Console/TerminalWindow.h"

#include "Platform/Application.h"
#include <chrono>
#include <thread>

int main()
{
    Application::Initialize();

    while(Application::Instance()->Tick())
    {}
    
    Application::Shutdown();

    return EXIT_SUCCESS;
}

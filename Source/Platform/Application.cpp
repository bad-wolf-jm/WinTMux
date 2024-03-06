#include "Application.h"

#include <stdio.h>
#include <windows.h>
Application::Application()
{
    _stdin.OnKeyPress = []( keycode_t const &keycode, uint32_t modifiers )
    {
        printf( "KeyPress" );
        //
    };
}

std::unique_ptr<Application> Application::_uniqueInstance;

void Application::Initialize()
{
    if( _uniqueInstance != nullptr )
        return;

    _uniqueInstance = std::make_unique<Application>();
}

std::unique_ptr<Application> &Application::Instance()
{
    return _uniqueInstance;
}

bool Application::Tick()
{
    _stdin.ProcessEvents();
    return true;
}

void Application::Shutdown()
{
}

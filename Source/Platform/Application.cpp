#include "Application.h"

#include <stdio.h>
#include <windows.h>

Application::Application()
{
    _stdin.OnKeyPress = [&]( keycode_t const &keycode, uint32_t modifiers )
    {
        if( keycode.KeyCode == keycode::Q )
        {
            _shouldExit = true;
            return;
        }

        _ui.OnKeyPress( keycode, modifiers );
    };

    _stdin.OnConsoleResize = [&]( uint32_t columns, uint32_t rows )
    {
        // Resize the UI
        _ui.Resize( columns, rows );
    };

    _ui.Resize( _stdout.Columns(), _stdout.Rows() );
    _ui.Start();
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

    _ui.Render();

    //_stdout.write( _ui.FrameBuffer() );

    if( _shouldExit )
        _ui.Stop();

    return !_shouldExit;
}

void Application::Shutdown()
{
}

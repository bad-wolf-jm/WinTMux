#include "stdin.h"
#include <windows.h>
#include <consoleapi.h>
#include <fmt/printf.h>

stdin_t::stdin_t()
{
    _stream = GetStdHandle( STD_INPUT_HANDLE );
    if( _stream == INVALID_HANDLE_VALUE )
    {
    }

    if( !GetConsoleMode( _stream, (LPDWORD)&_consoleMode ) )
    {
    }

    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if( !SetConsoleMode( _stream, fdwMode ) )
    {
    }
}

stdin_t::~stdin_t()
{
    SetConsoleMode( _stream, _consoleMode );
}

void stdin_t::ProcessEvents()
{
    DWORD               _numInputEvents;
    static INPUT_RECORD inputEvents[128];

    // TODO: Check if there are events pending

    GetNumberOfConsoleInputEvents( _stream, &_numInputEvents );
    if( _numInputEvents == 0 )
        return;

    if( !ReadConsoleInput( _stream, inputEvents, 128, &_numInputEvents ) )
    {
    }

    for( int i = 0; i < _numInputEvents; i++ )
    {
        switch( inputEvents[i].EventType )
        {
        case KEY_EVENT:
        {
            auto const &event             = inputEvents[i].Event.KeyEvent;
            auto const &keyCode           = _keyCodes.GetKeyCode( event.wVirtualKeyCode );
            auto const &platformModifiers = event.dwControlKeyState;
            switch( keyCode.KeyCode )
            {
            case keycode::LEFT_SHIFT:
            case keycode::LEFT_CONTROL:
            case keycode::LEFT_ALT:
            case keycode::LEFT_SUPER:
            case keycode::RIGHT_SHIFT:
            case keycode::RIGHT_CONTROL:
            case keycode::RIGHT_ALT:
            case keycode::RIGHT_SUPER:
                continue;
            default:
            {
                uint32_t modifiers = 0;
                if( platformModifiers & ( RIGHT_ALT_PRESSED | LEFT_ALT_PRESSED ) )
                    modifiers |= ( 1 << static_cast<uint32_t>( modifiers::ALT ) );

                if( platformModifiers & ( RIGHT_CTRL_PRESSED | LEFT_CTRL_PRESSED ) )
                    modifiers |= ( 1 << static_cast<uint32_t>( modifiers::CTRL ) );

                if( platformModifiers & ( SHIFT_PRESSED ) )
                    modifiers |= ( 1 << static_cast<uint32_t>( modifiers::SHIFT ) );

                if( OnKeyPress && inputEvents[i].Event.KeyEvent.bKeyDown )
                    OnKeyPress( keyCode, modifiers );
            }
            }
        }
        break;
        case MOUSE_EVENT:
        {
            auto const &event = inputEvents[i].Event.MouseEvent;
        }
        break;
        case WINDOW_BUFFER_SIZE_EVENT:
        {
            auto const &event = inputEvents[i].Event.WindowBufferSizeEvent;

            auto const columns = event.dwSize.X;
            auto const rows    = event.dwSize.Y;

            if( OnConsoleResize )
                OnConsoleResize( columns, rows );
        }
        break;
        case FOCUS_EVENT:
        case MENU_EVENT:
        default:
            break;
        }
    }
}


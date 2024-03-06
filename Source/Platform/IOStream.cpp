#include "IOStream.h"
#include <windows.h>

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

    if( !ReadConsoleInput( _stream, inputEvents, 128, &_numInputEvents ) )
    {
    }

    for( int i = 0; i < _numInputEvents; i++ )
    {
        switch( inputEvents[i].EventType )
        {
        case KEY_EVENT:
        {
            auto const &event     = inputEvents[i].Event.KeyEvent;
            auto const &keyCode   = _keyCodes.GetKeyCode( event.wVirtualKeyCode );
            auto const &modifiers = event.dwControlKeyState;
            switch( keyCode.KeyCode )
            {
            case key_codes::LEFT_SHIFT:
            case key_codes::LEFT_CONTROL:
            case key_codes::LEFT_ALT:
            case key_codes::LEFT_SUPER:
            case key_codes::RIGHT_SHIFT:
            case key_codes::RIGHT_CONTROL:
            case key_codes::RIGHT_ALT:
            case key_codes::RIGHT_SUPER:
                continue;
            default:
            {
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
    // }
}

stdout_t::stdout_t()
{
    _codePage = GetConsoleOutputCP();
    SetConsoleOutputCP( 65001 );
    _stream = GetStdHandle( STD_OUTPUT_HANDLE );
    if( _stream == INVALID_HANDLE_VALUE )
    {
    }

    GetConsoleMode( _stream, (LPDWORD)&_consoleMode );
    HRESULT hr = SetConsoleMode( _stream, _consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING ) ? S_OK : GetLastError();
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    if( GetConsoleScreenBufferInfo( _stream, &csbi ) )
    {
        _columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        _rows    = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
}

stdout_t::~stdout_t()
{
    SetConsoleOutputCP( _codePage );
    SetConsoleMode( _stream, _consoleMode );
}

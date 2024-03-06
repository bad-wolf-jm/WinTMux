#include "Application.h"

// #if 0
#include <stdio.h>
#include <windows.h>

static HANDLE       hStdin;
static HANDLE       _terminal{ INVALID_HANDLE_VALUE };
static DWORD        fdwSaveOldMode;
static DWORD        cNumRead, fdwMode, i;
static INPUT_RECORD irInBuf[128];
static int          counter = 0;
static int16_t      _columns{ 0 };
static int16_t      _rows{ 0 };

extern "C" VOID ErrorExit0( LPSTR lpszMessage )
{
    fprintf( stderr, "%s\n", lpszMessage );

    // Restore input mode on exit.

    SetConsoleMode( hStdin, fdwSaveOldMode );

    ExitProcess( 0 );
}

extern "C" VOID KeyEventProc( KEY_EVENT_RECORD ker )
{
    printf( "Key event: " );

    if( ker.bKeyDown )
        printf( "key pressed\n" );
    else
        printf( "key released\n" );
}

extern "C" VOID MouseEventProc( MOUSE_EVENT_RECORD mer )
{
#ifndef MOUSE_HWHEELED
#    define MOUSE_HWHEELED 0x0008
#endif
    printf( "Mouse event: " );

    switch( mer.dwEventFlags )
    {
    case 0:

        if( mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED )
        {
            printf( "left button press \n" );
        }
        else if( mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED )
        {
            printf( "right button press \n" );
        }
        else
        {
            printf( "button press\n" );
        }
        break;
    case DOUBLE_CLICK:
        printf( "double click\n" );
        break;
    case MOUSE_HWHEELED:
        printf( "horizontal mouse wheel\n" );
        break;
    case MOUSE_MOVED:
        printf( "mouse moved\n" );
        break;
    case MOUSE_WHEELED:
        printf( "vertical mouse wheel\n" );
        break;
    default:
        printf( "unknown\n" );
        break;
    }
}

extern "C" VOID ResizeEventProc( WINDOW_BUFFER_SIZE_RECORD wbsr )
{
    printf( "Resize event\n" );
    printf( "Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y );
}

bool running = true;
bool consoleHandler( int signal )
{
    if( signal == CTRL_C_EVENT )
    {
        running = false;
    }

    return true;
}

std::unique_ptr<Application> Application::_uniqueInstance;
void Application::Initialize()
{
    if(_uniqueInstance != nullptr)
        return;

    _uniqueInstance = std::make_unique<Application>();

    hStdin = GetStdHandle( STD_INPUT_HANDLE );
    if( hStdin == INVALID_HANDLE_VALUE )
        ErrorExit0( "GetStdHandle" );

    // Save the current input mode, to be restored on exit.
    if( !GetConsoleMode( hStdin, &fdwSaveOldMode ) )
        ErrorExit0( "GetConsoleMode" );

    // Enable the window and mouse input events.
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if( !SetConsoleMode( hStdin, fdwMode ) )
        ErrorExit0( "SetConsoleMode" );

    HRESULT hr{ E_UNEXPECTED };

    SetConsoleOutputCP( 65001 );
    SetConsoleCtrlHandler( (PHANDLER_ROUTINE)consoleHandler, TRUE );
    _terminal = { GetStdHandle( STD_OUTPUT_HANDLE ) };

    // Enable Console VT Processing
    DWORD consoleMode{};
    GetConsoleMode( _terminal, &consoleMode );
    hr = SetConsoleMode( _terminal, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING ) ? S_OK : GetLastError();
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    if( GetConsoleScreenBufferInfo( _terminal, &csbi ) )
    {
        _columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        _rows    = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
}

std::unique_ptr<Application> &Application::Instance()
{
    return _uniqueInstance;
}

bool Application::Tick()
{
    // while( counter++ <= 100 )
    // {
    // Wait for the events.
    if( !ReadConsoleInput( hStdin, irInBuf, 128, &cNumRead ) )
    {
        ErrorExit0( "ReadConsoleInput" );
        return false;
    }

    // Dispatch the events to the appropriate handler.

    for( i = 0; i < cNumRead; i++ )
    {
        switch( irInBuf[i].EventType )
        {
        case KEY_EVENT: // keyboard input
            KeyEventProc( irInBuf[i].Event.KeyEvent );
            break;
        case MOUSE_EVENT: // mouse input
            MouseEventProc( irInBuf[i].Event.MouseEvent );
            break;
        case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing
            ResizeEventProc( irInBuf[i].Event.WindowBufferSizeEvent );
            break;
        case FOCUS_EVENT: // disregard focus events
        case MENU_EVENT:  // disregard menu events
            break;
        default:
            ErrorExit0( "Unknown event type" );
            break;
        }
    }
    // }

    return running;
}

void Application::Shutdown()
{
    SetConsoleMode( hStdin, fdwSaveOldMode );
}


// #endif
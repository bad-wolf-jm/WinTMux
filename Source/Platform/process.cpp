#include "process.h"

#include <iostream>
#include <ostream>

process_t::process_t( string_t command, framebuffer_t &framebuffer )
    : _columns{ framebuffer.Columns() }
    , _lines{ framebuffer.Rows() }
    , _framebuffer{ framebuffer }
    , _command{ command }
{
    _startupInfo.StartupInfo.cb = sizeof( STARTUPINFOEXA );

    _console = std::make_unique<console_t>( _columns, _lines );

    size_t attributeListSize = 0;
    InitializeProcThreadAttributeList( NULL, 1, 0, &attributeListSize );

    _startupInfoAttributeList = reinterpret_cast<LPPROC_THREAD_ATTRIBUTE_LIST>( malloc( attributeListSize ) );
    if( InitializeProcThreadAttributeList( _startupInfoAttributeList, 1, 0, &attributeListSize ) )
    {
        _startupInfo.lpAttributeList = _startupInfoAttributeList;
        HRESULT hr                   = UpdateProcThreadAttribute( _startupInfo.lpAttributeList, 0, PROC_THREAD_ATTRIBUTE_PSEUDOCONSOLE,
                                                                  _console->handle(), sizeof( HPCON ), NULL, NULL );
        if( !hr )
        {
            LPTSTR errorText = NULL;
            FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
                           NULL,                                        // unused with FORMAT_MESSAGE_FROM_SYSTEM
                           GetLastError(),                              //
                           MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), //
                           (LPTSTR)&errorText,                          // output
                           0,                                           // minimum size for output buffer
                           NULL );                                      // arguments - see note

            if( NULL != errorText )
            {
                // ... do something with the string `errorText` - log it, display it to the user, etc.
                std::cout << "XXX"
                          << " " << errorText << std::endl;
                // release memory allocated by FormatMessage()
                LocalFree( errorText );
                errorText = NULL;
            }
        }
    }

    StartProcess();
}

process_t::~process_t()
{
    // Now safe to clean-up client app's process-info & thread
    CloseHandle( _clientProcess.hThread );
    CloseHandle( _clientProcess.hProcess );

    // Cleanup attribute list
    DeleteProcThreadAttributeList( _startupInfo.lpAttributeList );
    free( _startupInfo.lpAttributeList );
}

void process_t::WaitForCompletion( int32_t timeout )
{
    // Wait up to 10s for ping process to complete
    DWORD result = WaitForSingleObject( _clientProcess.hThread, timeout );
    if( result == WAIT_FAILED )
    {
        LPTSTR errorText = NULL;
        FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL,                                        // unused with FORMAT_MESSAGE_FROM_SYSTEM
                       GetLastError(),                              //
                       MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), //
                       (LPTSTR)&errorText,                          // output
                       0,                                           // minimum size for output buffer
                       NULL );                                      // arguments - see note

        if( NULL != errorText )
        {
            std::cout << "TTT " << errorText << std::endl;
            LocalFree( errorText );
            errorText = NULL;
        }
    }
}

void process_t::StartProcess()
{
    SetEnvironmentVariable( TEXT( "TERM" ), TEXT( "dumb" ) );
    CreateProcessA( NULL,                                       // No module name - use Command Line
                    reinterpret_cast<LPSTR>( _command.data() ), // Command Line
                    NULL,                                       // Process handle not inheritable
                    NULL,                                       // Thread handle not inheritable
                    FALSE,                                      // Inherit handles
                    EXTENDED_STARTUPINFO_PRESENT,               // Creation flags
                    NULL,                                       // Use parent's environment block
                    NULL,                                       // Use parent's starting directory
                    &_startupInfo.StartupInfo,                  // Pointer to STARTUPINFO
                    &_clientProcess );                          // Pointer to PROCESS_INFORMATION
}

void __cdecl process_t::PipeListener()
{
    HANDLE hPipe{ _console->std_out()->read_end() };
    // HANDLE hConsole{ GetStdHandle( STD_OUTPUT_HANDLE ) };

    const DWORD BUFF_SIZE{ 512 };
    char        szBuffer[BUFF_SIZE]{};

    // DWORD dwBytesWritten{};
    DWORD dwBytesRead{};
    BOOL  fRead{ FALSE };

    PeekNamedPipe( hPipe, NULL, 0, NULL, &dwBytesRead, NULL );

    if( dwBytesRead == 0 )
        return;

    fRead = ReadFile( hPipe, szBuffer, BUFF_SIZE, &dwBytesRead, NULL );

    _parser.parse( _framebuffer, (unsigned char *)szBuffer, dwBytesRead );
}

void process_t::OnKeyPress(keycode_t const& keyCode, uint32_t modifiers)
{
}


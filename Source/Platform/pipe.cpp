#include "pipe.h"

#include <fileapi.h>
#include <handleapi.h>
#include <iostream>
#include <namedpipeapi.h>
#include <ostream>
#include <winerror.h>

pipe_t::pipe_t()
//     : _columns{ columns }
//     , _lines{ lines }
//     , _command{ command }
{
    CreatePipe( &_rstream, &_wstream, NULL, 0 );
    //     _startupInfo.StartupInfo.cb = sizeof( STARTUPINFOEXA );
    //
    //     CreateConsole( _columns, _lines );
    //     _processIsActive    = true;
    //     _pipeListenerThread = std::thread( &pipe_t::PipeListener, this );
    //
    //     size_t attributeListSize = 0;
    //     InitializeProcThreadAttributeList( NULL, 1, 0, &attributeListSize );
    //
    //     _startupInfoAttributeList = reinterpret_cast<LPPROC_THREAD_ATTRIBUTE_LIST>( malloc( attributeListSize ) );
    //     if( InitializeProcThreadAttributeList( _startupInfoAttributeList, 1, 0, &attributeListSize ) )
    //     {
    //         _startupInfo.lpAttributeList = _startupInfoAttributeList;
    //         HRESULT hr = UpdateProcThreadAttribute( _startupInfo.lpAttributeList, 0, PROC_THREAD_ATTRIBUTE_PSEUDOCONSOLE,
    //         _console,
    //                                                 sizeof( HPCON ), NULL, NULL );
    //         if( !hr )
    //         {
    //             LPTSTR errorText = NULL;
    //             FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
    //                            NULL, // unused with FORMAT_MESSAGE_FROM_SYSTEM
    //                            GetLastError(), MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
    //                            (LPTSTR)&errorText, // output
    //                            0,                  // minimum size for output buffer
    //                            NULL );             // arguments - see note
    //
    //             if( NULL != errorText )
    //             {
    //                 // ... do something with the string `errorText` - log it, display it to the user, etc.
    //                 std::cout << "XXX"
    //                           << " " << errorText << std::endl;
    //                 // release memory allocated by FormatMessage()
    //                 LocalFree( errorText );
    //                 errorText = NULL;
    //             }
    //         }
    //     }
    //
    //     StartProcess();
}

pipe_t::~pipe_t()
{
    // Close the listening thread

    // Now safe to clean-up client app's process-info & thread
    //     CloseHandle( _clientProcess.hThread );
    //     CloseHandle( _clientProcess.hProcess );
    //
    //     // Close ConPTY - this will terminate client process if running
    //     ClosePseudoConsole( _console );
    //
    // Clean-up the pipes
    if( INVALID_HANDLE_VALUE != _rstream )
        CloseHandle( _rstream );

    if( INVALID_HANDLE_VALUE != _wstream )
        CloseHandle( _wstream );
    //
    //     // Cleanup attribute list
    //     DeleteProcThreadAttributeList( _startupInfo.lpAttributeList );
    //     free( _startupInfo.lpAttributeList );
}

// void pipe_t::WaitForCompletion( int32_t timeout )
// {
//     // Wait up to 10s for ping process to complete
//     DWORD result = WaitForSingleObject( _clientProcess.hThread, timeout );
//     if( result == WAIT_FAILED )
//     {
//         LPTSTR errorText = NULL;
//         FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
//                        NULL, // unused with FORMAT_MESSAGE_FROM_SYSTEM
//                        GetLastError(), MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
//                        (LPTSTR)&errorText, // output
//                        0,                  // minimum size for output buffer
//                        NULL );             // arguments - see note
//
//         if( NULL != errorText )
//         {
//             std::cout << "TTT " << errorText << std::endl;
//             LocalFree( errorText );
//             errorText = NULL;
//         }
//     }
//     _processIsActive = false;
//     _pipeListenerThread.join();
// }

// void pipe_t::CreateConsole( int16_t columns, int16_t lines )
// {
//     HANDLE consoleStdIn{ INVALID_HANDLE_VALUE };
//     HANDLE consoleStdOut{ INVALID_HANDLE_VALUE };
//
//     CreatePipes( consoleStdIn, consoleStdOut );
//     COORD consoleSize{ columns, lines };
//
//     // Create the Pseudo Console of the required size, attached to the PTY-end
//     // of the pipes
//     HRESULT hr = CreatePseudoConsole( consoleSize, consoleStdIn, consoleStdOut, 0, &_console );
//
//     // Note: We can close the handles to the PTY-end of the pipes here
//     // because the handles are dup'ed into the ConHost and will be released
//     // when the ConPTY is destroyed.
//     if( INVALID_HANDLE_VALUE != consoleStdOut )
//         CloseHandle( consoleStdOut );
//
//     if( INVALID_HANDLE_VALUE != consoleStdIn )
//         CloseHandle( consoleStdIn );
// }

// void pipe_t::StartProcess()
// {
//     CreateProcessA( NULL,                                       // No module name - use Command Line
//                     reinterpret_cast<LPSTR>( _command.data() ), // Command Line
//                     NULL,                                       // Process handle not inheritable
//                     NULL,                                       // Thread handle not inheritable
//                     FALSE,                                      // Inherit handles
//                     EXTENDED_STARTUPINFO_PRESENT,               // Creation flags
//                     NULL,                                       // Use parent's environment block
//                     NULL,                                       // Use parent's starting directory
//                     &_startupInfo.StartupInfo,                  // Pointer to STARTUPINFO
//                     &_clientProcess );                          // Pointer to PROCESS_INFORMATION
// }

// bool pipe_t::CreatePipes( HANDLE &consoleStdIn, HANDLE &consoleStdOut )
// {
//     HRESULT hr{ E_UNEXPECTED };
// 
//     return CreatePipe( &consoleStdIn, &_consoleStdIn, NULL, 0 ) && CreatePipe( &_consoleStdOut, &consoleStdOut, NULL, 0 );
// }

// void __cdecl pipe_t::PipeListener()
// {
//     HANDLE hPipe{ _consoleStdOut };
//     HANDLE hConsole{ GetStdHandle( STD_OUTPUT_HANDLE ) };
// 
//     const DWORD BUFF_SIZE{ 512 };
//     char        szBuffer[BUFF_SIZE]{};
// 
//     DWORD dwBytesWritten{};
//     DWORD dwBytesRead{};
//     BOOL  fRead{ FALSE };
//     do
//     {
//         // Read from the pipe
//         fRead = ReadFile( hPipe, szBuffer, BUFF_SIZE, &dwBytesRead, NULL );
// 
//         // Write received text to the Console
//         // Note: Write to the Console using WriteFile(hConsole...), not
//         // printf()/puts() to prevent partially-read VT sequences from corrupting
//         // output
//         WriteFile( hConsole, szBuffer, dwBytesRead, &dwBytesWritten, NULL );
//         std::cout << dwBytesRead << std::endl;
// 
//     } while( _processIsActive && fRead && dwBytesRead >= 0 );
// }

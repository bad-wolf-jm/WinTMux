#pragma once

#include <SDKDDKVer.h>
#include <Windows.h>
#include <errhandlingapi.h>
#include <process.h>
#include <processthreadsapi.h>
#include <stdint.h>
#include <tchar.h>


#include <winbase.h>

#include "Platform/pipe.h"

class console_t
{
  public:
    //console_t( string_t command, uint32_t columns, uint32_t lines );
    console_t( uint32_t columns, uint32_t lines );
    ~console_t();

    //void WaitForCompletion( int32_t timeout = 0 );

  private:
    //string_t _command = "";
    uint32_t _columns{ 0 };
    uint32_t _lines{ 0 };

    void*  _console{ (void*)-1 };       // Handle to the TTY
    pipe_t _stdin;//{ INVALID_HANDLE_VALUE };  // Console stdin
    pipe_t _stdout;//{ INVALID_HANDLE_VALUE }; // Console stdout

//    PROCESS_INFORMATION          _clientProcess{};
//    STARTUPINFOEXA               _startupInfo{};
//    LPPROC_THREAD_ATTRIBUTE_LIST _startupInfoAttributeList;

//    bool        _processIsActive = true;
//    std::thread _pipeListenerThread;

  private:
//     void StartProcess();
//     void CreateConsole( int16_t columns, int16_t lines );
//     bool CreatePipes( HANDLE &consoleStdIn, HANDLE &consoleStdOut );
//     void PipeListener();
};

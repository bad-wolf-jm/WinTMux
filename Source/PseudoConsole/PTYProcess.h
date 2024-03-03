#pragma once
#include <SDKDDKVer.h>
#include <Windows.h>
#include <errhandlingapi.h>
#include <process.h>
#include <processthreadsapi.h>
#include <stdint.h>
#include <tchar.h>

#include <thread>

#include <winbase.h>

#include "Core/String.h"

class PTYProcess
{
  public:
    PTYProcess( string_t command, uint32_t columns, uint32_t lines );
    ~PTYProcess();

    void WaitForCompletion( int32_t timeout = 0 );

  private:
    string_t _command = "";
    uint32_t _columns{ 0 };
    uint32_t _lines{ 0 };

    HPCON  _console{ INVALID_HANDLE_VALUE };       // Handle to the TTY
    HANDLE _consoleStdIn{ INVALID_HANDLE_VALUE };  // Console stdin
    HANDLE _consoleStdOut{ INVALID_HANDLE_VALUE }; // Console stdout

    PROCESS_INFORMATION          _clientProcess{};
    STARTUPINFOEXA               _startupInfo{};
    LPPROC_THREAD_ATTRIBUTE_LIST _startupInfoAttributeList;

    bool        _processIsActive = true;
    std::thread _pipeListenerThread;

  private:
    void StartProcess();
    void CreateConsole( int16_t columns, int16_t lines );
    bool CreatePipes( HANDLE &consoleStdIn, HANDLE &consoleStdOut );
    void PipeListener();
};

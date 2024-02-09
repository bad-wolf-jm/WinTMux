#pragma once


#include <SDKDDKVer.h>
#include <Windows.h>
#include <cstdio>
#include <errhandlingapi.h>
#include <iostream>
#include <ostream>
#include <process.h>
#include <processthreadsapi.h>
#include <stdint.h>
#include <tchar.h>

#include <string>
#include <thread>

#include <winbase.h>

using string_t = std::wstring;
using char_t   = wchar_t;

class PTYProcess
{
  public:
    PTYProcess( string_t command, int16_t columns, int16_t lines );
    ~PTYProcess();

    void WaitForCompletion( int32_t timeout = 0 );

  private:
    string_t _command = L"";
    int16_t  _columns{ 0 };
    int16_t  _lines{ 0 };

    HPCON  _console{ INVALID_HANDLE_VALUE };      // Handle to the TTY
    HANDLE _consoleStdIn{ INVALID_HANDLE_VALUE };  // Console stdin
    HANDLE _consoleStdOut{ INVALID_HANDLE_VALUE }; // Console stdout
    HANDLE _consoleStdErr{ INVALID_HANDLE_VALUE }; // Console stderr

    PROCESS_INFORMATION          _clientProcess{};
    STARTUPINFOEXW               _startupInfo{};
    LPPROC_THREAD_ATTRIBUTE_LIST _startupInfoAttributeList;

    bool        _processIsActive = true;
    std::thread _pipeListenerThread;

  private:
    void StartProcess();
    void CreateConsole( int16_t columns, int16_t lines );
    bool CreatePipes( HANDLE &consoleStdIn, HANDLE &consoleStdOut, HANDLE &consoleStdErr );
    void PipeListener();
};

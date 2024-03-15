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
#include "Platform/console.h"
#include "VtParser/Parser.h"

class process_t
{
  public:
    process_t( string_t command, framebuffer_t &framebuffer );
    ~process_t();

    void WaitForCompletion( int32_t timeout = 0 );
    void PipeListener();

  private:
    string_t _command = "";
    uint32_t _columns{ 0 };
    uint32_t _lines{ 0 };

    std::unique_ptr<console_t> _console;

    PROCESS_INFORMATION          _clientProcess{};
    STARTUPINFOEXA               _startupInfo{};
    LPPROC_THREAD_ATTRIBUTE_LIST _startupInfoAttributeList;

    bool        _processIsActive = true;
    std::thread _pipeListenerThread;

  private:
    void StartProcess();

    Vt100Parser    _parser;
    framebuffer_t &_framebuffer;
};

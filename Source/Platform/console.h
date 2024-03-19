#pragma once

#include <SDKDDKVer.h>
#include <Windows.h>
#include <errhandlingapi.h>
#include <memory>
#include <process.h>
#include <processthreadsapi.h>
#include <stdint.h>
#include <tchar.h>

#include <winbase.h>

#include "Platform/pipe.h"

class console_t
{
  public:
    console_t() = default;
    console_t( int16_t columns, int16_t lines );
    ~console_t();

    std::unique_ptr<pipe_t> &std_in();
    std::unique_ptr<pipe_t> &std_out();

    void *handle();
    void Resize(uint32_t rows, uint32_t columns);
    void  write( char c );

    ringbuffer_t<uint8_t> &read();

  private:
    int16_t _columns{ 0 };
    int16_t _lines{ 0 };

    void *_console{ (void *)-1 }; // Handle to the TTY

    std::unique_ptr<pipe_t> _stdin;  // Console stdin
    std::unique_ptr<pipe_t> _stdout; // Console stdout

    ringbuffer_t<uint8_t> _stdoutBuffer;
};

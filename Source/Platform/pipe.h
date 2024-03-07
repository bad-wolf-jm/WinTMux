#pragma once

//#include <SDKDDKVer.h>
//#include <Windows.h>
//#include <errhandlingapi.h>
//#include <process.h>
//#include <processthreadsapi.h>
//#include <tchar.h>
//#include <thread>
//#include <winbase.h>


class pipe_t
{
  public:
    pipe_t();
    ~pipe_t();

    void* _wstream{ (void*)-1 };  // Console stdin
    void* _rstream{ (void*)-1 };  // Console stdin
};

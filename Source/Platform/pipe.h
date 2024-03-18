#pragma once

#include "Core/String.h"
#include "Core/ringbuffer.h"

class pipe_t
{
  public:
    pipe_t();
    ~pipe_t();

    void *read_end();
    void *write_end();
    void  close_read();
    void  close_write();

    void   write( char c );
    void   write( string_t buffer );
    size_t chars_ready();
    void   read( ringbuffer_t<uint8_t> &buffer );

  private:
    void *_wstream{ (void *)-1 };
    void *_rstream{ (void *)-1 };
};

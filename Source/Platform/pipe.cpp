#include "pipe.h"

#include <Windows.h>
#include <fileapi.h>
#include <handleapi.h>
#include <namedpipeapi.h>
#include <winerror.h>

pipe_t::pipe_t()
{
    CreatePipe( &_rstream, &_wstream, NULL, 0 );
}

pipe_t::~pipe_t()
{
    // Clean-up the pipes
    close_read();
    close_write();
}

void *pipe_t::read_end()
{
    return _rstream;
}

void *pipe_t::write_end()
{
    return _wstream;
}

void pipe_t::close_read()
{
    if( INVALID_HANDLE_VALUE != _rstream )
        CloseHandle( _rstream );

    _rstream = INVALID_HANDLE_VALUE;
}

void pipe_t::close_write()
{
    if( INVALID_HANDLE_VALUE != _wstream )
        CloseHandle( _wstream );

    _wstream = INVALID_HANDLE_VALUE;
}

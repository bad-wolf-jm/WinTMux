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

void pipe_t::write( char c )
{
    DWORD bytesWritten;

    WriteFile( _wstream, &c, 1, &bytesWritten, NULL );
}

void pipe_t::write( string_t buffer )
{
    DWORD bytesWritten{};
    WriteFile( _wstream, buffer.c_str(), buffer.size() * sizeof( char_t ), &bytesWritten, NULL );
}

size_t pipe_t::chars_ready()
{
    DWORD bytesRead{};

    PeekNamedPipe( _rstream, NULL, 0, NULL, &bytesRead, NULL );

    return static_cast<size_t>( bytesRead );
}

void pipe_t::read( ringbuffer_t<uint8_t> &buffer )
{
    size_t availableInPipe = chars_ready();

    while( availableInPipe > 0 && buffer.available_size() > 0 )
    {
        const size_t readBufferSize = 1024;
        size_t       bytesToRead    = std::min( buffer.available_size(), readBufferSize );

        char  readBuffer[readBufferSize] = {};
        BOOL  readSuccess                = FALSE;
        DWORD bytesRead                  = 0;

        readSuccess = ReadFile( _rstream, readBuffer, bytesToRead, &bytesRead, NULL );

        for( int i = 0; i < bytesRead; i++ )
            buffer.push_back( readBuffer[i] );

        availableInPipe = chars_ready();
    }
}
uint32_t pipe_t::read( std::vector<char> &inputBuffer )
{
    size_t availableInPipe  = chars_ready();
    size_t positionInBuffer = 0;
    size_t inputBufferSize  = inputBuffer.size();

    while( availableInPipe > 0 && positionInBuffer < inputBufferSize )
    {
        // const size_t readBufferSize = 1024;
        // char  readBuffer[readBufferSize] = {};
        DWORD bytesToRead = static_cast<DWORD>( inputBufferSize - positionInBuffer );
        BOOL  readSuccess = FALSE;
        DWORD bytesRead   = 0;

        readSuccess = ReadFile( _rstream, inputBuffer.data() + positionInBuffer, bytesToRead, &bytesRead, NULL );

        positionInBuffer += bytesRead; // l //  / sizeof( _Ty );
        //std::cout << "bytesRead=" << bytesRead << std::endl;
        // for( int i = 0; i < bytesRead; i++ )
        //     buffer.push_back( readBuffer[i] );

        availableInPipe = chars_ready();
    }

        //std::cout << "positionInBuffer=" << positionInBuffer << std::endl;
    return positionInBuffer;
}

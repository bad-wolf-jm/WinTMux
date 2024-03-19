#include "console.h"
#include <consoleapi.h>
#include <handleapi.h>

console_t::console_t( int16_t columns, int16_t lines )
    : _stdoutBuffer( 1024 * 1024 )
{
    _stdin  = std::make_unique<pipe_t>();
    _stdout = std::make_unique<pipe_t>();

    COORD consoleSize{ columns, lines };

    // Create the Pseudo Console of the required size, attached to the PTY-end
    // of the pipes
    HRESULT hr = CreatePseudoConsole( consoleSize, _stdin->read_end(), _stdout->write_end(), 0, &_console );

    // Note: We can close the handles to the PTY-end of the pipes here
    // because the handles are dup'ed into the ConHost and will be released
    // when the ConPTY is destroyed.
    _stdin->close_read();
    _stdout->close_write();

    //_stdinBuffer = ringbuffer_t<uint8_t>(1024);
}

console_t::~console_t()
{
    ClosePseudoConsole( _console );
}

std::unique_ptr<pipe_t> &console_t::std_in()
{
    return _stdin;
}

std::unique_ptr<pipe_t> &console_t::std_out()
{
    return _stdout;
}

void *console_t::handle()
{
    return _console;
}

void console_t::write( char c )
{
    _stdin->write( c );
}

ringbuffer_t<uint8_t> &console_t::read()
{
    _stdout->read( _stdoutBuffer );

    return _stdoutBuffer;
}

void console_t::Resize( uint32_t rows, uint32_t columns )
{
    std::cout << "UUU Rows=" << rows << ", Columns=" << columns << std::endl;
    if( _console == INVALID_HANDLE_VALUE )
        return;

    COORD consoleSize{};
    consoleSize.X = static_cast<SHORT>( columns );
    consoleSize.Y = static_cast<SHORT>( rows );

    ResizePseudoConsole( _console, consoleSize );
}

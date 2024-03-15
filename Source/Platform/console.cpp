#include "console.h"

console_t::console_t( int16_t columns, int16_t lines )
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

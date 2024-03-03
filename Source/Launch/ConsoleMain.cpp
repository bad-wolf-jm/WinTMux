#include <iostream>

#include "PseudoConsole/PTYProcess.h"
#include "Console/TerminalWindow.h"

int main()
{
    terminal_window_t _window{};

    std::cout << _window.Columns() << " " <<  _window.Rows() << std::endl;

    return EXIT_SUCCESS;
}

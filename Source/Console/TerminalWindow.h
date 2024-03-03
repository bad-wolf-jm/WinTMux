#pragma once

#include <Windows.h>
#include <stdint.h>

class terminal_window_t
{
  public:
    terminal_window_t();

    int16_t Columns();
    int16_t Rows();

  private:
    int16_t _columns{ 0 };
    int16_t _rows{ 0 };

    HANDLE _terminal{ INVALID_HANDLE_VALUE };
};
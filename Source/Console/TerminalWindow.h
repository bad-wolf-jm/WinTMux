#pragma once

#include <Windows.h>
#include <stdint.h>

#include "Core/String.h"

class terminal_window_t
{
  public:
    terminal_window_t();

    int16_t Columns();
    int16_t Rows();

    void Write( string_t buffer );
    void Render();

    void SetForeground( uint8_t r, uint8_t g, uint8_t b );
    void SetBackground( uint8_t r, uint8_t g, uint8_t b );
    void ResetColors();
    void HideCursor();

  private:
    int16_t _columns{ 0 };
    int16_t _rows{ 0 };

    HANDLE _terminal{ INVALID_HANDLE_VALUE };
};
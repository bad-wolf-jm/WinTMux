#pragma once

// #include "MainWindow.h"
#include "Core/String.h"

class MainWindow;

class CommandLine
{
  public:
    CommandLine( MainWindow *parent );

    inline float Height()
    {
        return _height;
    }

    inline void SetHeight( float height )
    {
        _height = height;
    }

    void KeyPress( int keyCode, int mods );
    void Render();

  private:
    string_t    _currentCommand = "";
    int         _cursorPosition = 0;
    float       _height         = 25.0f;
    MainWindow *_window         = nullptr;
};

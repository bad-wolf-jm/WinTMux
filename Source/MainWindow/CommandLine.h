#pragma once

#include "Core/String.h"

class MainWindow;

class CommandLine
{
  public:
    CommandLine( MainWindow *parent );

    float Height();
    void  SetHeight( float height );

    void KeyPress( int keyCode, int mods );
    void Render();

  public:
    string_t    _currentCommand = "";
    int         _cursorPosition = 0;
    float       _height         = 25.0f;
    MainWindow *_window         = nullptr;
};

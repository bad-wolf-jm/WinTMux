#pragma once

#include "imgui.h"
#include "CommandLine.h"

class MainWindow
{
  public:
    MainWindow();

    inline float FontSize() { return _fontSize; }
    void Render();

  private:
    void RenderHeader();
    void RenderWorkspace();
    void RenderCommandLine();

  private:
    float _headerHeight      = 25.0f;
    float _commandLineHeight = 25.0f;
    bool  _windowIsOpen      = true;

    ImVec2 _windowSize{};
    float  _fontSize = 16.0f;

  private :
    CommandLine _commandLine;
};

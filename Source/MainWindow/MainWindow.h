#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include "imgui.h"
#include "CommandLine.h"
#include "Workspace/Workspace.h"

class MainWindow
{
  public:
    MainWindow();

    inline float FontSize() { return _fontSize; }
    void Render();
    
    void OpenWorkspace(string_t name);
    void CloseWorkspace(string_t name);
    Workspace &CurrentWorkspace();

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
    std::shared_ptr<CommandLine> _commandLine;
    std::vector<std::shared_ptr<Workspace>> _workspaces;
    int _currentWorkspace = -1;

};

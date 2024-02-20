#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "CommandLine.h"
#include "Core/Modes.h"
#include "MainWindow/IOverlay.h"
#include "MainWindow/TerminalSelectorOverlay.h"
#include "MainWindow/WorkspaceSelectorOverlay.h"
#include "Workspace/Workspace.h"
#include "imgui.h"

class MainWindow
{
  public:
    MainWindow();

    inline float FontSize()
    {
        return _fontSize;
    }
    void Render();

    void       OpenWorkspace( string_t name );
    void       CloseWorkspace( string_t name );
    Workspace &CurrentWorkspace();

  public:
    eInputMode Mode = eInputMode::Normal;

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

  public:
    std::shared_ptr<CommandLine>            _commandLine;
    std::vector<std::shared_ptr<Workspace>> _workspaces;

    std::shared_ptr<IOverlay> _workspaceSelector = nullptr;
    std::shared_ptr<IOverlay> _terminalSelector  = nullptr;

    std::shared_ptr<IOverlay> _displayedOverlay = nullptr;

    int _currentWorkspace = -1;
};

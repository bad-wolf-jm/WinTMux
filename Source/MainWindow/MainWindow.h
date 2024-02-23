#pragma once

#include <memory>
#include <vector>

#include "CommandLine.h"
#include "Core/Modes.h"
#include "MainWindow/TerminalSelectorOverlay.h"
#include "MainWindow/WorkspaceSelectorOverlay.h"
#include "Workspace/Workspace.h"
#include "imgui.h"

enum class eOverlayType
{
    NONE,
    WORKSPACE_SELECTOR,
    TERMINAL_SELECTOR
};

class MainWindow
{
  public:
    MainWindow();

    inline float FontSize()
    {
        return _fontSize;
    }
    void Render();

    void OnKeyPress( KeyCode const &keyCode, uint32_t modifiers );

    void ExecuteCurrentCommand();
    void OpenWorkspace( string_t name );
    void CloseWorkspace( string_t name );

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

    bool _commandInputMode = false;

    std::shared_ptr<WorkspaceSelectorOverlay> _workspaceSelectorOverlay = nullptr;
    std::shared_ptr<TerminalSelectorOverlay>  _terminalSelectorOverlay  = nullptr;

    // std::shared_ptr<IOverlay> _displayedOverlay = nullptr;
    eOverlayType _displayedOverlay = eOverlayType::NONE;
    int          _currentWorkspace = -1;
};

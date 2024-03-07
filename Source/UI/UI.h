#pragma once

#include <memory>
#include <vector>

// #include "CommandLine.h"
#include "Core/Modes.h"
// #include "MainWindow/TerminalSelectorOverlay.h"
// #include "MainWindow/WorkspaceSelectorOverlay.h"
#include "Workspace.h"
#include "Console/FrameBuffer.h"
#include "Core/KeyCodes.Console.h"
// #include "imgui.h"

enum class eOverlayType
{
    NONE,
    WORKSPACE_SELECTOR,
    TERMINAL_SELECTOR
};

class UI
{
  public:
    UI();

    void Render();
    void Resize(uint32_t columns, uint32_t rows);

    void OnKeyPress( keycode_t const &keyCode, uint32_t modifiers );

    void ExecuteCurrentCommand();
    void OpenWorkspace( string_t name );
    void CloseWorkspace( string_t name );

    Workspace &CurrentWorkspace();
    framebuffer_t &FrameBuffer();
    // void       SetFonts( ImFont *normalFont, ImFont *boldFont, ImFont *italicFont, ImFont *boldItalicFont );

  public:
    eInputMode Mode = eInputMode::Normal;

  private:
    void RenderHeader();
    void RenderWorkspace();
    void RenderCommandLine();

  private:
    // float _headerHeight      = 25.0f;
    // float _commandLineHeight = 25.0f;
    // bool  _windowIsOpen      = true;

    // ImVec2 _windowSize{};
    // float  _fontSize = 16.0f;

    // ImFont *_normalFont     = nullptr;
    // ImFont *_boldFont       = nullptr;
    // ImFont *_italicFont     = nullptr;
    // ImFont *_boldItalicFont = nullptr;

  public:
    // std::shared_ptr<CommandLine>            _commandLine;
    std::vector<std::shared_ptr<Workspace>> _workspaces;

    bool _commandInputMode = false;

    framebuffer_t _framebuffer;
    // std::shared_ptr<WorkspaceSelectorOverlay> _workspaceSelectorOverlay = nullptr;
    // std::shared_ptr<TerminalSelectorOverlay>  _terminalSelectorOverlay  = nullptr;

    // std::shared_ptr<IOverlay> _displayedOverlay = nullptr;
    eOverlayType _displayedOverlay = eOverlayType::NONE;
    int          _currentWorkspace = -1;
};

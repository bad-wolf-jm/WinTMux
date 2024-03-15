#pragma once

#include <memory>
#include <vector>

// #include "CommandLine.h"
// #include "Core/Modes.h"
// #include "MainWindow/TerminalSelectorOverlay.h"
// #include "MainWindow/WorkspaceSelectorOverlay.h"
#include "Console/FrameBuffer.h"
#include "Core/KeyCodes.h"
#include "Platform/process.h"
#include "Workspace.h"
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
    void Resize( uint32_t columns, uint32_t rows );
    void Start();
    void Stop();

    void OnKeyPress( keycode_t const &keyCode, uint32_t modifiers );

    framebuffer_t &FrameBuffer();

  public:
    eInputMode Mode = eInputMode::Normal;

    void RenderHeader();

  private:
    bool _displayTerminal = false;

  public:
    framebuffer_t _framebuffer;

    framebuffer_t _bgTerminalBuffer;

    int32_t       _fgTerminalWidth       = 0;
    int32_t       _fgTerminalHeight      = 0;
    int32_t       _fgTerminalInnerWidth  = 0;
    int32_t       _fgTerminalInnerHeight = 0;
    framebuffer_t _fgTerminalBuffer;

    std::shared_ptr<process_t> _bgTerminal = nullptr;
    std::shared_ptr<process_t> _fgTerminal = nullptr;
};

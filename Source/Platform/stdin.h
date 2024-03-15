#pragma once

#include <cstdint>
#include <functional>
#include <vector>

#include "Console/Framebuffer.h"
#include "Core/Glyph.h"
#include "Core/KeyCodes.h"
#include "Core/String.h"

using handle_t = void *;

class stdin_t
{
  public:
    stdin_t();
    ~stdin_t();

  public:
    using key_event_handler_t    = std::function<void( keycode_t const &, uint32_t )>;
    using resize_event_handler_t = std::function<void( uint32_t, uint32_t )>;

    resize_event_handler_t OnConsoleResize{};
    key_event_handler_t    OnKeyPress{};

  public:
    void ProcessEvents();

  private:
    handle_t        _stream;
    uint32_t        _consoleMode;
    KeyboardHandler _keyCodes;
};

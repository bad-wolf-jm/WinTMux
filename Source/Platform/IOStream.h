#pragma once
#include <cstdint>

using handle_t = void *;

class stdin_t
{
  public:
    stdin_t();
    ~stdin_t();

  private:
    handle_t _stream;
    uint32_t _consoleMode;
};

class stdout_t
{
  public:
    stdout_t();
    ~stdout_t();
  public:
    void ProcessEvents();
  private:
    handle_t _stream;

    uint32_t _consoleMode;
    uint32_t _codePage;

    uint32_t _columns = 0;
    uint32_t _rows    = 0;
};

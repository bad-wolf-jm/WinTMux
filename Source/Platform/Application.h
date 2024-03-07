#pragma once
#include "Platform/IOStream.h"
#include "UI/UI.h"
#include <memory>

class Application
{
  public:
    Application();

  public:
    static void Initialize();
    static void Shutdown();

    static std::unique_ptr<Application> &Instance();

  public:
    bool Tick();

  private:
    static std::unique_ptr<Application> _uniqueInstance;

    stdin_t  _stdin;
    stdout_t _stdout;

    UI _ui;
};

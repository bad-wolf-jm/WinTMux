#pragma once
#include <memory>

class Application
{
  public:
    static void Initialize();
    static void Shutdown();
    static std::unique_ptr<Application> &Instance();

  public:
    bool Tick();

  private:
    static std::unique_ptr<Application> _uniqueInstance;
};


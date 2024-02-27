#pragma once
#include "Core/String.h"
#include "Workspace/Tree.h"

class Workspace
{
  public:
    Workspace( string_t name );

    string_t const &Name()
    {
        return _name;
    }

    std::vector<std::shared_ptr<Terminal>> &Terminals();

    void Render();

    void VSplit();
    void HSplit();

  private:
    string_t _name = "";

    std::shared_ptr<Tree>                  _terminalTree;
    std::vector<std::shared_ptr<Terminal>> _terminals;
};

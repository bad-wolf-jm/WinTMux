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

    void Render();

  private:
    string_t              _name = "";
    std::shared_ptr<Tree> _workspaceElements;
};

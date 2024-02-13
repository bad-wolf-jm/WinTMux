#pragma once
#include "Core/String.h"

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
    string_t _name = "";
};

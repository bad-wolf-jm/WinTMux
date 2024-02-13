#include "Workspace.h"
#include <memory>

Workspace::Workspace( string_t name )
    : _name{ name }
    , _workspaceElements{ std::make_shared<Tree>() }
{
}

void Workspace::Render()
{
    _workspaceElements->Render();
}

#include "Workspace.h"
#include <memory>

Workspace::Workspace( string_t name )
    : _name{ name }
    , _workspaceElements{ std::make_shared<Tree>() }
{
}

void Workspace::VSplit()
{
    _workspaceElements->VSplit();
}

void Workspace::HSplit()
{
    _workspaceElements->HSplit();
}

void Workspace::Render()
{
    _workspaceElements->SetSize( ImGui::GetContentRegionAvail() );
    _workspaceElements->Render();
}

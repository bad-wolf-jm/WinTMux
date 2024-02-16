#include "Workspace.h"
#include <memory>

Workspace::Workspace( string_t name )
    : _name{ name }
    , _workspaceElements{ std::make_shared<Tree>() }
{
    _workspaceElements->VSplit();
    _workspaceElements->VSplit();
    _workspaceElements->VSplit();
    _workspaceElements->HSplit();
    _workspaceElements->HSplit();
}

void Workspace::Render()
{
    _workspaceElements->SetSize(ImGui::GetContentRegionAvail());
    _workspaceElements->Render();
}

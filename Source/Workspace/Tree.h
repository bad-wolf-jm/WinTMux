#pragma once
#include <memory>
#include <vector>

#include "Terminal.h"
#include "imgui.h"

enum class eOrientation
{
    HORIZONTAL,
    VERTICAL
};

class Tree
{
  public:
    Tree();

    Tree( const Tree & )            = default;
    Tree( Tree && )                 = default;
    Tree &operator=( const Tree & ) = default;
    Tree &operator=( Tree && )      = default;

  public:
    void   Render();
    void   VSplit();
    void   HSplit();
    void   SetSize( ImVec2 newSize );
    ImVec2 Size();

  private:
    std::shared_ptr<Terminal>          _terminal = nullptr;
    std::vector<std::shared_ptr<Tree>> _children;
    std::vector<float>                 _dimensions;

  private:
    void Layout();

  private:
    float  _dimension = 0.0f;
    ImVec2 _size{};
    ImVec2 _position{};

    eOrientation _orientation = eOrientation::VERTICAL;
};

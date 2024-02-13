#pragma once
#include <memory>
#include <vector>

#include "Terminal.h"

class Tree
{
  public:
    Tree() = default;

    Tree( const Tree & )            = default;
    Tree( Tree && )                 = default;
    Tree &operator=( const Tree & ) = default;
    Tree &operator=( Tree && )      = default;

  public:
    void Render();

  private:
    std::shared_ptr<Terminal>          _terminal = nullptr;
    std::vector<std::shared_ptr<Tree>> _children;

  private:
    float _dimension = 0.0f;
};

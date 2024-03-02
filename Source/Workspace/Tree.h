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
    Tree( std::shared_ptr<Terminal> terminal );
    Tree( Tree *other );

    Tree( const Tree & )            = default;
    Tree( Tree && )                 = default;
    Tree &operator=( const Tree & ) = default;
    Tree &operator=( Tree && )      = default;

  public:
    void   VSplit( std::shared_ptr<Terminal> newTerminal );
    void   HSplit( std::shared_ptr<Terminal> newTerminal );
    void   SetSize( ImVec2 newSize );
    void   SetPosition( ImVec2 newPosition );
    ImVec2 Size();
    
  private:
    std::shared_ptr<Terminal>          _terminal = nullptr;
    std::vector<std::shared_ptr<Tree>> _children;
    std::vector<float>                 _dimensions;

  private:
    void                  UpdateLayout();
    std::shared_ptr<Tree> Clone();

  private:
    float  _dimension = 0.0f;
    ImVec2 _size{};
    ImVec2 _position{};

    eOrientation _orientation = eOrientation::VERTICAL;

    ImFont *_normalFont     = nullptr;
    ImFont *_boldFont       = nullptr;
    ImFont *_italicFont     = nullptr;
    ImFont *_boldItalicFont = nullptr;
};

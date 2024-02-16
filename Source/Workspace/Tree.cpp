#include "Tree.h"
#include <iostream>
#include <memory>
#include <ostream>

Tree::Tree()
{
    _terminal = std::make_shared<Terminal>();
}

Tree::Tree( std::shared_ptr<Terminal> terminal )
{
    _terminal = terminal;
}

Tree::Tree( Tree *other )
{
    _terminal    = other->_terminal;
    _orientation = other->_orientation;

    _children.resize( other->_children.size() );
    std::copy( other->_children.begin(), other->_children.end(), _children.begin() );

    _size     = other->_size;
    _position = other->_position;
}

ImVec2 Tree::Size()
{
    return _size;
}

std::shared_ptr<Tree> Tree::Clone()
{
    return std::make_shared<Tree>( this );
}

void Tree::VSplit()
{
    if( _children.size() == 0 )
    {
        _orientation = eOrientation::VERTICAL;
        _children.push_back( std::make_shared<Tree>( _terminal ) );
        _children.push_back( std::make_shared<Tree>() );
        _terminal = nullptr;

        UpdateLayout();
        return;
    }

    if( _orientation == eOrientation::VERTICAL )
    {
        _children.push_back( std::make_shared<Tree>() );
        _terminal = nullptr;

        UpdateLayout();
        return;
    }

    if( _orientation == eOrientation::HORIZONTAL )
    {
        auto tree    = Clone();
        _orientation = eOrientation::VERTICAL;
        _children.clear();
        _children.push_back( tree );
        _children.push_back( std::make_shared<Tree>() );

        UpdateLayout();
        return;
    }
}

void Tree::HSplit()
{
    if( _children.size() == 0 )
    {
        _orientation = eOrientation::HORIZONTAL;
        _children.push_back( std::make_shared<Tree>( _terminal ) );
        _children.push_back( std::make_shared<Tree>() );
        _terminal = nullptr;

        UpdateLayout();
        return;
    }

    if( _orientation == eOrientation::HORIZONTAL )
    {
        _children.push_back( std::make_shared<Tree>() );
        _terminal = nullptr;

        UpdateLayout();
        return;
    }

    if( _orientation == eOrientation::VERTICAL )
    {
        auto tree    = Clone();
        _orientation = eOrientation::HORIZONTAL;
        _children.clear();
        _children.push_back( tree );
        _children.push_back( std::make_shared<Tree>() );

        UpdateLayout();
        return;
    }
}

void Tree::UpdateLayout()
{
    float _totalChildDimension = 0.0f;
    for( auto const &x : _children )
        _totalChildDimension += ( ( _orientation == eOrientation::VERTICAL ) ? x->_size.x : x->_size.y );

    float  difference        = ( ( _orientation == eOrientation::VERTICAL ) ? _size.x : _size.y ) - _totalChildDimension;
    float  averageDifference = difference / _children.size();
    ImVec2 position          = _position;
    for( auto const &x : _children )
    {
        auto size = x->Size();
        switch( _orientation )
        {
        case eOrientation::VERTICAL:

            x->SetSize( ImVec2{ size.x + averageDifference, _size.y } );
            x->SetPosition( position );
            x->UpdateLayout();
            //std::cout << "x=" << _position.x << " - "
            //          << "y=" << _position.y << std::endl;
            //std::cout << "w=" << _size.x << " - "
            //          << "h=" << _size.y << std::endl;
            position.x += x->Size().x;
            break;
        case eOrientation::HORIZONTAL:
            x->SetSize( ImVec2{ _size.x, size.y + averageDifference } );
            x->SetPosition( position );
            x->UpdateLayout();
            position.y += x->Size().y;
            break;
        }
    }
}

void Tree::SetPosition( ImVec2 newPosition )
{
    _position = newPosition;

    UpdateLayout();
}

void Tree::SetSize( ImVec2 newSize )
{
    _size = newSize;

    UpdateLayout();
}

void Tree::Render()
{
    if( _children.size() == 0 && _terminal != nullptr )
    {
        ImGui::SetCursorPos( _position );
        ImGui::PushID( (void *)_terminal.get() );
        ImGui::BeginChild( "##ChildItem", _size );
        {
            _terminal->Render();
        }
        ImGui::EndChild();
        ImGui::PopID();
    }
    else
    {
        for( auto const &_child : _children )
            _child->Render();
    }
}

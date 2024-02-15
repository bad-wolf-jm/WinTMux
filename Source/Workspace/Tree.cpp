#include "Tree.h"
#include <memory>

Tree::Tree()
{
    _terminal = std::make_shared<Terminal>();
}

void Tree::SetSize( ImVec2 newSize )
{
    _size = newSize;

    float _totalChildDimension = 0.0f;
    for( auto const &x : _children )
        _totalChildDimension += ( ( _orientation == eOrientation::VERTICAL ) ? x->_size.x : x->_size.y );

    float _difference        = ( ( _orientation == eOrientation::VERTICAL ) ? _size.x : _size.y ) - _totalChildDimension;
    float _averageDifference = _difference / _children.size();

    for( auto const &x : _children )
    {
        auto size = x->Size();
        switch( _orientation )
        {
        case eOrientation::VERTICAL:
            x->SetSize( ImVec2{ size.x - _averageDifference, size.y } );
            break;
        case eOrientation::HORIZONTAL:
            x->SetSize( ImVec2{ size.x, size.y - _averageDifference } );
            break;
        }
    }
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

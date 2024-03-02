#include "Workspace.h"
#include <iostream>
#include <memory>
#include <ostream>

Workspace::Workspace( string_t name )
    : _name{ name }
{
    _terminals.push_back( std::make_shared<Terminal>() );
    //_terminals.back()->IsFocused = true;

    _terminalTree = std::make_shared<Tree>( _terminals.back() );
}

void Workspace::SetFonts( ImFont *normalFont, ImFont *boldFont, ImFont *italicFont, ImFont *boldItalicFont )
{
    _normalFont     = normalFont;
    _boldFont       = boldFont;
    _italicFont     = italicFont;
    _boldItalicFont = boldItalicFont;

    for(auto const& terminal : _terminals)
        terminal->SetFonts( _normalFont, _boldFont, _italicFont, _boldItalicFont );
}

void Workspace::VSplit()
{
    _terminals.push_back( std::make_shared<Terminal>() );
    _terminalTree->VSplit( _terminals.back() );
}

void Workspace::HSplit()
{
    _terminals.push_back( std::make_shared<Terminal>() );
    _terminalTree->HSplit( _terminals.back() );
}

std::vector<std::shared_ptr<Terminal>> &Workspace::Terminals()
{
    return _terminals;
}

void Workspace::FocusTerminal( int32_t index )
{
    if( index < 0 )
        index = 0;

    if( index >= _terminals.size() )
        index = _terminals.size() - 1;

    _focusedTerminal = index;
}

void Workspace::Render()
{
    _terminalTree->SetSize( ImGui::GetContentRegionAvail() );

    int32_t terminalIndex = 0;
    for( auto const &terminal : _terminals )
    {
        ImGui::SetCursorPos( terminal->Position );
        ImGui::PushID( (void *)terminal.get() );
        ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2{ 5.0, 5.0 } );
        ImGui::BeginChild( "##ChildItem", terminal->Size, ImGuiChildFlags_None, ImGuiWindowFlags_None );
        {
            auto  *drawList       = ImGui::GetWindowDrawList();
            ImVec2 screenPosition = ImGui::GetCursorScreenPos();
            ImVec2 screenSize     = ImGui::GetWindowSize();

            ImVec2 topLeft{ screenPosition.x, screenPosition.y };
            ImVec2 windowSize{ screenSize.x, screenSize.y };
            ImVec2 bottomRight = ImVec2{ topLeft.x + windowSize.x, topLeft.y + windowSize.y };

            //uint32_t borderColor = terminal->IsFocused ? ImColor( 255, 255, 255, 150 ) : ImColor( 255, 255, 255, 50 );
            //drawList->AddRect( topLeft, bottomRight, borderColor );

            ImVec2 terminalPosition{ terminal->Position.x + 5.0f, terminal->Position.y + 5.0f };
            ImVec2 terminalSize{ terminal->Size.x - 10.0f, terminal->Size.y - 10.0f };
            // ImGui::SetCursorPos( terminalPosition );
            // ImGui::PushID( terminalIndex );
            // ImGui::BeginChild( "##TerminalDisplay", terminalSize );
            //{
            //     std::cout << "FOOBAR " << terminalIndex << " "
            //               << "X =" << terminalPosition.x << " Y=" << terminalPosition.y << std::endl;
            terminal->Render();
            // ImGui::Text( "FOOBAR %d", terminalIndex++ );
            // ImGui::Text( "%f x %f", terminalSize.x, terminalSize.y );
            // }
            //  ImGui::EndChild();
            //  ImGui::PopID();

            ImVec2 overlayTopLeft     = ImVec2{ topLeft.x + 1, topLeft.y + 1 };
            ImVec2 overlayBottomRight = ImVec2{ bottomRight.x - 1, bottomRight.y - 1 };
            if( _focusedTerminal != terminalIndex )
            {
                drawList->AddRectFilled( overlayTopLeft, overlayBottomRight, IM_COL32( 0, 0, 0, 200 ) );
            }
            else
            {
                uint32_t borderColor = ImColor( 255, 55, 255, 200 );

                drawList->AddRect( overlayTopLeft, overlayBottomRight, borderColor );
            }
            terminalIndex++;
        }
        ImGui::EndChild();
        ImGui::PopID();
        ImGui::PopStyleVar();
    }
}

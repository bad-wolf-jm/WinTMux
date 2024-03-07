#pragma once
#include "Core/String.h"
#include "Workspace/Tree.h"

class Workspace
{
  public:
    Workspace( string_t name );

    string_t const &Name()
    {
        return _name;
    }

    // std::vector<std::shared_ptr<Terminal>> &Terminals();
    // void                                    FocusTerminal( int32_t index );

    void Render();

    // void VSplit();
    // void HSplit();

    // void SetFonts( ImFont *normalFont, ImFont *boldFont, ImFont *italicFont, ImFont *boldItalicFont );

  private:
    string_t _name = "";

    // std::shared_ptr<Tree>                  _terminalTree;
    std::shared_ptr<Terminal> _bgTerminal = nullptr;
    std::shared_ptr<Terminal> _fgTerminal = nullptr;

    // int32_t _focusedTerminal = 0;

    // ImFont *_normalFont     = nullptr;
    // ImFont *_boldFont       = nullptr;
    // ImFont *_italicFont     = nullptr;
    // ImFont *_boldItalicFont = nullptr;
};

#include "Terminal.h"
#include "Core/Glyph.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <cstdint>
#include <vector>

string_t &Terminal::Name()
{
    return _name;
    //    _process = std::make_shared<PTYProcess>( "powershell", 100, 100 );
}

inline void DrawGlyph( ImVec2 position, uint32_t color, ImFontGlyph const *glyph, ImDrawVert *&vtx, ImDrawIdx *&idx, uint32_t &idxStart )
{
    float u1 = glyph->U0;
    float v1 = glyph->V0;
    float u2 = glyph->U1;
    float v2 = glyph->V1;

    float x1 = position.x + glyph->X0;
    float x2 = position.x + glyph->X1;
    float y1 = position.y + glyph->Y0;
    float y2 = position.y + glyph->Y1;

    idx[0] = (ImDrawIdx)( idxStart );
    idx[1] = (ImDrawIdx)( idxStart + 1 );
    idx[2] = (ImDrawIdx)( idxStart + 2 );
    idx[3] = (ImDrawIdx)( idxStart );
    idx[4] = (ImDrawIdx)( idxStart + 2 );
    idx[5] = (ImDrawIdx)( idxStart + 3 );
    idx += 6;
    idxStart += 4;

    vtx[0].col   = color;
    vtx[0].pos.x = x1;
    vtx[0].pos.y = y1;
    vtx[0].uv.x  = u1;
    vtx[0].uv.y  = v1;

    vtx[1].col   = color;
    vtx[1].pos.x = x2;
    vtx[1].pos.y = y1;
    vtx[1].uv.x  = u2;
    vtx[1].uv.y  = v1;

    vtx[2].col   = color;
    vtx[2].pos.x = x2;
    vtx[2].pos.y = y2;
    vtx[2].uv.x  = u2;
    vtx[2].uv.y  = v2;

    vtx[3].col   = color;
    vtx[3].pos.x = x1;
    vtx[3].pos.y = y2;
    vtx[3].uv.x  = u1;
    vtx[3].uv.y  = v2;

    vtx += 4;
}

void Terminal::SetFonts( ImFont *normalFont, ImFont *boldFont, ImFont *italicFont, ImFont *boldItalicFont )
{
    _normalFont     = normalFont;
    _boldFont       = boldFont;
    _italicFont     = italicFont;
    _boldItalicFont = boldItalicFont;
}

void Terminal::Render()
{
    //    auto  *drawList    = ImGui::GetWindowDrawList();
    //    ImVec2 topLeft     = ImGui::GetCursorScreenPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    //    ImVec2 bottomRight = ImVec2{ topLeft.x + windowSize.x, topLeft.y + windowSize.y };
    //
    //    uint32_t borderColor = IsFocused ? ImColor( 255, 255, 255, 150 ) : ImColor( 255, 255, 255, 50 );
    //    drawList->AddRect( topLeft, bottomRight, borderColor );
    //
    //ImGui::SetCursorPos( ImVec2{ 5.0f, 5.0f } );
    //ImGui::Text( "FOOBAR" );
    //ImGui::Text( "%f x %f", windowSize.x, windowSize.y );
    //    if( !IsFocused )
    //    {
    //        ImVec2 overlayTopLeft     = ImVec2{ topLeft.x + 1, topLeft.y + 1 };
    //        ImVec2 overlayBottomRight = ImVec2{ bottomRight.x - 1, bottomRight.y - 1 };
    //
    //        drawList->AddRectFilled( overlayTopLeft, overlayBottomRight, IM_COL32( 0, 0, 0, 200 ) );
    //    }
    //    else
    //    {
    //        ImVec2   overlayTopLeft     = ImVec2{ topLeft.x + 1, topLeft.y + 1 };
    //        ImVec2   overlayBottomRight = ImVec2{ bottomRight.x - 1, bottomRight.y - 1 };
    //        uint32_t borderColor        = ImColor( 255, 55, 255, 200 );
    //
    //        drawList->AddRect( overlayTopLeft, overlayBottomRight, borderColor );
    //    }
    auto  *drawList   = ImGui::GetWindowDrawList();
    ImVec2 topLeft    = ImGui::GetCursorScreenPos();
    ImVec2 windowSize = ImGui::GetWindowSize();

    // Update the number of rows and columns of the terminal.
    ImVec2 characterSize = ImGui::CalcTextSize( "M" );

    int32_t rows    = windowSize.y / characterSize.y;
    int32_t columns = windowSize.x / characterSize.x;
    if( rows != _rows || columns != _columns )
    {
        // Resize terminal process and update internal variables
        _rows    = rows;
        _columns = columns;
    }

    ImVec2 bottomRight = ImVec2{ topLeft.x + windowSize.x, topLeft.y + windowSize.y };

    uint32_t borderColor = IsFocused ? ImColor( 255, 255, 255, 200 ) : ImColor( 255, 255, 255, 50 );
    drawList->AddRect( topLeft, bottomRight, borderColor );

    ImGui::SetCursorPos( ImVec2{ 5.0f, 5.0f } );
    ImGui::Text( "FOOBAR" );
    ImGui::Text( "%f x %f", windowSize.x, windowSize.y );
    ImGui::Text( "%d x %d", _rows, _columns );
    ImGui::Text( "%f x %f", _columns * characterSize.x, _rows * characterSize.y );

    // auto &io = ImGui::GetIO();
    // static bool use_text_color_for_tint = false;
    // ImTextureID my_tex_id               = io.Fonts->TexID;
    // float       my_tex_w                = (float)io.Fonts->TexWidth;
    // float       my_tex_h                = (float)io.Fonts->TexHeight;
    // ImGui::Checkbox( "Use Text Color for Tint", &use_text_color_for_tint );
    // ImGui::Text( "%.0fx%.0f", my_tex_w, my_tex_h );
    // ImVec2 pos    = ImGui::GetCursorScreenPos();
    // ImVec2 uv_min = ImVec2( 0.0f, 0.0f ); // Top-left
    // ImVec2 uv_max = ImVec2( 1.0f, 1.0f ); // Lower-right
    // ImVec4 tint_col =
    //     use_text_color_for_tint ? ImGui::GetStyleColorVec4( ImGuiCol_Text ) : ImVec4( 1.0f, 1.0f, 1.0f, 1.0f ); // No tint
    // ImVec4 border_col = ImGui::GetStyleColorVec4( ImGuiCol_Border );
    // ImGui::Image( my_tex_id, ImVec2( my_tex_w, my_tex_h ), uv_min, uv_max, tint_col, border_col );

    // if( !IsFocused )
    // {
    //     ImVec2 overlayTopLeft     = ImVec2{ topLeft.x + 1, topLeft.y + 1 };
    //     ImVec2 overlayBottomRight = ImVec2{ bottomRight.x - 1, bottomRight.y - 1 };

    //     drawList->AddRectFilled( overlayTopLeft, overlayBottomRight, IM_COL32( 0, 0, 0, 200 ) );
    // }
    // else
    // {
    //     ImVec2   overlayTopLeft     = ImVec2{ topLeft.x + 1, topLeft.y + 1 };
    //     ImVec2   overlayBottomRight = ImVec2{ bottomRight.x - 1, bottomRight.y - 1 };
    //     uint32_t borderColor        = ImColor( 255, 55, 255, 200 );

    //     drawList->AddRect( overlayTopLeft, overlayBottomRight, borderColor );
    // }

    const char        *test_string = "abcdef";
    std::vector<Glyph> test_glyphs;
    for( int x = 0; x < 6; x++ )
    {
        Glyph g{};
        g.Character  = test_string[x];
        g.Foreground = IM_COL32( 0, 25, 12, 255 );
        g.Background = IM_COL32( 255, 25, 255, 255 );
        test_glyphs.push_back( g );
    }

    float advanceX   = 20.0f;
    float lineHeight = 20.0f;
    // 4 vertices per primitive, up to 11 primitives pr char (background, glyph (up to 8 because of boxdraw), strikethrough, underline)
    // and the cursor
    const int vtx_count_max = (int)( _columns * _rows ) * 4 * 11 + 16;
    // 6 indices per primitive, up to 4 primitives pr char (background, glyph, strikethrough, underline) and the cursor
    const int idx_count_max     = (int)( _columns * _rows ) * 6 * 11 + 24;
    const int idx_expected_size = drawList->IdxBuffer.Size + idx_count_max;
    drawList->PrimReserve( idx_count_max, vtx_count_max );

    ImDrawVert  *vtx_write       = drawList->_VtxWritePtr;
    ImDrawIdx   *idx_write       = drawList->_IdxWritePtr;
    unsigned int vtx_current_idx = drawList->_VtxCurrentIdx;

    auto  pos = ImGui::GetCursorScreenPos();
    float x   = pos.x + 0.0f;
    float y   = pos.y + 0.0f;
    for( auto const &gl : test_glyphs )
    {
        auto const *fontGlyph = _boldItalicFont->FindGlyphNoFallback( gl.Character );

        ImVec2 a( x, y ), c( x + advanceX, y + lineHeight );
        ImVec2 b( c.x, a.y ), d( a.x, c.y ), uv( drawList->_Data->TexUvWhitePixel );
        idx_write[0] = vtx_current_idx;
        idx_write[1] = (ImDrawIdx)( vtx_current_idx + 1 );
        idx_write[2] = (ImDrawIdx)( vtx_current_idx + 2 );
        idx_write[3] = vtx_current_idx;
        idx_write[4] = (ImDrawIdx)( vtx_current_idx + 2 );
        idx_write[5] = (ImDrawIdx)( vtx_current_idx + 3 );
        idx_write += 6;

        vtx_write[0].pos = a;
        vtx_write[0].uv  = uv;
        vtx_write[0].col = gl.Background;
        vtx_write[1].pos = b;
        vtx_write[1].uv  = uv;
        vtx_write[1].col = gl.Background;
        vtx_write[2].pos = c;
        vtx_write[2].uv  = uv;
        vtx_write[2].col = gl.Background;
        vtx_write[3].pos = d;
        vtx_write[3].uv  = uv;
        vtx_write[3].col = gl.Background;
        vtx_write += 4;
        vtx_current_idx += 4;

        DrawGlyph( ImVec2{ x, y }, gl.Foreground, fontGlyph, vtx_write, idx_write, vtx_current_idx );
        x += advanceX;
    }

    drawList->VtxBuffer.Size = (int)( vtx_write - drawList->VtxBuffer.Data ); // Same as calling shrink()
    drawList->IdxBuffer.Size = (int)( idx_write - drawList->IdxBuffer.Data );
    drawList->CmdBuffer[drawList->CmdBuffer.Size - 1].ElemCount -= ( idx_expected_size - drawList->IdxBuffer.Size );

    drawList->_VtxWritePtr   = vtx_write;
    drawList->_IdxWritePtr   = idx_write;
    drawList->_VtxCurrentIdx = vtx_current_idx;
    // for( int row = 0; row < _rows; row++ )
    //  {
    //      for( int column = 0; column < _columns; column++ )
    //      {
    //      }
    //  }
}

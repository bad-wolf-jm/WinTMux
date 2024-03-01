#include "Terminal.h"
#include "imgui.h"
#include <cstdint>

string_t &Terminal::Name()
{
    return _name;
    //    _process = std::make_shared<PTYProcess>( "powershell", 100, 100 );
}


inline void DrawGlyph( ImVec2 position, uint32_t color, ImFontGlyph *glyph, ImDrawVert *&vtx, ImDrawIdx *&idx, uint32_t &idxStart )
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

    for( int row = 0; row < _rows; row++ )
    {
        for( int column = 0; column < _columns; column++ )
        {
        }
    }
}

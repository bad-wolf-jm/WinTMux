#include "UI.h"

#include <fmt/printf.h>
#include <memory>

UI::UI()
{
}

void UI::Start()
{
    // _bgTerminal = std::make_shared<process_t>( "py \"C:\\GitLab\\WinTMux\\Scripts\\test_terminal.py\"", _bgTerminalBuffer );
    _bgTerminal = std::make_shared<process_t>( "py -m rich", _bgTerminalBuffer );
    // _bgTerminal = std::make_shared<process_t>( "nvim", _bgTerminalBuffer );
    _fgTerminal = std::make_shared<process_t>( "powershell", _fgTerminalBuffer );
    _bgTerminalBuffer.BeginFrame();
    _fgTerminalBuffer.BeginFrame();
}

void UI::Stop()
{
    _bgTerminal->WaitForCompletion( 1 );
}

void UI::Resize( uint32_t columns, uint32_t rows )
{
    std::cout << "TTT Rows=" << rows << ", Columns=" << columns << std::endl;
    if( _bgTerminal != nullptr )
        _bgTerminal->Resize( rows, columns );

    _framebuffer.Resize( rows, columns );
    _bgTerminalBuffer.Resize( rows, columns );

    _fgTerminalWidth  = static_cast<int32_t>( _framebuffer.Columns() * 0.75f );
    _fgTerminalHeight = static_cast<int32_t>( _framebuffer.Rows() * 0.95f );

    int32_t remainingWidth = _framebuffer.Columns() - _fgTerminalWidth;
    if( ( remainingWidth % 2 ) != 0 )
        _fgTerminalWidth++;

    int32_t remainingHeight = _framebuffer.Rows() - _fgTerminalHeight;
    if( ( remainingHeight % 2 ) != 0 )
        _fgTerminalHeight++;

    // Reduce the size of the terminal framebuffer to allow space for the frame
    if( _fgTerminal != nullptr )
        _fgTerminal->Resize( _fgTerminalHeight - 2, _fgTerminalWidth - 2 );

    _fgTerminalBuffer.Resize( _fgTerminalHeight - 2, _fgTerminalWidth - 2 );
}

framebuffer_t &UI::FrameBuffer()
{
    return _framebuffer;
}

void UI::OnKeyPress( keycode_t const &keyCode, uint32_t modifiers )
{
    if( _displayTerminal && keyCode.KeyCode == keycode::ESCAPE )
    {
        _displayTerminal = false;
        return;
    }

    if( !_displayTerminal && ( keyCode.KeyCode == keycode::GRAVE_ACCENT ) && ( modifiers & ( 1 << (uint32_t)modifiers::CTRL ) ) )
    {
        _displayTerminal = true;
        return;
    }

    if( _displayTerminal )
    {
        // If the foreground terminal is visible, then it receives
        // the keypress event, and further processing is disabled
        _fgTerminal->OnKeyPress( keyCode, modifiers );
        return;
    }

    // Send the keypress event to the main program.
    // _bgTerminal->OnKeyPress( keyCode, modifiers );
}

void UI::Render()
{
    _bgTerminal->PipeListener();
    _fgTerminal->PipeListener();

    _framebuffer.BeginFrame();

    // Blit the main terminal framebuffer to the output buffer.
    std::copy( _bgTerminalBuffer.DataNC().begin(), _bgTerminalBuffer.DataNC().end(), _framebuffer.DataNC().begin() );

    if( _displayTerminal )
    {
        // Dim the main terminal buffer before displaying the work terminal
        // over it
        for( auto &glyph : _framebuffer.DataNC() )
        {
            uint32_t fg = static_cast<uint32_t>( ( glyph.Attributes >> 24 ) & 0xFFFFFF );
            {
                uint8_t r = ( ( fg & 0xff0000 ) >> 16 ) >> 1;
                uint8_t g = ( ( fg & 0xff00 ) >> 8 ) >> 1;
                uint8_t b = ( fg & 0xff ) >> 1;

                fg = r << 16 | g << 8 | b;
            }

            uint32_t bg = static_cast<uint32_t>( glyph.Attributes & 0xFFFFFF );
            {
                uint8_t r = ( ( bg & 0xff0000 ) >> 16 ) >> 1;
                uint8_t g = ( ( bg & 0xff00 ) >> 8 ) >> 1;
                uint8_t b = ( bg & 0xff ) >> 1;

                bg = r << 16 | g << 8 | b;
            }

            uint32_t attributes = glyph.Attributes >> 48;

            glyph.Attributes =
                static_cast<uint64_t>( attributes ) << 48 | static_cast<uint64_t>( fg ) << 24 | static_cast<uint64_t>( bg );
        }

        int32_t remainingWidth  = _framebuffer.Columns() - _fgTerminalWidth;
        int32_t remainingHeight = _framebuffer.Rows() - _fgTerminalHeight;

        int32_t fgTerminalPositionX = remainingWidth / 2;
        int32_t fgTerminalPositionY = remainingHeight / 2;

        _framebuffer.SetForeground( 200, 200, 200 );
        _framebuffer.SetBackground( 20, 20, 20 );
        _framebuffer.DrawRect( fgTerminalPositionX, fgTerminalPositionY, _fgTerminalWidth, _fgTerminalHeight, u8"\u256D", u8"\u2500",
                               u8"\u256E", u8"\u2502", u8"\u256F", u8"\u2500", u8"\u2570", u8"\u2502" );

        // Paint the foreground terminal framebuffer inside the rectangle
        for( int r = 0; r < _fgTerminalBuffer.Rows(); r++ )
        {
            for( int c = 0; c < _fgTerminalBuffer.Columns(); c++ )
            {
                int position         = r * _fgTerminalBuffer.Columns() + c;
                int positionOnScreen = ( r + fgTerminalPositionY + 1 ) * _framebuffer.Columns() + ( c + fgTerminalPositionX + 1 );

                _framebuffer.DataNC()[positionOnScreen] = _fgTerminalBuffer.DataNC()[position];
            }
        }
    }

    _framebuffer.EndFrame();
}

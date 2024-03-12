#include "Parser.h"
#include "States.h"

#include <cstdint>
#include <iomanip>
#include <iostream>

Vt100Parser::Vt100Parser()
{
    state                  = VtParserState::ground;
    num_intermediate_chars = 0;
    num_params             = 0;
    ignore_flagged         = 0;
    // cb                     = cb;

    // Anywhere transitions
    OnEvent( 0x18, Action::execute, VtParserState::ground );
    OnEvent( 0x1a, Action::execute, VtParserState::ground );
    OnEvent( Range{ 0x80, 0x8f }, Action::execute, VtParserState::ground );
    OnEvent( Range{ 0x91, 0x97 }, Action::execute, VtParserState::ground );
    OnEvent( 0x99, Action::execute, VtParserState::ground );
    OnEvent( 0x9a, Action::execute, VtParserState::ground );
    OnEvent( 0x9c, VtParserState::ground );
    OnEvent( 0x1b, VtParserState::escape );
    OnEvent( 0x98, VtParserState::sos_pm_apc_string );
    OnEvent( 0x9e, VtParserState::sos_pm_apc_string );
    OnEvent( 0x9f, VtParserState::sos_pm_apc_string );
    OnEvent( 0x90, VtParserState::dcs_entry );
    OnEvent( 0x9d, VtParserState::osc_string );
    OnEvent( 0x9b, VtParserState::csi_entry );

    // Transitions from ground state
    OnEvent( VtParserState::ground, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::ground, 0x19, Action::execute );
    OnEvent( VtParserState::ground, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::ground, Range{ 0x20, 0x7f }, Action::print );

    //$states[:ESCAPE] = {
    OnEntry( VtParserState::escape, Action::clear );
    OnEvent( VtParserState::escape, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::escape, 0x19, Action::execute );
    OnEvent( VtParserState::escape, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::escape, 0x7f, Action::ignore );
    OnEvent( VtParserState::escape, Range{ 0x20, 0x2f }, Action::collect, VtParserState::escape_intermediate );
    OnEvent( VtParserState::escape, Range{ 0x30, 0x4f }, Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, Range{ 0x51, 0x57 }, Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, 0x59, Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, 0x5a, Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, 0x5c, Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, Range{ 0x60, 0x7e }, Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, 0x5b, VtParserState::csi_entry );
    OnEvent( VtParserState::escape, 0x5d, VtParserState::osc_string );
    OnEvent( VtParserState::escape, 0x50, VtParserState::dcs_entry );
    OnEvent( VtParserState::escape, 0x58, VtParserState::sos_pm_apc_string );
    OnEvent( VtParserState::escape, 0x5e, VtParserState::sos_pm_apc_string );
    OnEvent( VtParserState::escape, 0x5f, VtParserState::sos_pm_apc_string );

    //$states[:ESCAPE_INTERMEDIATE] = {
    OnEvent( VtParserState::escape_intermediate, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::escape_intermediate, 0x19, Action::execute );
    OnEvent( VtParserState::escape_intermediate, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::escape_intermediate, Range{ 0x20, 0x2f }, Action::collect );
    OnEvent( VtParserState::escape_intermediate, 0x7f, Action::ignore );
    OnEvent( VtParserState::escape_intermediate, Range{ 0x30, 0x7e }, Action::esc_dispatch, VtParserState::ground );

    //$states[:CSI_ENTRY] = {
    OnEntry( VtParserState::csi_entry, Action::clear );
    OnEvent( VtParserState::csi_entry, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::csi_entry, 0x19, Action::execute );
    OnEvent( VtParserState::csi_entry, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::csi_entry, 0x7f, Action::ignore );
    OnEvent( VtParserState::csi_entry, Range{ 0x20, 0x2f }, Action::collect, VtParserState::csi_intermediate );
    OnEvent( VtParserState::csi_entry, 0x3a, VtParserState::csi_ignore );
    OnEvent( VtParserState::csi_entry, Range{ 0x30, 0x39 }, Action::param, VtParserState::csi_param );
    OnEvent( VtParserState::csi_entry, 0x3b, Action::param, VtParserState::csi_param );
    OnEvent( VtParserState::csi_entry, Range{ 0x3c, 0x3f }, Action::collect, VtParserState::csi_param );
    OnEvent( VtParserState::csi_entry, Range{ 0x40, 0x7e }, Action::csi_dispatch, VtParserState::ground );

    //$states[:CSI_IGNORE] = {
    OnEvent( VtParserState::csi_ignore, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::csi_ignore, 0x19, Action::execute );
    OnEvent( VtParserState::csi_ignore, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::csi_ignore, Range{ 0x20, 0x3f }, Action::ignore );
    OnEvent( VtParserState::csi_ignore, 0x7f, Action::ignore );
    OnEvent( VtParserState::csi_ignore, Range{ 0x40, 0x7e }, VtParserState::ground );

    //$states[:CSI_PARAM] = {
    OnEvent( VtParserState::csi_param, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::csi_param, 0x19, Action::execute );
    OnEvent( VtParserState::csi_param, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::csi_param, Range{ 0x30, 0x39 }, Action::param );
    OnEvent( VtParserState::csi_param, 0x3b, Action::param );
    OnEvent( VtParserState::csi_param, 0x7f, Action::ignore );
    OnEvent( VtParserState::csi_param, 0x3a, VtParserState::csi_ignore );
    OnEvent( VtParserState::csi_param, Range{ 0x3c, 0x3f }, VtParserState::csi_ignore );
    OnEvent( VtParserState::csi_param, Range{ 0x20, 0x2f }, Action::collect, VtParserState::csi_intermediate );
    OnEvent( VtParserState::csi_param, Range{ 0x40, 0x7e }, Action::csi_dispatch, VtParserState::ground );

    //$states[:CSI_INTERMEDIATE] = {
    OnEvent( VtParserState::csi_intermediate, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::csi_intermediate, 0x19, Action::execute );
    OnEvent( VtParserState::csi_intermediate, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::csi_intermediate, Range{ 0x20, 0x2f }, Action::collect );
    OnEvent( VtParserState::csi_intermediate, 0x7f, Action::ignore );
    OnEvent( VtParserState::csi_intermediate, Range{ 0x30, 0x3f }, VtParserState::csi_ignore );
    OnEvent( VtParserState::csi_intermediate, Range{ 0x40, 0x7e }, Action::csi_dispatch, VtParserState::ground );
    //}

    //$states[:DCS_ENTRY] = {
    OnEntry( VtParserState::dcs_entry, Action::clear );
    OnEvent( VtParserState::dcs_entry, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::dcs_entry, 0x19, Action::ignore );
    OnEvent( VtParserState::dcs_entry, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::dcs_entry, 0x7f, Action::ignore );
    OnEvent( VtParserState::dcs_entry, 0x3a, VtParserState::dcs_ignore );
    OnEvent( VtParserState::dcs_entry, Range{ 0x20, 0x2f }, Action::collect, VtParserState::dcs_intermediate );
    OnEvent( VtParserState::dcs_entry, Range{ 0x30, 0x39 }, Action::param, VtParserState::dcs_param );
    OnEvent( VtParserState::dcs_entry, 0x3b, Action::param, VtParserState::dcs_param );
    OnEvent( VtParserState::dcs_entry, Range{ 0x3c, 0x3f }, Action::collect, VtParserState::dcs_param );
    OnEvent( VtParserState::dcs_entry, Range{ 0x40, 0x7e }, VtParserState::dcs_passthrough );

    //$states[:DCS_INTERMEDIATE] = {
    OnEvent( VtParserState::dcs_intermediate, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::dcs_intermediate, 0x19, Action::ignore );
    OnEvent( VtParserState::dcs_intermediate, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::dcs_intermediate, Range{ 0x20, 0x2f }, Action::collect );
    OnEvent( VtParserState::dcs_intermediate, 0x7f, Action::ignore );
    OnEvent( VtParserState::dcs_intermediate, Range{ 0x30, 0x3f }, VtParserState::dcs_ignore );
    OnEvent( VtParserState::dcs_intermediate, Range{ 0x40, 0x7e }, VtParserState::dcs_passthrough );

    //$states[:DCS_IGNORE] = {
    OnEvent( VtParserState::dcs_ignore, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::dcs_ignore, 0x19, Action::ignore );
    OnEvent( VtParserState::dcs_ignore, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::dcs_ignore, Range{ 0x20, 0x7f }, Action::ignore );

    //$states[:DCS_PARAM] = {
    OnEvent( VtParserState::dcs_param, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::dcs_param, 0x19, Action::ignore );
    OnEvent( VtParserState::dcs_param, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::dcs_param, Range{ 0x30, 0x39 }, Action::param );
    OnEvent( VtParserState::dcs_param, 0x3b, Action::param );
    OnEvent( VtParserState::dcs_param, 0x7f, Action::ignore );
    OnEvent( VtParserState::dcs_param, 0x3a, VtParserState::dcs_ignore );
    OnEvent( VtParserState::dcs_param, Range{ 0x3c, 0x3f }, VtParserState::dcs_ignore );
    OnEvent( VtParserState::dcs_param, Range{ 0x20, 0x2f }, Action::collect, VtParserState::dcs_intermediate );
    OnEvent( VtParserState::dcs_param, Range{ 0x40, 0x7e }, VtParserState::dcs_passthrough );

    //$states[:DCS_PASSTHROUGH] = {
    OnEntry( VtParserState::dcs_passthrough, Action::hook );
    OnExit( VtParserState::dcs_passthrough, Action::unhook );
    OnEvent( VtParserState::dcs_passthrough, Range{ 0x00, 0x17 }, Action::put );
    OnEvent( VtParserState::dcs_passthrough, 0x19, Action::put );
    OnEvent( VtParserState::dcs_passthrough, Range{ 0x1c, 0x1f }, Action::put );
    OnEvent( VtParserState::dcs_passthrough, Range{ 0x20, 0x7e }, Action::put );
    OnEvent( VtParserState::dcs_passthrough, 0x7f, Action::ignore );

    //$states[:SOS_PM_APC_STRING] = {
    OnEvent( VtParserState::sos_pm_apc_string, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::sos_pm_apc_string, 0x19, Action::ignore );
    OnEvent( VtParserState::sos_pm_apc_string, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::sos_pm_apc_string, Range{ 0x20, 0x7f }, Action::ignore );

    //$states[:OSC_STRING] = {
    OnEntry( VtParserState::osc_string, Action::osc_start );
    OnExit( VtParserState::osc_string, Action::osc_end );
    OnEvent( VtParserState::osc_string, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::osc_string, 0x19, Action::ignore );
    OnEvent( VtParserState::osc_string, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::osc_string, Range{ 0x20, 0x7f }, Action::osc_put );
}

void Vt100Parser::OnEntry( VtParserState state, Action action )
{
    _entryActions[(uint8_t)state] = action;
}

void Vt100Parser::OnExit( VtParserState state, Action action )
{
    _exitActions[(uint8_t)state] = action;
}

void Vt100Parser::OnEvent( Range range, Action action )
{
    OnEvent( range, action, VtParserState::none );
}

void Vt100Parser::OnEvent( Range range, VtParserState transitionTo )
{
    OnEvent( range, Action::none, transitionTo );
}

void Vt100Parser::OnEvent( Range range, Action action, VtParserState transitionTo )
{
    for( int i = 0; i < (int)VtParserState::count; i++ )
        OnEvent( (VtParserState)i, range, action, transitionTo );
}

void Vt100Parser::OnEvent( VtParserState state, Range range, Action action )
{
    OnEvent( state, range, action, VtParserState::none );
}

void Vt100Parser::OnEvent( VtParserState state, Range range, VtParserState transitionTo )
{
    OnEvent( state, range, Action::none, transitionTo );
}

void Vt100Parser::OnEvent( VtParserState state, Range range, Action action, VtParserState transitionTo )
{
    for( uint8_t c = range.Start; c <= range.End; c++ )
        OnEvent( state, c, action, transitionTo );
}

void Vt100Parser::OnEvent( uint8_t character, Action action )
{
    OnEvent( character, action, VtParserState::none );
}

void Vt100Parser::OnEvent( uint8_t character, VtParserState transitionTo )
{
    OnEvent( character, Action::none, transitionTo );
}

void Vt100Parser::OnEvent( uint8_t character, Action action, VtParserState transitionTo )
{
    for( int i = 0; i < (int)VtParserState::count; i++ )
        OnEvent( (VtParserState)i, character, action, transitionTo );
}

void Vt100Parser::OnEvent( VtParserState state, uint8_t character, Action action )
{
    OnEvent( state, character, action, VtParserState::none );
}

void Vt100Parser::OnEvent( VtParserState state, uint8_t character, VtParserState transitionTo )
{
    OnEvent( state, character, Action::none, transitionTo );
}

void Vt100Parser::OnEvent( VtParserState state, uint8_t character, Action action, VtParserState transitionTo )
{
    _stateTransitions[(uint8_t)state][character] = state_transition_t{ transitionTo, action };
}

void Vt100Parser::Dispatch( framebuffer_t &framebuffer, Action action, char ch )
{

    switch( action )
    {
    case Action::print:
        // if( ch == ' ' )
        //     std::cout << "SPACE" << std::hex << (uint8_t)action << " "
        //               << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint16_t)ch << std::endl;
        framebuffer.putc( ch );
        break;
    case Action::execute:
        switch( ch )
        {
        case '\x0a':
        {
            uint32_t x, y;
            framebuffer.Cursor( x, y );
            y += 1;
            y = std::min( framebuffer.Rows() - 1, y );
            x = 0;
            framebuffer.SetCursor( x, y );
        }
        break;
        case '\x0d':
        {
            uint32_t x, y;
            framebuffer.Cursor( x, y );
            x = 0;
            framebuffer.SetCursor( x, y );
        }
        break;
        case '\x09':
        {
            uint32_t x, y;
            framebuffer.Cursor( x, y );
            x = ( x / 8 + 1 ) * 8;
            framebuffer.SetCursor( x, y );
        }
        break;
        }
        // #if 0
        // #endif
        break;
    case Action::hook:
        // std::cout << "Action::hook" << std::endl;
        break;
    case Action::put:
        // std::cout << "Action::put" << std::endl;
        break;
    case Action::osc_start:
        // std::cout << "Action::osc_start"
        //   << " " << ch << std::endl;
        //   << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint16_t)ch << std::endl;
        break;
    case Action::osc_put:
        // std::cout << "Action::osc_put"
        //   << " " << ch << std::endl;
        //   << " "
        //   << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint16_t)ch << std::endl;
        break;
    case Action::osc_end:
        // std::cout << "Action::osc_end" //    << " " << ch << std::endl;
        //   << " "
        //   << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint16_t)ch << std::endl;
        break;
    case Action::unhook:
        break;
    case Action::csi_dispatch:
    {
        switch( ch )
        {
        case 'H':
            if( num_params == 0 )
                framebuffer.SetCursor( 0, 0 );
            else
            {
                std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;

                framebuffer.SetCursor( params[1] - 1, params[0] - 1 );
            }
            break;
        case 'f':
            std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            if( num_params != 0 )
                framebuffer.SetCursor( params[1] - 1, params[0] - 1 );
            break;
        case 'A':
        {
            std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            uint32_t x, y;
            framebuffer.Cursor( x, y );
            y -= params[0];
            y = std::max( 0u, y );
            framebuffer.SetCursor( x, y );
        }
        break;
        case 'B':
        {
            std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            uint32_t x, y;
            framebuffer.Cursor( x, y );
            y += params[0];
            y = std::min( framebuffer.Rows() - 1, y );
            framebuffer.SetCursor( x, y );
        }
        break;
        case 'C':
        {
            // std::cout << ch << " " << num_params << " " << params[0] << " " << framebuffer.Columns() << std::endl;
            uint32_t x, y;
            framebuffer.Cursor( x, y );
            x += params[0];
            x = std::min( framebuffer.Columns() - 1, x );
            framebuffer.SetCursor( x, y );
        }
        break;
        case 'D':
        {
            std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            uint32_t x, y;
            framebuffer.Cursor( x, y );
            x -= params[0];
            x = std::max( 0u, x );
            framebuffer.SetCursor( x, y );
        }
        break;
        case 'E':
        {
            std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            uint32_t x, y;
            framebuffer.Cursor( x, y );
            y += params[0];
            y = std::min( framebuffer.Rows() - 1, y );
            x = 0;
            framebuffer.SetCursor( x, y );
        }
        break;
        case 'F':
        {
            std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            uint32_t x, y;
            framebuffer.Cursor( x, y );
            y += params[0];
            y = std::min( framebuffer.Rows() - 1, y );
            x = 0;
            framebuffer.SetCursor( x, y );
        }
        break;
        case 'G':
        {
            std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            uint32_t x, y;
            framebuffer.Cursor( x, y );
            x = params[0];
            framebuffer.SetCursor( x, y );
        }
        break;
        case 'n':
            std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            break;
        case 'J':
        {
            std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            if( num_params == 0 )
            {
                framebuffer.BeginFrame();
                framebuffer.SetCursor( 0, 0 );
                break;
            }
            switch( params[0] )
            {
            case 1:
                break;
            case 0:
                break;
            case 2:
                framebuffer.BeginFrame();
                framebuffer.SetCursor( 0, 0 );
            default:
                break;
            }
        }
        break;
        case 'K':
        {
            if( num_params == 0 )
            {
                framebuffer.ClearCurrentLine();
                break;
            }

            std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            switch( params[0] )
            {
            case 1:
                break;
            case 2:
                break;
            case 0:
                framebuffer.ClearCurrentLine();
            default:
                break;
            }
        }
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
        break;
        case 'm':
            // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
            ProcessGraphicsMode( framebuffer );
            break;
        default:
            break;
        }
    }

    break;
    case Action::esc_dispatch:
        // std::cout << "Action::esc_dispatch"
        //           << " " << ch << " " << num_intermediate_chars << " "
        //           << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << intermediate_chars[0] << " "
        //           << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << intermediate_chars[1] << std::endl;
        //   << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint16_t)ch << std::endl;
        break;
    case Action::none:
        // std::cout << "Action::none" << std::endl;
        break;
    case Action::ignore:
    case Action::clear:
    case Action::collect:
    case Action::param:
    case Action::count:
    default:
        break;
    }
}

#define rgb( r, g, b ) \
    ( ( 255u << 24 ) | ( ( (uint8_t)r & 0xff ) << 16 ) | ( ( (uint8_t)g & 0xff ) << 8 ) | ( ( (uint8_t)b & 0xff ) << 0 ) )
// clang-format off
static const uint32_t colormapped[256] = {
    // Use the windows palette here: normal colors
    rgb( 0, 0, 0 ),       rgb( 128, 0, 0 ),     rgb( 0, 128, 0 ),     rgb( 128, 128, 0 ),
    rgb( 0, 0, 128 ),     rgb( 128, 0, 128 ),   rgb( 0, 128, 128 ),   rgb( 192, 192, 192 ),

    // Use the windows palette here: bright colors
    rgb( 128, 128, 128 ), rgb( 255, 0, 0 ),     rgb( 0, 255, 0 ),     rgb( 255, 255, 0 ),
    rgb( 0, 0, 255 ),     rgb( 255, 0, 255 ),   rgb( 0, 255, 255 ),   rgb( 255, 255, 255 ),

    rgb( 0, 0, 0 ),       rgb( 0, 0, 95 ),      rgb( 0, 0, 135 ),     rgb( 0, 0, 175 ),
    rgb( 0, 0, 215 ),     rgb( 0, 0, 255 ),     rgb( 0, 95, 0 ),      rgb( 0, 95, 95 ),
    rgb( 0, 95, 135 ),    rgb( 0, 95, 175 ),    rgb( 0, 95, 215 ),    rgb( 0, 95, 255 ),
    rgb( 0, 135, 0 ),     rgb( 0, 135, 95 ),    rgb( 0, 135, 135 ),   rgb( 0, 135, 175 ),
    rgb( 0, 135, 215 ),   rgb( 0, 135, 255 ),   rgb( 0, 175, 0 ),     rgb( 0, 175, 95 ),
    rgb( 0, 175, 135 ),   rgb( 0, 175, 175 ),   rgb( 0, 175, 215 ),   rgb( 0, 175, 255 ),
    rgb( 0, 215, 0 ),     rgb( 0, 215, 95 ),    rgb( 0, 215, 135 ),   rgb( 0, 215, 175 ),
    rgb( 0, 215, 215 ),   rgb( 0, 215, 255 ),   rgb( 0, 255, 0 ),     rgb( 0, 255, 95 ),
    rgb( 0, 255, 135 ),   rgb( 0, 255, 175 ),   rgb( 0, 255, 215 ),   rgb( 0, 255, 255 ),
    rgb( 95, 0, 0 ),      rgb( 95, 0, 95 ),     rgb( 95, 0, 135 ),    rgb( 95, 0, 175 ),
    rgb( 95, 0, 215 ),    rgb( 95, 0, 255 ),    rgb( 95, 95, 0 ),     rgb( 95, 95, 95 ),
    rgb( 95, 95, 135 ),   rgb( 95, 95, 175 ),   rgb( 95, 95, 215 ),   rgb( 95, 95, 255 ),
    rgb( 95, 135, 0 ),    rgb( 95, 135, 95 ),   rgb( 95, 135, 135 ),  rgb( 95, 135, 175 ),
    rgb( 95, 135, 215 ),  rgb( 95, 135, 255 ),  rgb( 95, 175, 0 ),    rgb( 95, 175, 95 ),
    rgb( 95, 175, 135 ),  rgb( 95, 175, 175 ),  rgb( 95, 175, 215 ),  rgb( 95, 175, 255 ),
    rgb( 95, 215, 0 ),    rgb( 95, 215, 95 ),   rgb( 95, 215, 135 ),  rgb( 95, 215, 175 ),
    rgb( 95, 215, 215 ),  rgb( 95, 215, 255 ),  rgb( 95, 255, 0 ),    rgb( 95, 255, 95 ),
    rgb( 95, 255, 135 ),  rgb( 95, 255, 175 ),  rgb( 95, 255, 215 ),  rgb( 95, 255, 255 ),
    rgb( 135, 0, 0 ),     rgb( 135, 0, 95 ),    rgb( 135, 0, 135 ),   rgb( 135, 0, 175 ),
    rgb( 135, 0, 215 ),   rgb( 135, 0, 255 ),   rgb( 135, 95, 0 ),    rgb( 135, 95, 95 ),
    rgb( 135, 95, 135 ),  rgb( 135, 95, 175 ),  rgb( 135, 95, 215 ),  rgb( 135, 95, 255 ),
    rgb( 135, 135, 0 ),   rgb( 135, 135, 95 ),  rgb( 135, 135, 135 ), rgb( 135, 135, 175 ),
    rgb( 135, 135, 215 ), rgb( 135, 135, 255 ), rgb( 135, 175, 0 ),   rgb( 135, 175, 95 ),
    rgb( 135, 175, 135 ), rgb( 135, 175, 175 ), rgb( 135, 175, 215 ), rgb( 135, 175, 255 ),
    rgb( 135, 215, 0 ),   rgb( 135, 215, 95 ),  rgb( 135, 215, 135 ), rgb( 135, 215, 175 ),
    rgb( 135, 215, 215 ), rgb( 135, 215, 255 ), rgb( 135, 255, 0 ),   rgb( 135, 255, 95 ),
    rgb( 135, 255, 135 ), rgb( 135, 255, 175 ), rgb( 135, 255, 215 ), rgb( 135, 255, 255 ),
    rgb( 175, 0, 0 ),     rgb( 175, 0, 95 ),    rgb( 175, 0, 135 ),   rgb( 175, 0, 175 ),
    rgb( 175, 0, 215 ),   rgb( 175, 0, 255 ),   rgb( 175, 95, 0 ),    rgb( 175, 95, 95 ),
    rgb( 175, 95, 135 ),  rgb( 175, 95, 175 ),  rgb( 175, 95, 215 ),  rgb( 175, 95, 255 ),
    rgb( 175, 135, 0 ),   rgb( 175, 135, 95 ),  rgb( 175, 135, 135 ), rgb( 175, 135, 175 ),
    rgb( 175, 135, 215 ), rgb( 175, 135, 255 ), rgb( 175, 175, 0 ),   rgb( 175, 175, 95 ),
    rgb( 175, 175, 135 ), rgb( 175, 175, 175 ), rgb( 175, 175, 215 ), rgb( 175, 175, 255 ),
    rgb( 175, 215, 0 ),   rgb( 175, 215, 95 ),  rgb( 175, 215, 135 ), rgb( 175, 215, 175 ),
    rgb( 175, 215, 215 ), rgb( 175, 215, 255 ), rgb( 175, 255, 0 ),   rgb( 175, 255, 95 ),
    rgb( 175, 255, 135 ), rgb( 175, 255, 175 ), rgb( 175, 255, 215 ), rgb( 175, 255, 255 ),
    rgb( 215, 0, 0 ),     rgb( 215, 0, 95 ),    rgb( 215, 0, 135 ),   rgb( 215, 0, 175 ),
    rgb( 215, 0, 215 ),   rgb( 215, 0, 255 ),   rgb( 215, 95, 0 ),    rgb( 215, 95, 95 ),
    rgb( 215, 95, 135 ),  rgb( 215, 95, 175 ),  rgb( 215, 95, 215 ),  rgb( 215, 95, 255 ),
    rgb( 215, 135, 0 ),   rgb( 215, 135, 95 ),  rgb( 215, 135, 135 ), rgb( 215, 135, 175 ),
    rgb( 215, 135, 215 ), rgb( 215, 135, 255 ), rgb( 215, 175, 0 ),   rgb( 215, 175, 95 ),
    rgb( 215, 175, 135 ), rgb( 215, 175, 175 ), rgb( 215, 175, 215 ), rgb( 215, 175, 255 ),
    rgb( 215, 215, 0 ),   rgb( 215, 215, 95 ),  rgb( 215, 215, 135 ), rgb( 215, 215, 175 ),
    rgb( 215, 215, 215 ), rgb( 215, 215, 255 ), rgb( 215, 255, 0 ),   rgb( 215, 255, 95 ),
    rgb( 215, 255, 135 ), rgb( 215, 255, 175 ), rgb( 215, 255, 215 ), rgb( 215, 255, 255 ),
    rgb( 255, 0, 0 ),     rgb( 255, 0, 95 ),    rgb( 255, 0, 135 ),   rgb( 255, 0, 175 ),
    rgb( 255, 0, 215 ),   rgb( 255, 0, 255 ),   rgb( 255, 95, 0 ),    rgb( 255, 95, 95 ),
    rgb( 255, 95, 135 ),  rgb( 255, 95, 175 ),  rgb( 255, 95, 215 ),  rgb( 255, 95, 255 ),
    rgb( 255, 135, 0 ),   rgb( 255, 135, 95 ),  rgb( 255, 135, 135 ), rgb( 255, 135, 175 ),
    rgb( 255, 135, 215 ), rgb( 255, 135, 255 ), rgb( 255, 175, 0 ),   rgb( 255, 175, 95 ),
    rgb( 255, 175, 135 ), rgb( 255, 175, 175 ), rgb( 255, 175, 215 ), rgb( 255, 175, 255 ),
    rgb( 255, 215, 0 ),   rgb( 255, 215, 95 ),  rgb( 255, 215, 135 ), rgb( 255, 215, 175 ),
    rgb( 255, 215, 215 ), rgb( 255, 215, 255 ), rgb( 255, 255, 0 ),   rgb( 255, 255, 95 ),
    rgb( 255, 255, 135 ), rgb( 255, 255, 175 ), rgb( 255, 255, 215 ), rgb( 255, 255, 255 ),
    rgb( 8, 8, 8 ),       rgb( 18, 18, 18 ),    rgb( 28, 28, 28 ),    rgb( 38, 38, 38 ),
    rgb( 48, 48, 48 ),    rgb( 58, 58, 58 ),    rgb( 68, 68, 68 ),    rgb( 78, 78, 78 ),
    rgb( 88, 88, 88 ),    rgb( 98, 98, 98 ),    rgb( 108, 108, 108 ), rgb( 118, 118, 118 ),
    rgb( 128, 128, 128 ), rgb( 138, 138, 138 ), rgb( 148, 148, 148 ), rgb( 158, 158, 158 ),
    rgb( 168, 168, 168 ), rgb( 178, 178, 178 ), rgb( 188, 188, 188 ), rgb( 198, 198, 198 ),
    rgb( 208, 208, 208 ), rgb( 218, 218, 218 ), rgb( 228, 228, 228 ), rgb( 238, 238, 238 ) 
};
// clang-format on

void Vt100Parser::ProcessGraphicsMode( framebuffer_t &framebuffer )
{
    if( num_params == 0 )
    {
        _bold      = false;
        _faint     = false;
        _italic    = false;
        _underline = false;
        _strikeout = false;
        _reversed  = false;
        _hidden    = false;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        framebuffer.SetForeground( 0u );
        framebuffer.SetBackground( 0u );

        return;
    }

    auto code = params[0];

    switch( code )
    {
    case 0:
        _bold      = false;
        _faint     = false;
        _italic    = false;
        _underline = false;
        _strikeout = false;
        _reversed  = false;
        _hidden    = false;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        framebuffer.SetForeground( 0u );
        framebuffer.SetBackground( 0u );
        // std::cout << "RESET1" << std::endl;
        break; // Reset or normal	All attributes become turned off
    case 1:
        _bold = true;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Bold or increased intensity	As with faint, the color change is a PC (SCO / CGA) invention.[25][better source
               // needed]
    case 2:
        _faint = true;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Faint, decreased intensity, or dim	May be implemented as a light font weight like bold.[26]
    case 3:
        _italic = true;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Italic	Not widely supported. Sometimes treated as inverse or blink.[25]
    case 4:
        _underline = true;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Underline	Style extensions exist for Kitty, VTE, mintty, iTerm2 and Konsole.[27][28][29]
    case 5:
        break; // Slow blink	Sets blinking to less than 150 times per minute
    case 6:
        break; // Rapid blink	MS-DOS ANSI.SYS, 150+ per minute; not widely supported
    case 7:
        _reversed = true;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Reverse video or invert	Swap foreground and background colors; inconsistent emulation[30][dubious – discuss]
    case 8:
        _hidden = true;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Conceal or hide	Not widely supported.
    case 9:
        _strikeout = true;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Crossed-out, or strike	Characters legible but marked as if for deletion. Not supported in Terminal.app.
    case 10:
        break; // Primary (default) font
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        break; // Alternative font	Select alternative font n − 10
    case 20:
        break; // Fraktur (Gothic)	Rarely supported
    case 21:
        break; // Doubly underlined; or: not bold	Double-underline per ECMA-48,[5]: 8.3.117  but instead disables bold intensity on
               // several terminals, including in the Linux kernel's console before version 4.17.[31]
    case 22:
        _bold  = false;
        _faint = false;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Normal intensity	Neither bold nor faint; color changes where intensity is implemented as such.
    case 23:
        _italic = false;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Neither italic, nor blackletter
    case 24:
        _underline = false;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Not underlined	Neither singly nor doubly underlined
    case 25:
        break; // Not blinking	Turn blinking off
    case 26:
        break; // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
    case 27:
        _reversed = false;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Not reversed
    case 28:
        _hidden = false;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Reveal	Not concealed
    case 29:
        _strikeout = false;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden );
        break; // Not crossed out
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
        _foregroundColor = colormapped[code - 30];
        framebuffer.SetForeground( _foregroundColor );
        break; // Next arguments are 5;n or 2;r;g;b
    case 38:
    {
        if( params[1] == 2 )
        {
            framebuffer.SetForeground( params[2], params[3], params[4] );
        }
        else if( params[1] == 5 )
        {
            framebuffer.SetForeground( colormapped[params[3]] );
        }
    }
    break; // Next arguments are 5;n or 2;r;g;b
    case 39:
        framebuffer.SetForeground( 0u );
        break; // Default foreground color	Implementation defined (according to standard)
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
        _backgroundColor = colormapped[code - 30];
        framebuffer.SetBackground( _backgroundColor );
        break; // Set background color	Next arguments are 5;n or 2;r;g;b
    case 48:
    {
        if( params[1] == 2 )
        {
            framebuffer.SetBackground( params[2], params[3], params[4] );
        }
        else if( params[1] == 5 )
        {
            framebuffer.SetBackground( colormapped[params[3]] );
        }
    }
    break; // Set background color	Next arguments are 5;n or 2;r;g;b
    case 49:
        framebuffer.SetBackground( 0u );
        break; // Default background color	Implementation defined (according to standard)
    case 50:
        break; // Disable proportional spacing	T.61 and T.416
    case 51:
        break; // Framed	Implemented as "emoji variation selector" in mintty.[32]
    case 52:
        break; // Encircled
    case 53:
        break; // Overlined	Not supported in Terminal.app
    case 54:
        break; // Neither framed nor encircled
    case 55:
        break; // Not overlined
    case 58:
        break; // Set underline color	Not in standard; implemented in Kitty, VTE, mintty, and iTerm2.[27][28] Next arguments are 5;n
               // or 2;r;g;b.
    case 59:
        break; // Default underline color	Not in standard; implemented in Kitty, VTE, mintty, and iTerm2.[27][28]
    case 60:
        break; // Ideogram underline or right side line	Rarely supported
    case 61:
        break; // Ideogram double underline, or double line on the right side
    case 62:
        break; // Ideogram overline or left side line
    case 63:
        break; // Ideogram double overline, or double line on the left side
    case 64:
        break; // Ideogram stress marking
    case 65:
        break; // No ideogram attributes	Reset the effects of all of 60–64
    case 73:
        break; // Superscript	Implemented only in mintty[32]
    case 74:
        break; // Subscript
    case 75:
        break; // Neither superscript nor subscript
    case 90:
    case 91:
    case 92:
    case 93:
    case 94:
    case 95:
    case 96:
    case 97:
        _foregroundColor = colormapped[code - 82];
        framebuffer.SetForeground( _foregroundColor );
        break; // Set bright foreground color	Not in standard; originally implemented by aixterm[16]
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 107:
        _backgroundColor = colormapped[code - 92];
        framebuffer.SetBackground( _backgroundColor );
    default:
        break;
    }
}

void Vt100Parser::Erase( framebuffer_t &framebuffer )
{
}

void Vt100Parser::do_action( framebuffer_t &framebuffer, Action action, char ch )
{
    /* Some actions we handle internally (like parsing parameters), others
     * we hand to our client for processing */

    switch( action )
    {
    case Action::print:
    case Action::execute:
    case Action::hook:
    case Action::put:
    case Action::osc_start:
    case Action::osc_put:
    case Action::osc_end:
    case Action::unhook:
    case Action::csi_dispatch:
    case Action::esc_dispatch:
        Dispatch( framebuffer, action, ch );
        break;

    case Action::ignore:
        /* do nothing */
        break;

    case Action::collect:
    {
        /* Append the character to the intermediate params */
        if( num_intermediate_chars + 1 > MAX_INTERMEDIATE_CHARS )
            ignore_flagged = 1;
        else
            intermediate_chars[num_intermediate_chars++] = ch;

        break;
    }

    case Action::param:
    {
        /* process the param character */

        if( ch == ';' )
        {
            num_params += 1;
            params[num_params - 1] = 0;
        }
        else
        {
            /* the character is a digit */
            int current_param;

            if( num_params == 0 )
            {
                num_params = 1;
                params[0]  = 0;
            }

            current_param = num_params - 1;
            params[current_param] *= 10;
            params[current_param] += ( ch - '0' );
        }

        break;
    }

    case Action::clear:
        num_intermediate_chars = 0;
        num_params             = 0;
        ignore_flagged         = 0;
        break;

    default:
        Dispatch( framebuffer, Action::none, 0 );
        break;
    }
}

void Vt100Parser::do_state_change( framebuffer_t &framebuffer, VtParserState new_state, Action action, char ch )
{
    /* A state change is an action and/or a new state to transition to. */

    if( new_state != VtParserState::none )
    {
        /* Perform up to three actions:
         *   1. the exit action of the old state
         *   2. the action associated with the transition
         *   3. the entry action of the new state
         */

        Action exit_action  = _exitActions[(int)state];
        Action entry_action = _entryActions[(int)new_state];

        if( exit_action != Action::none )
            do_action( framebuffer, exit_action, 0 );

        if( action != Action::none )
            do_action( framebuffer, action, ch );

        if( entry_action != Action::none )
            do_action( framebuffer, entry_action, 0 );

        state = new_state;
    }
    else
    {
        do_action( framebuffer, action, ch );
    }
}

void Vt100Parser::vtparse( framebuffer_t &framebuffer, unsigned char *data, int len )
{
    int i;
    for( i = 0; i < len; i++ )
    {
        unsigned char      ch     = data[i];
        state_transition_t change = _stateTransitions[(uint8_t)state][ch];
        // std::cout << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint32_t)ch << " ";
        do_state_change( framebuffer, change.TransitionTo, change.Action, ch );
    }
}

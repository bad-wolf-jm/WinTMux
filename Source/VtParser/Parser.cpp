#include "Parser.h"
#include "Console/FrameBuffer.h"
#include "States.h"
#include "VtParser/csi_commands.h"

#include <cstdint>
#include <iomanip>
#include <iostream>

vtparser_t::vtparser_t()
{
    state                  = vtparser_state::ground;
    num_intermediate_chars = 0;
    num_params             = 0;
    ignore_flagged         = 0;
    // cb                     = cb;

    // Anywhere transitions
    OnEvent( 0x18, vtparser_action::execute, vtparser_state::ground );
    OnEvent( 0x1a, vtparser_action::execute, vtparser_state::ground );
    OnEvent( Range{ 0x80, 0x8f }, vtparser_action::execute, vtparser_state::ground );
    OnEvent( Range{ 0x91, 0x97 }, vtparser_action::execute, vtparser_state::ground );
    OnEvent( 0x99, vtparser_action::execute, vtparser_state::ground );
    OnEvent( 0x9a, vtparser_action::execute, vtparser_state::ground );
    OnEvent( 0x9c, vtparser_state::ground );
    OnEvent( 0x1b, vtparser_state::escape );
    OnEvent( 0x98, vtparser_state::sos_pm_apc_string );
    OnEvent( 0x9e, vtparser_state::sos_pm_apc_string );
    OnEvent( 0x9f, vtparser_state::sos_pm_apc_string );
    OnEvent( 0x90, vtparser_state::dcs_entry );
    OnEvent( 0x9d, vtparser_state::osc_string );
    OnEvent( 0x9b, vtparser_state::csi_entry );

    // Transitions from ground state
    OnEvent( vtparser_state::ground, Range{ 0x00, 0x17 }, vtparser_action::execute );
    OnEvent( vtparser_state::ground, 0x19, vtparser_action::execute );
    OnEvent( vtparser_state::ground, Range{ 0x1c, 0x1f }, vtparser_action::execute );
    OnEvent( vtparser_state::ground, Range{ 0x20, 0x7f }, vtparser_action::print );

    //$states[:ESCAPE] = {
    OnEntry( vtparser_state::escape, vtparser_action::clear );
    OnEvent( vtparser_state::escape, Range{ 0x00, 0x17 }, vtparser_action::execute );
    OnEvent( vtparser_state::escape, 0x19, vtparser_action::execute );
    OnEvent( vtparser_state::escape, Range{ 0x1c, 0x1f }, vtparser_action::execute );
    OnEvent( vtparser_state::escape, 0x7f, vtparser_action::ignore );
    OnEvent( vtparser_state::escape, Range{ 0x20, 0x2f }, vtparser_action::collect, vtparser_state::escape_intermediate );
    OnEvent( vtparser_state::escape, Range{ 0x30, 0x4f }, vtparser_action::esc_dispatch, vtparser_state::ground );
    OnEvent( vtparser_state::escape, Range{ 0x51, 0x57 }, vtparser_action::esc_dispatch, vtparser_state::ground );
    OnEvent( vtparser_state::escape, 0x59, vtparser_action::esc_dispatch, vtparser_state::ground );
    OnEvent( vtparser_state::escape, 0x5a, vtparser_action::esc_dispatch, vtparser_state::ground );
    OnEvent( vtparser_state::escape, 0x5c, vtparser_action::esc_dispatch, vtparser_state::ground );
    OnEvent( vtparser_state::escape, Range{ 0x60, 0x7e }, vtparser_action::esc_dispatch, vtparser_state::ground );
    OnEvent( vtparser_state::escape, 0x5b, vtparser_state::csi_entry );
    OnEvent( vtparser_state::escape, 0x5d, vtparser_state::osc_string );
    OnEvent( vtparser_state::escape, 0x50, vtparser_state::dcs_entry );
    OnEvent( vtparser_state::escape, 0x58, vtparser_state::sos_pm_apc_string );
    OnEvent( vtparser_state::escape, 0x5e, vtparser_state::sos_pm_apc_string );
    OnEvent( vtparser_state::escape, 0x5f, vtparser_state::sos_pm_apc_string );

    //$states[:ESCAPE_INTERMEDIATE] = {
    OnEvent( vtparser_state::escape_intermediate, Range{ 0x00, 0x17 }, vtparser_action::execute );
    OnEvent( vtparser_state::escape_intermediate, 0x19, vtparser_action::execute );
    OnEvent( vtparser_state::escape_intermediate, Range{ 0x1c, 0x1f }, vtparser_action::execute );
    OnEvent( vtparser_state::escape_intermediate, Range{ 0x20, 0x2f }, vtparser_action::collect );
    OnEvent( vtparser_state::escape_intermediate, 0x7f, vtparser_action::ignore );
    OnEvent( vtparser_state::escape_intermediate, Range{ 0x30, 0x7e }, vtparser_action::esc_dispatch, vtparser_state::ground );

    //$states[:CSI_ENTRY] = {
    OnEntry( vtparser_state::csi_entry, vtparser_action::clear );
    OnEvent( vtparser_state::csi_entry, Range{ 0x00, 0x17 }, vtparser_action::execute );
    OnEvent( vtparser_state::csi_entry, 0x19, vtparser_action::execute );
    OnEvent( vtparser_state::csi_entry, Range{ 0x1c, 0x1f }, vtparser_action::execute );
    OnEvent( vtparser_state::csi_entry, 0x7f, vtparser_action::ignore );
    OnEvent( vtparser_state::csi_entry, Range{ 0x20, 0x2f }, vtparser_action::collect, vtparser_state::csi_intermediate );
    OnEvent( vtparser_state::csi_entry, 0x3a, vtparser_state::csi_ignore );
    OnEvent( vtparser_state::csi_entry, Range{ 0x30, 0x39 }, vtparser_action::param, vtparser_state::csi_param );
    OnEvent( vtparser_state::csi_entry, 0x3b, vtparser_action::param, vtparser_state::csi_param );
    OnEvent( vtparser_state::csi_entry, Range{ 0x3c, 0x3f }, vtparser_action::collect, vtparser_state::csi_param );
    OnEvent( vtparser_state::csi_entry, Range{ 0x40, 0x7e }, vtparser_action::csi_dispatch, vtparser_state::ground );

    //$states[:CSI_IGNORE] = {
    OnEvent( vtparser_state::csi_ignore, Range{ 0x00, 0x17 }, vtparser_action::execute );
    OnEvent( vtparser_state::csi_ignore, 0x19, vtparser_action::execute );
    OnEvent( vtparser_state::csi_ignore, Range{ 0x1c, 0x1f }, vtparser_action::execute );
    OnEvent( vtparser_state::csi_ignore, Range{ 0x20, 0x3f }, vtparser_action::ignore );
    OnEvent( vtparser_state::csi_ignore, 0x7f, vtparser_action::ignore );
    OnEvent( vtparser_state::csi_ignore, Range{ 0x40, 0x7e }, vtparser_state::ground );

    //$states[:CSI_PARAM] = {
    OnEvent( vtparser_state::csi_param, Range{ 0x00, 0x17 }, vtparser_action::execute );
    OnEvent( vtparser_state::csi_param, 0x19, vtparser_action::execute );
    OnEvent( vtparser_state::csi_param, Range{ 0x1c, 0x1f }, vtparser_action::execute );
    OnEvent( vtparser_state::csi_param, Range{ 0x30, 0x39 }, vtparser_action::param );
    OnEvent( vtparser_state::csi_param, 0x3b, vtparser_action::param );
    OnEvent( vtparser_state::csi_param, 0x7f, vtparser_action::ignore );
    OnEvent( vtparser_state::csi_param, 0x3a, vtparser_state::csi_ignore );
    OnEvent( vtparser_state::csi_param, Range{ 0x3c, 0x3f }, vtparser_state::csi_ignore );
    OnEvent( vtparser_state::csi_param, Range{ 0x20, 0x2f }, vtparser_action::collect, vtparser_state::csi_intermediate );
    OnEvent( vtparser_state::csi_param, Range{ 0x40, 0x7e }, vtparser_action::csi_dispatch, vtparser_state::ground );

    //$states[:CSI_INTERMEDIATE] = {
    OnEvent( vtparser_state::csi_intermediate, Range{ 0x00, 0x17 }, vtparser_action::execute );
    OnEvent( vtparser_state::csi_intermediate, 0x19, vtparser_action::execute );
    OnEvent( vtparser_state::csi_intermediate, Range{ 0x1c, 0x1f }, vtparser_action::execute );
    OnEvent( vtparser_state::csi_intermediate, Range{ 0x20, 0x2f }, vtparser_action::collect );
    OnEvent( vtparser_state::csi_intermediate, 0x7f, vtparser_action::ignore );
    OnEvent( vtparser_state::csi_intermediate, Range{ 0x30, 0x3f }, vtparser_state::csi_ignore );
    OnEvent( vtparser_state::csi_intermediate, Range{ 0x40, 0x7e }, vtparser_action::csi_dispatch, vtparser_state::ground );
    //}

    //$states[:DCS_ENTRY] = {
    OnEntry( vtparser_state::dcs_entry, vtparser_action::clear );
    OnEvent( vtparser_state::dcs_entry, Range{ 0x00, 0x17 }, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_entry, 0x19, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_entry, Range{ 0x1c, 0x1f }, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_entry, 0x7f, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_entry, 0x3a, vtparser_state::dcs_ignore );
    OnEvent( vtparser_state::dcs_entry, Range{ 0x20, 0x2f }, vtparser_action::collect, vtparser_state::dcs_intermediate );
    OnEvent( vtparser_state::dcs_entry, Range{ 0x30, 0x39 }, vtparser_action::param, vtparser_state::dcs_param );
    OnEvent( vtparser_state::dcs_entry, 0x3b, vtparser_action::param, vtparser_state::dcs_param );
    OnEvent( vtparser_state::dcs_entry, Range{ 0x3c, 0x3f }, vtparser_action::collect, vtparser_state::dcs_param );
    OnEvent( vtparser_state::dcs_entry, Range{ 0x40, 0x7e }, vtparser_state::dcs_passthrough );

    //$states[:DCS_INTERMEDIATE] = {
    OnEvent( vtparser_state::dcs_intermediate, Range{ 0x00, 0x17 }, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_intermediate, 0x19, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_intermediate, Range{ 0x1c, 0x1f }, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_intermediate, Range{ 0x20, 0x2f }, vtparser_action::collect );
    OnEvent( vtparser_state::dcs_intermediate, 0x7f, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_intermediate, Range{ 0x30, 0x3f }, vtparser_state::dcs_ignore );
    OnEvent( vtparser_state::dcs_intermediate, Range{ 0x40, 0x7e }, vtparser_state::dcs_passthrough );

    //$states[:DCS_IGNORE] = {
    OnEvent( vtparser_state::dcs_ignore, Range{ 0x00, 0x17 }, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_ignore, 0x19, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_ignore, Range{ 0x1c, 0x1f }, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_ignore, Range{ 0x20, 0x7f }, vtparser_action::ignore );

    //$states[:DCS_PARAM] = {
    OnEvent( vtparser_state::dcs_param, Range{ 0x00, 0x17 }, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_param, 0x19, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_param, Range{ 0x1c, 0x1f }, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_param, Range{ 0x30, 0x39 }, vtparser_action::param );
    OnEvent( vtparser_state::dcs_param, 0x3b, vtparser_action::param );
    OnEvent( vtparser_state::dcs_param, 0x7f, vtparser_action::ignore );
    OnEvent( vtparser_state::dcs_param, 0x3a, vtparser_state::dcs_ignore );
    OnEvent( vtparser_state::dcs_param, Range{ 0x3c, 0x3f }, vtparser_state::dcs_ignore );
    OnEvent( vtparser_state::dcs_param, Range{ 0x20, 0x2f }, vtparser_action::collect, vtparser_state::dcs_intermediate );
    OnEvent( vtparser_state::dcs_param, Range{ 0x40, 0x7e }, vtparser_state::dcs_passthrough );

    //$states[:DCS_PASSTHROUGH] = {
    OnEntry( vtparser_state::dcs_passthrough, vtparser_action::hook );
    OnExit( vtparser_state::dcs_passthrough, vtparser_action::unhook );
    OnEvent( vtparser_state::dcs_passthrough, Range{ 0x00, 0x17 }, vtparser_action::put );
    OnEvent( vtparser_state::dcs_passthrough, 0x19, vtparser_action::put );
    OnEvent( vtparser_state::dcs_passthrough, Range{ 0x1c, 0x1f }, vtparser_action::put );
    OnEvent( vtparser_state::dcs_passthrough, Range{ 0x20, 0x7e }, vtparser_action::put );
    OnEvent( vtparser_state::dcs_passthrough, 0x7f, vtparser_action::ignore );

    //$states[:SOS_PM_APC_STRING] = {
    OnEvent( vtparser_state::sos_pm_apc_string, Range{ 0x00, 0x17 }, vtparser_action::ignore );
    OnEvent( vtparser_state::sos_pm_apc_string, 0x19, vtparser_action::ignore );
    OnEvent( vtparser_state::sos_pm_apc_string, Range{ 0x1c, 0x1f }, vtparser_action::ignore );
    OnEvent( vtparser_state::sos_pm_apc_string, Range{ 0x20, 0x7f }, vtparser_action::ignore );

    //$states[:OSC_STRING] = {
    OnEntry( vtparser_state::osc_string, vtparser_action::osc_start );
    OnExit( vtparser_state::osc_string, vtparser_action::osc_end );
    OnEvent( vtparser_state::osc_string, Range{ 0x00, 0x17 }, vtparser_action::ignore );
    OnEvent( vtparser_state::osc_string, 0x19, vtparser_action::ignore );
    OnEvent( vtparser_state::osc_string, Range{ 0x1c, 0x1f }, vtparser_action::ignore );
    OnEvent( vtparser_state::osc_string, Range{ 0x20, 0x7f }, vtparser_action::osc_put );
}

void vtparser_t::OnEntry( vtparser_state state, vtparser_action action )
{
    _entryActions[(uint8_t)state] = action;
}

void vtparser_t::OnExit( vtparser_state state, vtparser_action action )
{
    _exitActions[(uint8_t)state] = action;
}

void vtparser_t::OnEvent( Range range, vtparser_action action )
{
    OnEvent( range, action, vtparser_state::none );
}

void vtparser_t::OnEvent( Range range, vtparser_state transitionTo )
{
    OnEvent( range, vtparser_action::none, transitionTo );
}

void vtparser_t::OnEvent( Range range, vtparser_action action, vtparser_state transitionTo )
{
    for( int i = 0; i < (int)vtparser_state::count; i++ )
        OnEvent( (vtparser_state)i, range, action, transitionTo );
}

void vtparser_t::OnEvent( vtparser_state state, Range range, vtparser_action action )
{
    OnEvent( state, range, action, vtparser_state::none );
}

void vtparser_t::OnEvent( vtparser_state state, Range range, vtparser_state transitionTo )
{
    OnEvent( state, range, vtparser_action::none, transitionTo );
}

void vtparser_t::OnEvent( vtparser_state state, Range range, vtparser_action action, vtparser_state transitionTo )
{
    for( uint8_t c = range.Start; c <= range.End; c++ )
        OnEvent( state, c, action, transitionTo );
}

void vtparser_t::OnEvent( uint8_t character, vtparser_action action )
{
    OnEvent( character, action, vtparser_state::none );
}

void vtparser_t::OnEvent( uint8_t character, vtparser_state transitionTo )
{
    OnEvent( character, vtparser_action::none, transitionTo );
}

void vtparser_t::OnEvent( uint8_t character, vtparser_action action, vtparser_state transitionTo )
{
    for( int i = 0; i < (int)vtparser_state::count; i++ )
        OnEvent( (vtparser_state)i, character, action, transitionTo );
}

void vtparser_t::OnEvent( vtparser_state state, uint8_t character, vtparser_action action )
{
    OnEvent( state, character, action, vtparser_state::none );
}

void vtparser_t::OnEvent( vtparser_state state, uint8_t character, vtparser_state transitionTo )
{
    OnEvent( state, character, vtparser_action::none, transitionTo );
}

void vtparser_t::OnEvent( vtparser_state state, uint8_t character, vtparser_action action, vtparser_state transitionTo )
{
    _stateTransitions[(uint8_t)state][character] = state_transition_t{ transitionTo, action };
}

void vtparser_t::dispatch_csi( char ch, framebuffer_t &framebuffer )
{
    switch( ch )
    {
    case csi_command::move:
        if( num_params == 0 )
            framebuffer.SetCursor( 0, 0 );
        else
        {
            // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;

            framebuffer.SetCursor( params[1] - 1, params[0] - 1 );
        }
        break;
    case csi_command::move_1:
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
        if( num_params != 0 )
            framebuffer.SetCursor( params[1] - 1, params[0] - 1 );
        break;
    case csi_command::move_up:
    {
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
        uint32_t x, y;
        framebuffer.Cursor( x, y );
        y -= params[0];
        y = std::max( 0u, y );
        framebuffer.SetCursor( x, y );
    }
    break;
    case csi_command::move_down:
    {
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
        uint32_t x, y;
        framebuffer.Cursor( x, y );
        y += params[0];
        y = std::min( framebuffer.Rows() - 1, y );
        framebuffer.SetCursor( x, y );
    }
    break;
    case csi_command::move_right:
    {
        // std::cout << ch << " " << num_params << " " << params[0] << " " << framebuffer.Columns() << std::endl;
        uint32_t x, y;
        framebuffer.Cursor( x, y );
        x += params[0];
        x = std::min( framebuffer.Columns() - 1, x );
        framebuffer.SetCursor( x, y );
    }
    break;
    case csi_command::move_left:
    {
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
        uint32_t x, y;
        framebuffer.Cursor( x, y );
        x -= params[0];
        x = std::max( 0u, x );
        framebuffer.SetCursor( x, y );
    }
    break;
    case csi_command::move_down_bol:
    {
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
        uint32_t x, y;
        framebuffer.Cursor( x, y );
        y += params[0];
        y = std::min( framebuffer.Rows() - 1, y );
        x = 0;
        framebuffer.SetCursor( x, y );
    }
    break;
    case csi_command::move_up_bol:
    {
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
        uint32_t x, y;
        framebuffer.Cursor( x, y );
        y += params[0];
        y = std::min( framebuffer.Rows() - 1, y );
        x = 0;
        framebuffer.SetCursor( x, y );
    }
    break;
    case csi_command::move_to_column:
    {
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
        uint32_t x, y;
        framebuffer.Cursor( x, y );
        x = params[0];
        framebuffer.SetCursor( x, y );
    }
    break;
    case csi_command::device_status_report:
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
        break;
    case csi_command::erase_screen:
    {
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
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
    case csi_command::erase_line:
    {
        if( num_params == 0 )
        {
            framebuffer.ClearCurrentLine();
            break;
        }

        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
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
    case csi_command::graphics_mode:
        // std::cout << ch << " " << num_params << " " << params[0] << " " << params[1] << std::endl;
        ProcessGraphicsMode( framebuffer );
        break;
    default:
        break;
    }
}

void vtparser_t::Dispatch( framebuffer_t &framebuffer, vtparser_action action, char ch )
{

    switch( action )
    {
    case vtparser_action::print:
        // if( ch == ' ' )
        //     std::cout << "SPACE" << std::hex << (uint8_t)action << " "
        //               << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint16_t)ch << std::endl;
        framebuffer.putc( ch );
        break;
    case vtparser_action::execute:
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
    case vtparser_action::hook:
        // std::cout << "vtparser_action::hook" << std::endl;
        break;
    case vtparser_action::put:
        // std::cout << "vtparser_action::put" << std::endl;
        break;
    case vtparser_action::osc_start:
        // std::cout << "vtparser_action::osc_start"
        //   << " " << ch << std::endl;
        //   << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint16_t)ch << std::endl;
        break;
    case vtparser_action::osc_put:
        // std::cout << "vtparser_action::osc_put"
        //   << " " << ch << std::endl;
        //   << " "
        //   << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint16_t)ch << std::endl;
        break;
    case vtparser_action::osc_end:
        // std::cout << "vtparser_action::osc_end" //    << " " << ch << std::endl;
        //   << " "
        //   << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint16_t)ch << std::endl;
        break;
    case vtparser_action::unhook:
        break;
    case vtparser_action::csi_dispatch:
    {
        dispatch_csi( ch, framebuffer );
    }

    break;
    case vtparser_action::esc_dispatch:
        // std::cout << "vtparser_action::esc_dispatch"
        //           << " " << ch << " " << num_intermediate_chars << " "
        //           << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << intermediate_chars[0] << " "
        //           << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << intermediate_chars[1] << std::endl;
        //   << "0x" << std::setw( 2 ) << std::setfill( '0' ) << std::hex << (uint16_t)ch << std::endl;
        break;
    case vtparser_action::none:
        // std::cout << "vtparser_action::none" << std::endl;
        break;
    case vtparser_action::ignore:
    case vtparser_action::clear:
    case vtparser_action::collect:
    case vtparser_action::param:
    case vtparser_action::count:
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

void vtparser_t::ProcessGraphicsMode( framebuffer_t &framebuffer )
{
    auto code = params[0];
    if( ( code >= 10 && code <= 21 ) || ( code >= 50 && code <= 75 ) )
        return;

    if( num_params == 0 || code == 0 )
    {
        _bold      = false;
        _faint     = false;
        _italic    = false;
        _underline = false;
        _strikeout = false;
        _reversed  = false;
        _hidden    = false;
        _slowBlink = false;
        _fastBlink = false;
        framebuffer.SetTextAttributes( _bold, _italic, _underline, _strikeout, _faint, _reversed, _hidden, _slowBlink, _fastBlink );
        framebuffer.SetForeground( 0u );
        framebuffer.SetBackground( 0u );

        return;
    }

    if( code >= 30 && code <= 37 )
    {
        _foregroundColor = colormapped[code - 30];
        framebuffer.SetForeground( _foregroundColor );
        return;
    }

    if( code >= 90 && code <= 97 )
    {
        _foregroundColor = colormapped[code - 82];
        framebuffer.SetForeground( _foregroundColor );
        return;
    }

    if( code >= 40 && code <= 47 )
    {
        _backgroundColor = colormapped[code - 40];
        framebuffer.SetBackground( _backgroundColor );
        return;
    }

    if( code >= 100 && code <= 107 )
    {
        _backgroundColor = colormapped[code - 92];
        framebuffer.SetBackground( _backgroundColor );
        return;
    }

    if( ( code >= 1 && code < 9 ) || ( code >= 22 && code <= 29 ) )
    {
        constexpr int _bold      = 0;
        constexpr int _faint     = 1;
        constexpr int _italic    = 2;
        constexpr int _underline = 3;
        constexpr int _slowBlink = 4;
        constexpr int _fastBlink = 5;
        constexpr int _reversed  = 6;
        constexpr int _hidden    = 7;
        constexpr int _strikeout = 8;

        if( code >= 1 && code < 9 )
        {
            _textAttributes[code - 1] = true;
        }
        else
        {
            switch( code )
            {
            case 22:
                _textAttributes[_bold]  = false;
                _textAttributes[_faint] = false;
                break;
            case 23:
                _textAttributes[_italic] = false;
                break;
            case 24:
                _textAttributes[_underline] = false;
                break; // Not underlined	Neither singly nor doubly underlined
            case 25:
                _textAttributes[_slowBlink] = false;
                _textAttributes[_fastBlink] = false;
                break; // Not blinking	Turn blinking off
            case 26:
                break; // Proportional spacing	ITU T.61 and T.416, not known to be used on terminals
            case 27:
                _textAttributes[_reversed] = false;
                break; // Not reversed
            case 28:
                _textAttributes[_hidden] = false;
                break; // Reveal	Not concealed
            case 29:
                _textAttributes[_strikeout] = false;
                break;
            }
        }

        // clang-format off
        framebuffer.SetTextAttributes( 
            _textAttributes[_bold], _textAttributes[_italic], _textAttributes[_underline], _textAttributes[_strikeout], 
            _textAttributes[_faint], _textAttributes[_reversed], _textAttributes[_hidden], _textAttributes[_slowBlink], 
            _textAttributes[_fastBlink] );
        // clang-format on       
        return;
    }

    if(code == 38)
    {
        if( params[1] == 2 )
        {
            framebuffer.SetForeground( params[2], params[3], params[4] );
        }
        else if( params[1] == 5 )
        {
            framebuffer.SetForeground( colormapped[params[3]] );
        }

        return; // Next arguments are 5;n or 2;r;g;b
    }

    if(code == 39)
    {
        framebuffer.SetForeground( 0u );
        return;
    }

    if(code == 48)
    {
        if( params[1] == 2 )
        {
            framebuffer.SetBackground( params[2], params[3], params[4] );
        }
        else if( params[1] == 5 )
        {
            framebuffer.SetBackground( colormapped[params[3]] );
        }

        return; // Set background color	Next arguments are 5;n or 2;r;g;b
    }

    if(code == 49)
    {
        framebuffer.SetBackground( 0u );
        return; // Default background color	Implementation defined (according to standard)$^
    }
}

void vtparser_t::Erase( framebuffer_t &framebuffer )
{
}

void vtparser_t::do_action( framebuffer_t &framebuffer, vtparser_action action, char ch )
{
    /* Some actions we handle internally (like parsing parameters), others
     * we hand to our client for processing */

    switch( action )
    {
    case vtparser_action::print:
    case vtparser_action::execute:
    case vtparser_action::hook:
    case vtparser_action::put:
    case vtparser_action::osc_start:
    case vtparser_action::osc_put:
    case vtparser_action::osc_end:
    case vtparser_action::unhook:
    case vtparser_action::csi_dispatch:
    case vtparser_action::esc_dispatch:
        Dispatch( framebuffer, action, ch );
        break;

    case vtparser_action::ignore:
        /* do nothing */
        break;

    case vtparser_action::collect:
    {
        /* Append the character to the intermediate params */
        if( num_intermediate_chars + 1 > MAX_INTERMEDIATE_CHARS )
            ignore_flagged = 1;
        else
            intermediate_chars[num_intermediate_chars++] = ch;

        break;
    }

    case vtparser_action::param:
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

    case vtparser_action::clear:
        num_intermediate_chars = 0;
        num_params             = 0;
        ignore_flagged         = 0;
        break;

    default:
        Dispatch( framebuffer, vtparser_action::none, 0 );
        break;
    }
}

void vtparser_t::do_state_change( framebuffer_t &framebuffer, vtparser_state new_state, vtparser_action action, char ch )
{
    /* A state change is an action and/or a new state to transition to. */

    if( new_state != vtparser_state::none )
    {
        /* Perform up to three actions:
         *   1. the exit action of the old state
         *   2. the action associated with the transition
         *   3. the entry action of the new state
         */

        vtparser_action exit_action  = _exitActions[(int)state];
        vtparser_action entry_action = _entryActions[(int)new_state];

        if( exit_action != vtparser_action::none )
            do_action( framebuffer, exit_action, 0 );

        if( action != vtparser_action::none )
            do_action( framebuffer, action, ch );

        if( entry_action != vtparser_action::none )
            do_action( framebuffer, entry_action, 0 );

        state = new_state;
    }
    else
    {
        do_action( framebuffer, action, ch );
    }
}

void vtparser_t::parse( framebuffer_t &framebuffer, unsigned char *data, int len )
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

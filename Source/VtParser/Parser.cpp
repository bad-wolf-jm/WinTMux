#include "Parser.h"
#include "States.h"

#include <cstdint>
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

void Vt100Parser::Dispatch( Action action, char ch )
{
    switch( action )
    {
    case Action::print:
        // std::cout << "Action::print" << " " << ch << std::endl;
        break;
    case Action::execute:
        std::cout << "Action::execute"  << " " << ch <<  std::endl;
        break;
    case Action::hook:
        std::cout << "Action::hook" << std::endl;
        break;
    case Action::put:
        std::cout << "Action::put" << std::endl;
        break;
    case Action::osc_start:
        std::cout << "Action::osc_start" << std::endl;
        break;
    case Action::osc_put:
        std::cout << "Action::osc_put" << std::endl;
        break;
    case Action::osc_end:
        std::cout << "Action::osc_end" << std::endl;
        break;
    case Action::unhook:
        std::cout << "Action::unhook" << std::endl;
        break;
    case Action::csi_dispatch:
        std::cout << "Action::csi_dispatch"  << " " << ch <<  std::endl;
        break;
    case Action::esc_dispatch:
        std::cout << "Action::esc_dispatch" << std::endl;
        break;
    case Action::none:
        std::cout << "Action::none" << std::endl;
        break;
    }
}

void Vt100Parser::do_action( Action action, char ch )
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
        // cb( action, ch );
        Dispatch( action, ch );
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
        Dispatch( Action::none, 0 );
        break;
    }
}

void Vt100Parser::do_state_change( VtParserState new_state, Action action, char ch )
{
    /* A state change is an action and/or a new state to transition to. */

    if( new_state != VtParserState::none )
    {
        /* Perform up to three actions:
         *   1. the exit action of the old state
         *   2. the action associated with the transition
         *   3. the entry action of the new state
         */

        Action exit_action  = _entryActions[(int)state];
        Action entry_action = _exitActions[(int)new_state];

        if( exit_action != Action::none )
            do_action( exit_action, 0 );

        if( action != Action::none )
            do_action( action, ch );

        if( entry_action != Action::none )
            do_action( entry_action, 0 );

        state = new_state;
    }
    else
    {
        do_action( action, ch );
    }
}

void Vt100Parser::vtparse( unsigned char *data, int len )
{
    int i;
    for( i = 0; i < len; i++ )
    {
        unsigned char      ch     = data[i];
        state_transition_t change = _stateTransitions[(uint8_t)state][ch];
        do_state_change( change.TransitionTo, change.Action, ch );
    }
}

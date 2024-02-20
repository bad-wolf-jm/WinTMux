#include "Parser.h"
#include "States.h"

#include <cstdint>

Vt100Parser::Vt100Parser()
{
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
    //  OnEvent( VtParserState::escape,  :on_entry , Action::clear);
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
    //}

    //$states[:ESCAPE_INTERMEDIATE] = {
    OnEvent( VtParserState::escape_intermediate, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::escape_intermediate, 0x19, Action::execute );
    OnEvent( VtParserState::escape_intermediate, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::escape_intermediate, Range{ 0x20, 0x2f }, Action::collect );
    OnEvent( VtParserState::escape_intermediate, 0x7f, Action::ignore );
    OnEvent( VtParserState::escape_intermediate, Range{ 0x30, 0x7e }, Action::esc_dispatch, VtParserState::ground );
    //}

    //$states[:CSI_ENTRY] = {
    //   OnEvent( VtParserState::csi_entry, :on_entry , Action::clear);
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
    //}

    //$states[:CSI_IGNORE] = {
    OnEvent( VtParserState::csi_ignore, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::csi_ignore, 0x19, Action::execute );
    OnEvent( VtParserState::csi_ignore, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::csi_ignore, Range{ 0x20, 0x3f }, Action::ignore );
    OnEvent( VtParserState::csi_ignore, 0x7f, Action::ignore );
    OnEvent( VtParserState::csi_ignore, Range{ 0x40, 0x7e }, VtParserState::ground );
    //}

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
    //}

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
    //   OnEvent( VtParserState::dcs_entry, :on_entry , Action::clear);
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
    //}

    //$states[:DCS_INTERMEDIATE] = {
    OnEvent( VtParserState::dcs_intermediate, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::dcs_intermediate, 0x19, Action::ignore );
    OnEvent( VtParserState::dcs_intermediate, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::dcs_intermediate, Range{ 0x20, 0x2f }, Action::collect );
    OnEvent( VtParserState::dcs_intermediate, 0x7f, Action::ignore );
    OnEvent( VtParserState::dcs_intermediate, Range{ 0x30, 0x3f }, VtParserState::dcs_ignore );
    OnEvent( VtParserState::dcs_intermediate, Range{ 0x40, 0x7e }, VtParserState::dcs_passthrough );
    //}

    //$states[:DCS_IGNORE] = {
    OnEvent( VtParserState::dcs_ignore, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::dcs_ignore, 0x19, Action::ignore );
    OnEvent( VtParserState::dcs_ignore, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::dcs_ignore, Range{ 0x20, 0x7f }, Action::ignore );
    //}

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
    //}

    //$states[:DCS_PASSTHROUGH] = {
    OnEntry( VtParserState::dcs_passthrough, Action::hook );
    OnExit( VtParserState::dcs_passthrough, Action::unhook );
    OnEvent( VtParserState::dcs_passthrough, Range{ 0x00, 0x17 }, Action::put );
    OnEvent( VtParserState::dcs_passthrough, 0x19, Action::put );
    OnEvent( VtParserState::dcs_passthrough, Range{ 0x1c, 0x1f }, Action::put );
    OnEvent( VtParserState::dcs_passthrough, Range{ 0x20, 0x7e }, Action::put );
    OnEvent( VtParserState::dcs_passthrough, 0x7f, Action::ignore );
    //}

    //$states[:SOS_PM_APC_STRING] = {
    OnEvent( VtParserState::sos_pm_apc_string, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::sos_pm_apc_string, 0x19, Action::ignore );
    OnEvent( VtParserState::sos_pm_apc_string, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::sos_pm_apc_string, Range{ 0x20, 0x7f }, Action::ignore );
    //}

    //$states[:OSC_STRING] = {
    OnEntry( VtParserState::osc_string, Action::osc_start );
    OnExit( VtParserState::osc_string, Action::osc_end );
    OnEvent( VtParserState::osc_string, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::osc_string, 0x19, Action::ignore );
    OnEvent( VtParserState::osc_string, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::osc_string, Range{ 0x20, 0x7f }, Action::osc_put );
    //}
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
    uint16_t transition                               = ( (uint8_t)action << 8 ) + ( (uint8_t)transitionTo );
    _stateTransitions[(uint8_t)transition][character] = transition;
}

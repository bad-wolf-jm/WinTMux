#include "StateMachine.h"
#include "VtParser/States.h"

Vt100StateMachine::Vt100StateMachine()
{
    // Anywhere transitions
    // clang-format off
    OnEvent( 0x18,                Action::execute, VtParserState::ground );
    OnEvent( 0x1a,                Action::execute, VtParserState::ground );
    OnEvent( Range{ 0x80, 0x8f }, Action::execute, VtParserState::ground );
    OnEvent( Range{ 0x91, 0x97 }, Action::execute, VtParserState::ground );
    OnEvent( 0x99,                Action::execute, VtParserState::ground );
    OnEvent( 0x9a,                Action::execute, VtParserState::ground );
    OnEvent( 0x9c,                                 VtParserState::ground );
    OnEvent( 0x1b,                                 VtParserState::escape );
    OnEvent( 0x98,                                 VtParserState::sos_pm_apc_string );
    OnEvent( 0x9e,                                 VtParserState::sos_pm_apc_string );
    OnEvent( 0x9f,                                 VtParserState::sos_pm_apc_string );
    OnEvent( 0x90,                                 VtParserState::dcs_entry );
    OnEvent( 0x9d,                                 VtParserState::osc_string );
    OnEvent( 0x9b,                                 VtParserState::csi_entry );
    // clang-format on

    // Transitions from ground state
    // clang-format off
    OnEvent( VtParserState::ground, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::ground, 0x19,                Action::execute );
    OnEvent( VtParserState::ground, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::ground, Range{ 0x20, 0x7f }, Action::print );
    // clang-format on

    //$states[:ESCAPE] = {
    //  OnEvent( VtParserState::escape,  :on_entry , Action::clear);
    // clang-format off
    OnEvent( VtParserState::escape, Range{ 0x00, 0x17 }, Action::execute );
    OnEvent( VtParserState::escape, 0x19,                Action::execute );
    OnEvent( VtParserState::escape, Range{ 0x1c, 0x1f }, Action::execute );
    OnEvent( VtParserState::escape, 0x7f,                Action::ignore );
    OnEvent( VtParserState::escape, Range{ 0x20, 0x2f }, Action::collect,      VtParserState::escape_intermediate );
    OnEvent( VtParserState::escape, Range{ 0x30, 0x4f }, Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, Range{ 0x51, 0x57 }, Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, 0x59,                Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, 0x5a,                Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, 0x5c,                Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, Range{ 0x60, 0x7e }, Action::esc_dispatch, VtParserState::ground );
    OnEvent( VtParserState::escape, 0x5b,                                      VtParserState::csi_entry );
    OnEvent( VtParserState::escape, 0x5d,                                      VtParserState::osc_string );
    OnEvent( VtParserState::escape, 0x50,                                      VtParserState::dcs_entry );
    OnEvent( VtParserState::escape, 0x58,                                      VtParserState::sos_pm_apc_string );
    OnEvent( VtParserState::escape, 0x5e,                                      VtParserState::sos_pm_apc_string );
    OnEvent( VtParserState::escape, 0x5f,                                      VtParserState::sos_pm_apc_string );
    // clang-format on
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
    //   OnEvent( VtParserState::dcs_passthrough, :on_entry , Action::hook);
    OnEvent( VtParserState::dcs_passthrough, Range{ 0x00, 0x17 }, Action::put );
    OnEvent( VtParserState::dcs_passthrough, 0x19, Action::put );
    OnEvent( VtParserState::dcs_passthrough, Range{ 0x1c, 0x1f }, Action::put );
    OnEvent( VtParserState::dcs_passthrough, Range{ 0x20, 0x7e }, Action::put );
    OnEvent( VtParserState::dcs_passthrough, 0x7f, Action::ignore );
    // OnEvent( VtParserState::dcs_passthrough, :on_exit   => :unhook
    //}

    //$states[:SOS_PM_APC_STRING] = {
    OnEvent( VtParserState::sos_pm_apc_string, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::sos_pm_apc_string, 0x19, Action::ignore );
    OnEvent( VtParserState::sos_pm_apc_string, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::sos_pm_apc_string, Range{ 0x20, 0x7f }, Action::ignore );
    //}

    //$states[:OSC_STRING] = {
    //  OnEvent( VtParserState::osc_string, :on_entry , Action::osc_start);
    OnEvent( VtParserState::osc_string, Range{ 0x00, 0x17 }, Action::ignore );
    OnEvent( VtParserState::osc_string, 0x19, Action::ignore );
    OnEvent( VtParserState::osc_string, Range{ 0x1c, 0x1f }, Action::ignore );
    OnEvent( VtParserState::osc_string, Range{ 0x20, 0x7f }, Action::osc_put );
    // OnEvent( VtParserState::osc_string, :on_exit   => :osc_end
    //}
}

void Vt100StateMachine::OnEvent( VtParserState state, Range range, Action action )
{
}

void Vt100StateMachine::OnEvent( VtParserState state, Range range, VtParserState transitionTo )
{
}

void Vt100StateMachine::OnEvent( VtParserState state, Range range, Action action, VtParserState transitionTo )
{
}

void Vt100StateMachine::OnEvent( VtParserState state, uint8_t character, Action action )
{
}

void Vt100StateMachine::OnEvent( VtParserState state, uint8_t character, VtParserState transitionTo )
{
}

void Vt100StateMachine::OnEvent( VtParserState state, uint8_t character, Action action, VtParserState transitionTo )
{
}

#include "StateMachine.h"

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

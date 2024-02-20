#pragma once

#include <cstdint>
#include <limits>

#include "Actions.h"
#include "States.h"

struct Range
{
    uint8_t Start;
    uint8_t End;
};

class Vt100Parser
{
  public:
    Vt100Parser();

  private:
    void OnEvent( Range range, Action action );
    void OnEvent( Range range, VtParserState transitionTo );
    void OnEvent( Range range, Action action, VtParserState transitionTo );

    void OnEvent( VtParserState state, Range range, Action action );
    void OnEvent( VtParserState state, Range range, VtParserState transitionTo );
    void OnEvent( VtParserState state, Range range, Action action, VtParserState transitionTo );

    void OnEvent( uint8_t character, Action action );
    void OnEvent( uint8_t character, VtParserState transitionTo );
    void OnEvent( uint8_t character, Action action, VtParserState transitionTo );

    void OnEvent( VtParserState state, uint8_t character, Action action );
    void OnEvent( VtParserState state, uint8_t character, VtParserState transitionTo );
    void OnEvent( VtParserState state, uint8_t character, Action action, VtParserState transitionTo );

    void OnEntry( VtParserState state, Action action );
    void OnExit( VtParserState state, Action action );

  private:
    uint16_t _stateTransitions[(size_t)VtParserState::count][std::numeric_limits<uint8_t>::max()];

    Action _entryActions[(size_t)VtParserState::count] = { Action::none };
    Action _exitActions[(size_t)VtParserState::count]  = { Action::none };
};

#pragma once

#include <cstdint>

#include "Actions.h"
#include "States.h"

struct Range
{
    uint8_t Start;
    uint8_t End;
};

class Vt100StateMachine
{
  public:
    Vt100StateMachine();
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
};
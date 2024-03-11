#pragma once

#include <cstdint>
#include <limits>

#include "Actions.h"
#include "States.h"
#include <Console/FrameBuffer.h>

struct Range
{
    uint8_t Start;
    uint8_t End;
};

struct state_transition_t
{
    VtParserState TransitionTo{ VtParserState::none };
    Action        Action{ Action::none };
};

constexpr int MAX_INTERMEDIATE_CHARS = 2;

class Vt100Parser
{
  public:
    Vt100Parser();

    void vtparse( framebuffer_t &framebuffer, unsigned char *data, int len );

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
    state_transition_t _stateTransitions[(size_t)VtParserState::count][std::numeric_limits<uint8_t>::max()];

    Action _entryActions[(size_t)VtParserState::count] = { Action::none };
    Action _exitActions[(size_t)VtParserState::count]  = { Action::none };
    void   do_action( framebuffer_t &framebuffer, Action action, char ch );
    void   do_state_change( framebuffer_t &framebuffer, VtParserState newState, Action action, char ch );

    VtParserState state;
    // vtparse_callback_t cb;
    unsigned char intermediate_chars[MAX_INTERMEDIATE_CHARS + 1];
    int           num_intermediate_chars;
    char          ignore_flagged;
    int           params[16];
    int           num_params;
    void         *user_data;

    void Dispatch( framebuffer_t &framebuffer, Action action, char ch );
    void ProcessGraphicsMode( framebuffer_t &freamebuffer );
    void Erase( framebuffer_t &freamebuffer );

  private:
    bool     _bold         = false;
    bool     _faint        = false;
    bool     _italic       = false;
    bool     _underline    = false;
    bool     _strikeout    = false;
    bool     _useDefaultFg = false;
    bool     _useDefaultBg = false;
    uint32_t _foregroundColor = 0;
    uint32_t _backgroundColor = 0;
};

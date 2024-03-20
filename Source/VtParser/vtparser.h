#pragma once

#include <array>
#include <cstdint>
#include <limits>

#include "Actions.h"
#include "Core/ringbuffer.h"
#include "States.h"
#include <Console/FrameBuffer.h>

struct Range
{
    uint8_t Start;
    uint8_t End;
};

struct state_transition_t
{
    vtparser_state  TransitionTo{ vtparser_state::none };
    vtparser_action Action{ vtparser_action::none };
};

constexpr int MAX_INTERMEDIATE_CHARS = 2;

class vtparser_t
{
  public:
    vtparser_t();

    void parse( framebuffer_t &framebuffer, unsigned char *data, int len );
    void parse( framebuffer_t &framebuffer, ringbuffer_t<uint8_t> &inputBuffer );
    void parse( framebuffer_t &framebuffer, std::vector<char> &inputBuffer, size_t bytesToProcess );

  private:
    void OnEvent( Range range, vtparser_action action );
    void OnEvent( Range range, vtparser_state transitionTo );
    void OnEvent( Range range, vtparser_action action, vtparser_state transitionTo );

    void OnEvent( vtparser_state state, Range range, vtparser_action action );
    void OnEvent( vtparser_state state, Range range, vtparser_state transitionTo );
    void OnEvent( vtparser_state state, Range range, vtparser_action action, vtparser_state transitionTo );

    void OnEvent( uint8_t character, vtparser_action action );
    void OnEvent( uint8_t character, vtparser_state transitionTo );
    void OnEvent( uint8_t character, vtparser_action action, vtparser_state transitionTo );

    void OnEvent( vtparser_state state, uint8_t character, vtparser_action action );
    void OnEvent( vtparser_state state, uint8_t character, vtparser_state transitionTo );
    void OnEvent( vtparser_state state, uint8_t character, vtparser_action action, vtparser_state transitionTo );

    void OnEntry( vtparser_state state, vtparser_action action );
    void OnExit( vtparser_state state, vtparser_action action );

  private:
    state_transition_t _stateTransitions[(size_t)vtparser_state::count][std::numeric_limits<uint8_t>::max()];

    vtparser_action _entryActions[(size_t)vtparser_state::count] = { vtparser_action::none };
    vtparser_action _exitActions[(size_t)vtparser_state::count]  = { vtparser_action::none };
    void            do_action( framebuffer_t &framebuffer, vtparser_action action, char ch );
    void            do_state_change( framebuffer_t &framebuffer, vtparser_state newState, vtparser_action action, char ch );

    vtparser_state state;
    // vtparse_callback_t cb;
    unsigned char intermediate_chars[MAX_INTERMEDIATE_CHARS + 1];
    int           num_intermediate_chars;
    char          ignore_flagged;
    int           params[16];
    int           num_params;
    void         *user_data;

    void dispatch_csi( char ch, framebuffer_t &framebuffer );
    void Dispatch( framebuffer_t &framebuffer, vtparser_action action, char ch );
    void ProcessGraphicsMode( framebuffer_t &freamebuffer );
    void Erase( framebuffer_t &freamebuffer );

  private:
    bool _bold         = false;
    bool _faint        = false;
    bool _italic       = false;
    bool _underline    = false;
    bool _strikeout    = false;
    bool _reversed     = false;
    bool _hidden       = false;
    bool _slowBlink    = false;
    bool _fastBlink    = false;
    bool _useDefaultFg = false;
    bool _useDefaultBg = false;

    std::array<bool, 9> _textAttributes = { 0 };

    uint32_t _foregroundColor = 0;
    uint32_t _backgroundColor = 0;
};

#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Minimax{
public:
  static Move get_move(State *state, int depth);
};

struct possible_state
{
  State* prev_state;
  Move taken_move;
  bool operator < (possible_state& rhs)
  {
    return this->prev_state->next_state(taken_move)->evaluate() < rhs.prev_state->next_state(rhs.taken_move)->evaluate();
  }
};
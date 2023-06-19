#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Alphabeta{
public:
  static Move get_move(State *state, int depth);
  static int mini(int lhs, int rhs);
  static int max(int lhs, int rhs);
  static int alphabeta(State* state, int alpha, int beta, int depth, bool maximizing);
};
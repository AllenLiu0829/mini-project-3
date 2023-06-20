#include <cstdlib>

#include "../state/state.hpp"
#include "./alphabeta.hpp"
#include "queue"
#include "vector"
#include "algorithm"
#include <iostream>

/**
 * @brief choose the maximum priority legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Alphabeta::get_move(State* state, int depth)
{
  int player_num = state->player;
  if(!state->legal_actions.size())
    state->get_legal_actions();
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  Move best_move;
  int max = -1000, possible_state_value;
  for(it = action.begin(); it != action.end(); it++)
  {
    possible_state_value = alphabeta(state->next_state(*it), 0, __INT_MAX__, depth, true, player_num);
    if(possible_state_value > max)
    {
      max = possible_state_value;
      best_move = *it;
    }
  }
  return best_move;
}

int Alphabeta::alphabeta(State* state, int alpha, int beta,int depth, bool maximizing, int side)
{
  if(depth == 0)
  {
    return state->evaluate(side);
  }
  state->get_legal_actions();
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  if(maximizing)
  {
    int value = -1000;
    for(it = action.begin(); it != action.end(); it++)
    {
      value = std::max(value, alphabeta(state->next_state(*it), alpha, beta, depth - 1, false, side));
      alpha = std::max(alpha, value);
      if(alpha >= beta) break;
    }
    return value;
  }
  else
  {
    int value = __INT_MAX__;
    for(it = action.begin(); it != action.end(); it++)
    {
      value = std::min(value, alphabeta(state->next_state(*it), alpha, beta, depth - 1, true, side));
      beta = std::min(value, beta);
      if(beta <= alpha) break;
    }
    return value;
  }
}
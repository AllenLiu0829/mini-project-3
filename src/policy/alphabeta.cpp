#include <cstdlib>

#include "../state/state.hpp"
#include "./alphabeta.hpp"
#include "queue"
#include "vector"
#include "algorithm"
#include <iostream>
#include <climits>

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
  Move best_move = action[(rand()+depth)%action.size()];
  int alpha = INT_MIN, beta = __INT_MAX__, max = INT_MIN, possible_state_value;
  for(it = action.begin(); it != action.end(); it++)
  {
    possible_state_value = alphabeta(state->next_state(*it), alpha, beta, depth, false, player_num);
    if(possible_state_value > max)
    {
      max = possible_state_value;
      best_move = *it;
    }
    alpha = std::max(alpha, possible_state_value);
  }
  return best_move;
}

int Alphabeta::alphabeta(State* state, int alpha, int beta,int depth, bool maximizing, int side)
{
  state->get_legal_actions();
  if(depth == 0 || state->legal_actions.size() == 0)
  {
    return state->evaluate(side);
  }
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  if(maximizing)
  {
    int value = INT_MIN;
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
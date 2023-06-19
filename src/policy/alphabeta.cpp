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
  if(!state->legal_actions.size())
    state->get_legal_actions();
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  Move best_move;
  int max = -1, possible_state_value;
  for(it = action.begin(); it != action.end(); it++)
  {
    possible_state_value = alphabeta(state, 0, __INT_MAX__, depth, true);
    if(possible_state_value > max)
    {
      max = possible_state_value;
      best_move = *it;
    }
  }
  return best_move;
}

int Alphabeta::max(int lhs, int rhs)
{
  return (lhs > rhs)? lhs : rhs;
}

int Alphabeta::mini(int lhs, int rhs)
{
  return (lhs < rhs)? lhs : rhs;
}

int Alphabeta::alphabeta(State* state, int alpha, int beta,int depth, bool maximizing)
{
  if(depth == 0)
  {
    return state->evaluate();
  }
  state->get_legal_actions();
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  if(maximizing)
  {
    int value = 0;
    for(it = action.begin(); it != action.end(); it++)
    {
      value = max(value, alphabeta(state->next_state(*it), alpha, beta, depth - 1, false));
      alpha = max(alpha, value);
      if(alpha > beta) break;
    }
    return value;
  }
  else
  {
    int value = __INT_MAX__;
    for(it = action.begin(); it != action.end(); it++)
    {
      value = mini(value, alphabeta(state->next_state(*it), alpha, beta, depth - 1, true));
      beta = mini(value, beta);
      if(beta > alpha) break;
    }
    return value;
  }
}
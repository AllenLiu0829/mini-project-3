#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"
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

Move Minimax::get_move(State* state, int depth)
{
  if(!state->legal_actions.size())
    state->get_legal_actions();
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  Move best_move;
  int max = -100, possible_state_value;
  for(it = action.begin(); it != action.end(); it++)
  {
    possible_state_value = minimax(state, depth, true);
    if(possible_state_value > max)
    {
      max = possible_state_value;
      best_move = *it;
    }
  }
  return best_move;
}

int Minimax::max(int lhs, int rhs)
{
  return (lhs > rhs)? lhs : rhs;
}

int Minimax::mini(int lhs, int rhs)
{
  return (lhs < rhs)? lhs : rhs;
}

int Minimax::minimax(State* state, int depth, bool maximizing)
{
  state->get_legal_actions();
  if(depth == 0 || state->legal_actions.size() == 0)
  {
    return state->evaluate();
  }
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  if(maximizing)
  {
    int value = 0;
    for(it = action.begin(); it != action.end(); it++)
    {
      value = max(value, minimax(state->next_state(*it), depth - 1, false));
    }
    return value;
  }
  else
  {
    int value = __INT_MAX__;
    for(it = action.begin(); it != action.end(); it++)
    {
      value = mini(value, minimax(state->next_state(*it), depth - 1, true));
    }
    return value;
  }
}
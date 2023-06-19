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
  state->get_legal_actions();
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  int max_evaluate = -1, possible_state_value;
  Move best_step = action[(rand()+depth)%action.size()];
  for(it = action.begin();it != action.end(); it++)
  {
    possible_state_value = max(state, depth + 3, *it);
    if(possible_state_value > max_evaluate)
    {
      max_evaluate = possible_state_value;
      best_step = *it;
    }
  }
  return best_step;
}

auto minicompare = [](int lhs, int rhs) {return lhs < rhs;};
auto maxcompare = [](int lhs, int rhs) {return lhs > rhs;};

int Minimax::mini(State* prev_state, int depth, Move move)
{
  State* state = prev_state->next_state(move);
  state->get_legal_actions();
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  std::priority_queue<int, std::vector<int>, decltype(minicompare)> possible_state_value;
  for(it = action.begin();it != action.end(); it++)
  {
    if(depth == 0) possible_state_value.push(state->next_state(*it)->evaluate());
    else possible_state_value.push(max(state, depth - 1, *it));
  }
  return possible_state_value.top();
}

int Minimax::max(State* prev_state, int depth, Move move)
{
  State* state = prev_state->next_state(move);
  state->get_legal_actions();
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  std::priority_queue<int, std::vector<int>, decltype(maxcompare)> possible_state_value;
  for(it = action.begin();it != action.end(); it++)
  {
    if(depth == 0) possible_state_value.push(state->next_state(*it)->evaluate());
    else possible_state_value.push(mini(state, depth - 1, *it));
  }
  return possible_state_value.top();
}
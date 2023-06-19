#include <cstdlib>

#include "../state/state.hpp"
#include "./alphabeta.hpp"

#include <vector>
#include <queue>
#include <utility>

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

class node
{
  int alpha = -1;
  int beta = __INT_MAX__;
  node* next = nullptr;
  node* prev = nullptr;
};
Move Alphabeta::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  return actions[(rand()+depth)%actions.size()];
}


auto mini_compare = [](int lhs, int rhs) {return lhs < rhs;};
auto max_compare = [](int lhs, int rhs) {return lhs > rhs;};

int Alphabeta::beta(State* prev_state, int depth, Move move)
{
  State* state = prev_state->next_state(move);
  state->get_legal_actions();
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  std::priority_queue<int, std::vector<int>, decltype(mini_compare)> possible_state_value;
  for(it = action.begin();it != action.end(); it++)
  {
    if(depth == 0) possible_state_value.push(state->next_state(*it)->evaluate());
    else possible_state_value.push(alpha(state, depth - 1, *it));
  }
  return possible_state_value.top();
}

int Alphabeta::alpha(State* prev_state, int depth, Move move)
{
  State* state = prev_state->next_state(move);
  state->get_legal_actions();
  std::vector<Move> action = state->legal_actions;
  std::vector<Move>::iterator it;
  std::priority_queue<int, std::vector<int>, decltype(max_compare)> possible_state_value;
  int alpha = 0;
  for(it = action.begin();it != action.end(); it++)
  {
    if(depth == 0) possible_state_value.push(state->next_state(*it)->evaluate());
    else possible_state_value.push(beta(state, depth - 1, *it));
  }
  return possible_state_value.top();
}
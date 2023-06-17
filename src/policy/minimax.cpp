#include <cstdlib>get_move

#include "../state/state.hpp"
#include "./minimax.hpp"
#include "queue"
#include "vector"

/**
 * @brief choose the maximum priority legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();

  std::vector<Move> action = state->legal_actions;
  std::priority_queue<possible_state> possible_result;
  std::vector<Move>::iterator it;
  for(it = action.begin(); it != action.end(); it++)
  {
    possible_result.emplace(state, *it);
  }
  return possible_result.top().taken_move;
}
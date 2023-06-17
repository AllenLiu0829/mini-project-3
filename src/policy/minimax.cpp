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

  //std::vector<Move> action = state->legal_actions;
  //std::priority_queue<possible_state> possible_result;
  //std::vector<Move>::iterator it;
  //for(it = action.begin(); it != action.end(); it++)
  //{
  //  possible_result.emplace(state, *it);
  //}
  //return possible_result.top().taken_move;

  std::vector<Move> action_1 = state->legal_actions;
  std::priority_queue<possible_state_max> possible_result_1;
  std::vector<Move>::iterator it_1;
  for(it_1 = action_1.begin(); it_1 != action_1.end(); it_1++)
  {
    State* new_state;
    std::vector<Move>::iterator it_2;
    std::priority_queue<possible_state_mini> possible_result_2;
    new_state = state->next_state(*it_1);
    new_state->get_legal_actions();
    std::vector<Move> action_2 = new_state->legal_actions;
    for(it_2 = action_2.begin(); it_2 != action_2.end(); it_2++)
    {
      possible_result_2.emplace(state, *it_2);
    }
    possible_result_1.emplace(possible_result_2.top().prev_state, possible_result_2.top().taken_move);
  }
  return possible_result_1.top().taken_move;
}
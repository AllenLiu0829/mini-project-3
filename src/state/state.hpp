#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include <cstdlib>
#include <vector>
#include <utility>

#include "../config.hpp"


typedef std::pair<size_t, size_t> Point;
typedef std::pair<Point, Point> Move;
class Board{
  public:
    char board[2][BOARD_H][BOARD_W] = {{
      //white
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1},
      {2, 3, 4, 5, 6},
    }, {
      //black
      {6, 5, 4, 3, 2},
      {1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
    }};
};

enum GameState {
  UNKNOWN = 0,
  WIN,
  DRAW,
  NONE
};


class State{
  public:
    //You may want to add more property for a state
    GameState game_state = UNKNOWN;
    Board board;
    int player = 0;
    std::vector<Move> legal_actions;
    int hold_pos[2][BOARD_H][BOARD_W];
    
    State(){};
    State(int player): player(player){};
    State(Board board): board(board){};
    State(Board board, int player): board(board), player(player){};
    
    int evaluate();

    // tools
    void hold_init();
    bool pass(int x, int y);

    int upward_hold(int x, int y, int side);
    int downward_hold(int x, int y, int side);
    int left_hold(int x, int y, int side);
    int right_hold(int x, int y, int side);
    int left_up_hold(int x, int y, int side);
    int right_up_hold(int x, int y, int side);
    int left_down_hold(int x, int y, int side);
    int right_down_hold(int x, int y, int side);

    //evaluates
    int pawn_evaluate(int x, int y, int side);
    int rook_evaluate(int x, int y, int side);
    int knight_evaluate(int x, int y, int side);
    int bishop_evaluate(int x, int y, int steps);
    int queen_evaluate(int x, int y, int steps);

    State* next_state(Move move);
    void get_legal_actions();
    std::string encode_output();
    std::string encode_state();
};

#endif
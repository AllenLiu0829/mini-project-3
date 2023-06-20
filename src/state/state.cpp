#include <iostream>
#include <sstream>
#include <cstdint>

#include "./state.hpp"
#include "../config.hpp"


/**
 * @brief evaluate the state
 * 
 * @return int 
 */

bool State::pass(int x, int y)
{
  return (this->board.board[0][x][y] == 0) && (this->board.board[1][x][y] == 0);
}

int State::upward_hold(int x, int y)
{
  int score = 0;
  for(int k=(x+1);k<BOARD_H;k++) // upward
  {
    if(!pass(k, y))
    {
      score += this->board.board[0][k][y] + this->board.board[1][k][y];
    }
  }
  return score;
}
int State::downward_hold(int x, int y)
{
  int score = 0;
  for(int k=(x-1);k>=0;k--) // doward
  {
    if(!pass(k, y))
    {
      score += this->board.board[0][k][y] + this->board.board[1][k][y];
    }
  }
  return score;
}
int State::right_hold(int x, int y)
{
  int score = 0;
  for(int k=(y+1);k<BOARD_W;k++)
  {
    if(!pass(x, k))
    {
      score += this->board.board[0][x][k] + this->board.board[1][x][k];
    }
  }
  return score;
}
int State::left_hold(int x, int y)
{
  int score = 0;
  for(int k=(y-1);k>=0;k--)
  {
    if(!pass(x, k))
    {
      score += this->board.board[0][x][k] + this->board.board[1][x][k];
    }
  }
  return score;
}
int State::left_up_hold(int x, int y)
{
  int score = 0;
  for(int k=(y-1), l=(x-1);k>=0, l>=0;k--, l--)
  {
    if(!pass(l, k))
    {
      score += this->board.board[0][l][k] + this->board.board[1][l][k];
    }
  }
  return score;
}
int State::right_up_hold(int x, int y)
{
  int score = 0;
  for(int k=(y+1), l=(x-1);k<BOARD_W, l>=0;k++, l--)
  {
    if(!pass(l, k))
    {
      score += this->board.board[0][l][k] + this->board.board[1][l][k];
    }
  }
  return score;  
}
int State::left_down_hold(int x, int y)
{
  int score = 0;
  for(int k=(y-1), l=(x+1);k>=0, l<BOARD_H;k--, l++)
  {
    if(!pass(l, k))
    {
      score += this->board.board[0][l][k] + this->board.board[1][l][k];
    }
  }
  return score;
}
int State::right_down_hold(int x, int y)
{
  int score = 0;
  for(int k=(y+1), l=(x+1);k<BOARD_W, l<BOARD_H;k++, l++)
  {
    if(!pass(l, k))
    {
      score += this->board.board[0][l][k] + this->board.board[1][l][k];
    }
  }
  return score;
}

int State::rook_evaluate(int x, int y)
{
  int score = 0;
  score += upward_hold(x, y);
  score += downward_hold(x, y);
  score += left_hold(x, y);
  score += right_hold(x, y);
  return score;
}
int State::bishop_evaluate(int x, int y)
{
  int score = 0;
  score += left_up_hold(x, y);
  score += right_up_hold(x, y);
  score += left_down_hold(x, y);
  score += right_down_hold(x, y);
  return score;
}
int State::queen_evaluate(int x, int y)
{
  int score = 0;
  score += upward_hold(x, y);
  score += downward_hold(x, y);
  score += left_hold(x, y);
  score += right_hold(x, y);
  score += left_up_hold(x, y);
  score += right_up_hold(x, y);
  score += left_down_hold(x, y);
  score += right_down_hold(x, y);
  return score;
}

int State::evaluate(){
  int side, stand[2];
  for(int i=0;i<BOARD_H;i++)
  {
    for(int j=0;j<BOARD_W;j++)
    {
      side = (this->board.board[0][i][j])? 0 : 1;
      switch(this->board.board[side][i][j])
      {
        case 1: // pawn
          stand[side] += pawn_score[side][i][j];
          break;
        case 2: // rook
          stand[side] += 5;
          stand[side] += rook_evaluate(i, j);
          break;
        case 3: // knight
          stand[side] += knight_score[side][i][j];
          break;
        case 4: // bishop
          stand[side] += 4;
          stand[side] += bishop_evaluate(i, j);
          break;
        case 5: // queen
          stand[side] += 9;
          stand[side] += queen_evaluate(i, j);
          break;
        case 6:
          stand[side] += king_score[side][i][j];
          break;
      }
    }
  }
  return stand[player] - stand[1-player];
}


/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}
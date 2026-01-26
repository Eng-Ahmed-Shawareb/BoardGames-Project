#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H

#include "BoardGame_Classes.h"

class MemoryGame_UI : public UI<char> {
public:
  MemoryGame_UI();

  ~MemoryGame_UI(){};

  Player<char> *create_player(string &name, char symbol, PlayerType type);

  Move<char> *get_move(Player<char> *player);

  void display_board_matrix(const vector<vector<char>> &matrix) const override;
};

#endif
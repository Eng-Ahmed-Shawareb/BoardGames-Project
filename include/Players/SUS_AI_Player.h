#ifndef SUS_AI_PLAYER_H
#define SUS_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "SUS_Board.h"

class SUS_AI_Player : public Player<char> {
private:
  int min_max(SUS_Board *current_board, bool is_max);

public:
  SUS_AI_Player(string name, char symbol);

  Move<char> *get_best_move();
};

#endif
#ifndef NUMERICAL_AI_PLAYER_H
#define NUMERCIAL_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "Numerical_Board.h"

class Numerical_AI_Player : public Player<int> {
private:
  int min_max(Numerical_Board *current_board, int depth, int alpha, int beta,
              bool is_max);

public:
  Numerical_AI_Player(string name, int symbol);

  Move<int> *get_best_move();
};

#endif
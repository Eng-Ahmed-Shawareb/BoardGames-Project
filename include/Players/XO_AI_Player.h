#ifndef XO_AI_PLAYER_H
#define XO_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "XO_Board.h"
#include <algorithm>

using namespace std;

class XO_AI_Player : public Player<char> {
private:
  int min_max(Board<char> *current_board, int depth, bool is_max);

public:
  XO_AI_Player(string name, char symbol);
  Move<char> *get_best_move();
};

#endif
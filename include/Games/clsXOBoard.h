#ifndef XO_BOARD_H
#define XO_BOARD_H

#include "BoardGame_Classes.h"

class clsXOBoard : public Board<char> {
private:
  char _blankSymbol = '.';

public:
  clsXOBoard();

  bool update_board(Move<char> *move);

  bool is_win(Player<char> *player);

  bool is_lose(Player<char> *player);

  bool is_draw(Player<char> *player);

  bool game_is_over(Player<char> *player);
};

#endif
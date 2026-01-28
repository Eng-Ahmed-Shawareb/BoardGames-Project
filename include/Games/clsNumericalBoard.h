#ifndef NUMERICAL_BOARD_H
#define NUMERICAL_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <set>

using namespace std;

class clsNumericalBoard : public Board<int> {

private:
  int _blankSymbol = 0;

public:
  clsNumericalBoard();

  set<int> sAvailableEvenNumbers;
  set<int> sAvailableOddNumbers;

  bool update_board(Move<int> *move) override;

  bool is_win(Player<int> *player) override;

  bool is_lose(Player<int> *player) override { return false; };

  bool is_draw(Player<int> *player) override;

  bool game_is_over(Player<int> *player) override;

  ~clsNumericalBoard(){};
};

#endif
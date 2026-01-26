#ifndef NUMERICAL_BOARD_H
#define NUMERICAL_BOARD_H

#include "BoardGame_Classes.h"
#include <set>
#include <iostream>

using namespace std;

class Numerical_Board : public Board<int> {

private:
  int Blank_Symbol = 0;

public:
  Numerical_Board();

  set<int> avaliable_even_numbers;
  set<int> avaliable_odd_numbers;

  bool update_board(Move<int> *move) override;

  bool is_win(Player<int> *player) override;

  bool is_lose(Player<int> *player) override { return false; };

  bool is_draw(Player<int> *player) override;

  bool game_is_over(Player<int> *player) override;

  ~Numerical_Board(){};
};

#endif
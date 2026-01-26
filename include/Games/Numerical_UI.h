#ifndef NUMERICAL_UI_H
#define NUMERICAL_UI_H

#include "BoardGame_Classes.h"
#include "Numerical_Board.h"
#include <iostream>
#include <set>

using namespace std;

class Numerical_UI : public UI<int> {
public:
  Numerical_UI();

  void print_available_numbers(Numerical_Board* current_board , int num_type);

  Player<int> *create_player(string &name, int symbol,
                             PlayerType type) override;

  Move<int> *get_move(Player<int> *player) override;

  Player<int> **setup_players() override;
};

#endif
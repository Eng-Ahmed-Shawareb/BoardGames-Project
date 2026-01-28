#ifndef NUMERICAL_UI_H
#define NUMERICAL_UI_H

#include "BoardGame_Classes.h"
#include "clsNumericalBoard.h"
#include <iostream>
#include <set>

using namespace std;

class clsNumericalUI : public UI<int> {
public:
  clsNumericalUI();

  void printAvailableNumbers(clsNumericalBoard *currentBoard, int numType);

  Player<int> *create_player(string &name, int symbol,
                             PlayerType type) override;

  Move<int> *get_move(Player<int> *player) override;

  Player<int> **setup_players() override;
};

#endif
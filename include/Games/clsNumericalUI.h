#ifndef NUMERICAL_UI_H
#define NUMERICAL_UI_H

#include "BoardGame_Classes.h"
#include "clsNumericalBoard.h"
#include <iostream>
#include <set>

using namespace std;

class clsNumericalUI : public clsUI<int> {
public:
  clsNumericalUI();

  void printAvailableNumbers(clsNumericalBoard *currentBoard, int numType);

  clsPlayer<int> *createPlayer(string &name, int symbol,
                               enPlayerType type) override;

  clsMove<int> *getMove(clsPlayer<int> *player) override;

  clsPlayer<int> **setupPlayers() override;
};

#endif
#ifndef NUMERICAL_BOARD_H
#define NUMERICAL_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <set>

using namespace std;

class clsNumericalBoard : public clsBoard<int> {

private:
  int _blankSymbol = 0;

public:
  clsNumericalBoard();

  set<int> sAvailableEvenNumbers;
  set<int> sAvailableOddNumbers;

  bool updateBoard(clsMove<int> *move) override;

  bool isWin(clsPlayer<int> *player) override;

  bool isLose(clsPlayer<int> *player) override { return false; };

  bool isDraw(clsPlayer<int> *player) override;

  bool gameIsOver(clsPlayer<int> *player) override;

  ~clsNumericalBoard(){};
};

#endif
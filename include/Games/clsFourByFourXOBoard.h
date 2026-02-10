#ifndef FOUR_BY_FOUR_BOARD_H
#define FOUR_BY_FOUR_BOARD_H

#include "BoardGame_Classes.h"

class clsFourByFourBoard : public clsBoard<char> {
private:
  char _blankSymbol = '.';

public:
  clsFourByFourBoard();

  bool updateBoard(clsMove<char> *move) override;

  bool isWin(clsPlayer<char> *player) override;

  bool isLose(clsPlayer<char> *player) override;

  bool isDraw(clsPlayer<char> *player) override;

  bool gameIsOver(clsPlayer<char> *player) override;
};

#endif
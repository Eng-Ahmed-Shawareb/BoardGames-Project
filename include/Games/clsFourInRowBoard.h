#ifndef FOUR_IN_ROW_BOARD_H
#define FOUR_IN_ROW_BOARD_H

#include "BoardGame_Classes.h"

class clsFourInRowBoard : public clsBoard<char> {
private:
  char _blankSymbol = '.';

public:
  clsFourInRowBoard();

  bool isValidMove(const int &y) const;

  bool updateBoard(clsMove<char> *move) override;

  bool isWin(clsPlayer<char> *player) override;

  bool isLose(clsPlayer<char> *player) override;

  bool isDraw(clsPlayer<char> *player) override;

  bool gameIsOver(clsPlayer<char> *player) override;
};

#endif
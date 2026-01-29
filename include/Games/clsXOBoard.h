#ifndef XO_BOARD_H
#define XO_BOARD_H

#include "BoardGame_Classes.h"

class clsXOBoard : public clsBoard<char> {
private:
  char _blankSymbol = '.';

public:
  clsXOBoard();

  bool updateBoard(clsMove<char> *move) override;

  bool isWin(clsPlayer<char> *player) override;

  bool isLose(clsPlayer<char> *player) override;

  bool isDraw(clsPlayer<char> *player) override;

  bool gameIsOver(clsPlayer<char> *player) override;
};

#endif
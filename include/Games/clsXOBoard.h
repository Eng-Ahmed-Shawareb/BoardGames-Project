#ifndef XO_BOARD_H
#define XO_BOARD_H

#include "BoardGame_Classes.h"

class clsXOBoard : public clsBoard<char> {
private:
  char _blankSymbol = '.';

public:
  clsXOBoard();

  bool updateBoard(clsMove<char> *move);

  bool isWin(clsPlayer<char> *player);

  bool isLose(clsPlayer<char> *player);

  bool isDraw(clsPlayer<char> *player);

  bool gameIsOver(clsPlayer<char> *player);
};

#endif
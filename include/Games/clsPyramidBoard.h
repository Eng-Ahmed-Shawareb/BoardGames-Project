#ifndef PYRAMID_BOARD_H
#define PYRAMID_BOARD_H

#include "BoardGame_Classes.h"

class clsPyramidBoard : public clsBoard<char> {
private:
  char _blankSymbol = '.';
  char _invalidSymbol = ' ';

  bool isValidPosition(int x, int y) const;

public:
  clsPyramidBoard();

  bool updateBoard(clsMove<char> *move) override;

  bool isWin(clsPlayer<char> *player) override;

  bool isLose(clsPlayer<char> *player) override;

  bool isDraw(clsPlayer<char> *player) override;

  bool gameIsOver(clsPlayer<char> *player) override;
};

#endif

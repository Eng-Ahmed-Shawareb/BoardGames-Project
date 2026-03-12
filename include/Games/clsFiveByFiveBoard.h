#ifndef FIVEBYFIVE_BOARD_H
#define FIVEBYFIVE_BOARD_H

#include "BoardGame_Classes.h"

class clsFiveByFiveBoard : public clsBoard<char> {
private:
  char _blankSymbol = '.';
  int count3InARow(char symbol);

public:
  clsFiveByFiveBoard();

  bool updateBoard(clsMove<char> *move) override;

  bool isWin(clsPlayer<char> *player) override;

  bool isLose(clsPlayer<char> *player) override;

  bool isDraw(clsPlayer<char> *player) override;

  bool gameIsOver(clsPlayer<char> *player) override;
};

#endif

#ifndef INFINITY_BOARD_H
#define INFINITY_BOARD_H

#include "BoardGame_Classes.h"
#include "vector"

class clsInfinityBoard : public clsBoard<char> {
private:
  char _blankSymbol = '.';
  
public:
  clsInfinityBoard();

  vector<vector<int>>vOrderOfMoves;

  bool updateBoard(clsMove<char> *move) override;

  bool isWin(clsPlayer<char> *player) override;

  bool isLose(clsPlayer<char> *player) override;

  bool isDraw(clsPlayer<char> *player) override;

  bool gameIsOver(clsPlayer<char> *player) override;
};

#endif
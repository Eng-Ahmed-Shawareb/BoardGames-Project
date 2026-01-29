#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include "BoardGame_Classes.h"

class clsSUSBoard : public clsBoard<char> {
private:
  char _blankSymbol = '.';
  vector<vector<int>> _vOrderOfMoves;

public:
  clsSUSBoard();

  pair<int, int> calculatePlayersScore();

  bool isValidMove(int x, int y);

  bool isWin(clsPlayer<char> *player) override;

  bool isLose(clsPlayer<char> *player) override;

  bool gameIsOver(clsPlayer<char> *player) override;

  bool isDraw(clsPlayer<char> *player) override;

  bool updateBoard(clsMove<char> *move) override;
};

#endif
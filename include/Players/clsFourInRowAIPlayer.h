#ifndef FOUR_IN_ROW_AI_PLAYER_H
#define FOUR_IN_ROW_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "clsFourInRowBoard.h"

class clsFourInRowAIPlayer : public clsPlayer<char> {
private:
  int _minMax(clsBoard<char> *currentBoard, bool isMax, int depth, int alpha,
              int beta) const;

public:
  clsFourInRowAIPlayer(string name, char symbol);

  clsMove<char> *getBestMove() const;
};

#endif
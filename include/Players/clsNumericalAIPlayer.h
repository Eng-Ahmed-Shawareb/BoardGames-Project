#ifndef NUMERICAL_AI_PLAYER_H
#define NUMERICAL_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "clsNumericalBoard.h"

class clsNumericalAIPlayer : public clsPlayer<int> {
private:
  int _minMax(clsNumericalBoard *currentBoard, int depth, int alpha, int beta,
              bool isMax) const;

public:
  clsNumericalAIPlayer(string name, int symbol);

  clsMove<int> *getBestMove() const;
};

#endif
#ifndef FOUR_BY_FOUR_AI_PLAYER_H
#define FOUR_BY_FOUR_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "clsFourByFourXOBoard.h"

class clsFourByFourAIPlayer : public clsPlayer<char>{
private:
  int _minMax(clsBoard<char> *currentBoard, bool isMax, int depth, int alpha,
              int beta) const;

public:
  clsFourByFourAIPlayer(string name, char symbol);

  clsMove<char> *getBestMove() const;
};

#endif
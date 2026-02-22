#ifndef PYRAMID_AI_PLAYER_H
#define PYRAMID_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "clsPyramidBoard.h"
#include <algorithm>

using namespace std;

class clsPyramidAIPlayer : public clsPlayer<char> {
private:
  int _minMax(clsBoard<char> *currentBoard, int depth, bool isMax, int alpha, int beta) const;

public:
  clsPyramidAIPlayer(string name, char symbol);
  clsMove<char> *getBestMove() const;
};

#endif

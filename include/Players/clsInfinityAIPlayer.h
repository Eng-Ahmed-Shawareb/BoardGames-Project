#ifndef INFINITY_AI_PLAYER_H
#define INFINITY_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "clsInfinityBoard.h"
#include <algorithm>

using namespace std;

class clsInfinityAIPlayer : public clsPlayer<char> {
private:
  int _minMax(clsBoard<char> *currentBoard, int depth, bool isMax , int alpha , int beta) const;

public:
  clsInfinityAIPlayer(string name, char symbol);
  clsMove<char> *getBestMove() const;
};

#endif
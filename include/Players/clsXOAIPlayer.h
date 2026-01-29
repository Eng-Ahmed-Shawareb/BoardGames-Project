#ifndef XO_AI_PLAYER_H
#define XO_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "clsXOBoard.h"
#include <algorithm>

using namespace std;

class clsXOAIPlayer : public clsPlayer<char> {
private:
  int _minMax(clsBoard<char> *currentBoard, int depth, bool isMax) const;

public:
  clsXOAIPlayer(string name, char symbol);
  clsMove<char> *getBestMove() const;
};

#endif
#ifndef MISERE_AI_PLAYER_H
#define MISERE_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "clsMisereBoard.h"
#include <algorithm>

using namespace std;

class clsMisereAIPlayer : public clsPlayer<char> {
private:
  int _minMax(clsBoard<char> *currentBoard, int depth, bool isMax) const;

public:
  clsMisereAIPlayer(string name, char symbol);
  clsMove<char> *getBestMove() const;
};

#endif
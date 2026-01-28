#ifndef XO_AI_PLAYER_H
#define XO_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "clsXOBoard.h"
#include <algorithm>

using namespace std;

class clsXOAIPlayer : public Player<char> {
private:
  int _minMax(Board<char> *currentBoard, int depth, bool isMax);

public:
  clsXOAIPlayer(string name, char symbol);
  Move<char> *getBestMove();
};

#endif
#ifndef WORDGAME_AIPLAYER_H
#define WORDGAME_AIPLAYER_H

#include "BoardGame_Classes.h"
#include <algorithm>
using namespace std;

class clsWordGameAIPlayer : public clsPlayer<char> {
private:
  int _minMax(clsBoard<char> *currentBoard, bool isMax, int depth, int alpha,
              int beta) const;

public:
  clsWordGameAIPlayer(string name, char symbol);
  clsMove<char> *getBestMove() const;
};

#endif

#ifndef FIVEBYFIVE_AI_PLAYER_H
#define FIVEBYFIVE_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "clsFiveByFiveBoard.h"
#include <algorithm>

using namespace std;

class clsFiveByFiveAIPlayer : public clsPlayer<char> {
private:
  int _minMax(clsBoard<char> *currentBoard, bool isMax, int depth, int alpha, int beta) const;
  int evaluateBoard(clsBoard<char> *currentBoard) const;

public:
  clsFiveByFiveAIPlayer(string name, char symbol);
  clsMove<char> *getBestMove() const;
};

#endif

#ifndef SUS_AI_PLAYER_H
#define SUS_AI_PLAYER_H

#include "BoardGame_Classes.h"
#include "clsSUSBoard.h"

class clsSUSAIPlayer : public clsPlayer<char> {
private:
  int _minMax(clsSUSBoard *currentBoard, bool isMax);

public:
  clsSUSAIPlayer(string name, char symbol);

  clsMove<char> *getBestMove();
};

#endif
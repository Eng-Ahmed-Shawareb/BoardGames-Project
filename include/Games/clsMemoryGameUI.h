#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H

#include "BoardGame_Classes.h"

class clsMemoryGameUI : public clsUI<char> {
public:
  clsMemoryGameUI();

  ~clsMemoryGameUI(){};

  clsPlayer<char> *createPlayer(string &name, char symbol, enPlayerType type);

  clsMove<char> *getMove(clsPlayer<char> *player);

  void displayBoardMatrix(const vector<vector<char>> &matrix) const override;
};

#endif
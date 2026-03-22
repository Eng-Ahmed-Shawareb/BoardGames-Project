#ifndef PYRAMID_UI_H
#define PYRAMID_UI_H

#include "BoardGame_Classes.h"

class clsPyramidUI : public clsUI<char> {
public:
  clsPyramidUI();

  ~clsPyramidUI(){};

  clsPlayer<char> *createPlayer(string &name, char symbol,
                                enPlayerType type) override;

  clsMove<char> *getMove(clsPlayer<char> *player) override;

  clsPlayer<char> **setupPlayers() override;

  void displayBoardMatrix(const vector<vector<char>> &matrix) const override;
};

#endif

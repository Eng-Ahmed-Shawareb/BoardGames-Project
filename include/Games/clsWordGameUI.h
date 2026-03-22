#ifndef WORDGAME_UI_H
#define WORDGAME_UI_H

#include "BoardGame_Classes.h"
#include <string>
using namespace std;

class clsWordGameUI : public clsUI<char> {
public:
  clsWordGameUI();

  ~clsWordGameUI(){};

  clsPlayer<char> **setupPlayers() override;

  clsPlayer<char> *createPlayer(string &name, char symbol,
                                enPlayerType type) override;

  clsMove<char> *getMove(clsPlayer<char> *player) override;

  void displayBoardMatrix(const vector<vector<char>> &matrix) const override;
};

#endif

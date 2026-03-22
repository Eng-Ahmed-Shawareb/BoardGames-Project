#ifndef SUS_UI_H
#define SUS_UI_H

#include "BoardGame_Classes.h"
#include "clsSUSBoard.h"

class clsSUSUI : public clsUI<char> {
public:
  clsSUSUI();

  clsMove<char> *getMove(clsPlayer<char> *player) override;

  clsPlayer<char> *createPlayer(string &name, char symbol,
                                enPlayerType type) override;

  clsPlayer<char> **setupPlayers() override;

  void displayBoardMatrix(const vector<vector<char>> &matrix) const override;
};

#endif
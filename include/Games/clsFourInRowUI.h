#ifndef FOUR_IN_ROW_UI_H
#define FOUR_IN_ROW_UI_H

#include "BoardGame_Classes.h"

class clsFourInRowUI : public clsUI<char> {
public:
  clsFourInRowUI();

  clsMove<char> *getMove(clsPlayer<char> *player) override;

  clsPlayer<char> *createPlayer(string &name, char symbol,
                                enPlayerType type) override;

  clsPlayer<char> **setupPlayers() override;
};

#endif
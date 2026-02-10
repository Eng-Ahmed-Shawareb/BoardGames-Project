#ifndef FOUR_BY_FOUR_UI_H
#define FOUR_BY_FOUR_UI_H

#include "BoardGame_Classes.h"

class clsFourByFourUI : public clsUI<char> {
public:
  clsFourByFourUI();

  static bool validDirection(const int &x, const int &y, const char &symbol,
                       clsBoard<char> *currentBoard);

  clsMove<char> *getMove(clsPlayer<char> *player) override;

  clsPlayer<char> *createPlayer(string &name, char symbol,
                                enPlayerType type) override;

  clsPlayer<char> **setupPlayers() override;
};

#endif
#ifndef MISERE_UI_H
#define MISERE_UI_H

#include "BoardGame_Classes.h"

class clsMisereUI : public clsUI<char> {
public:
  clsMisereUI();

  clsPlayer<char> *createPlayer(string &name, char symbol,
                                enPlayerType type) override;

  clsMove<char> *getMove(clsPlayer<char> *player) override;
};
#endif
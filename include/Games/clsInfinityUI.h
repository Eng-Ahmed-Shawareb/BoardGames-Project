#ifndef INFINITY_UI_H
#define INFINITY_UI_H

#include "BoardGame_Classes.h"

class clsInfinityUI : public clsUI<char> {
public:
  clsInfinityUI();

  ~clsInfinityUI(){};

  clsPlayer<char> *createPlayer(string &name, char symbol,
                                enPlayerType type) override;

  clsMove<char> *getMove(clsPlayer<char> *player) override;
};

#endif
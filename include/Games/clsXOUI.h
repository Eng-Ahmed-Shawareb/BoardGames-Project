#ifndef XO_UI_H
#define XO_UI_H

#include "BoardGame_Classes.h"

class clsXOUI : public clsUI<char> {
public:
  clsXOUI();

  ~clsXOUI(){};

  clsPlayer<char> *createPlayer(string &name, char symbol,
                                enPlayerType type) override;

  clsMove<char> *getMove(clsPlayer<char> *player) override;

  void displayBoardMatrix(const vector<vector<char>> &matrix) const override;
};

#endif
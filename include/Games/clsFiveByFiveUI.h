#ifndef FIVEBYFIVE_UI_H
#define FIVEBYFIVE_UI_H

#include "BoardGame_Classes.h"

class clsFiveByFiveUI : public clsUI<char> {
public:
  clsFiveByFiveUI();

  ~clsFiveByFiveUI() {};

  clsPlayer<char> *createPlayer(string &name, char symbol,
                                enPlayerType type) override;

  clsMove<char> *getMove(clsPlayer<char> *player) override;

  void displayBoardMatrix(const vector<vector<char>> &matrix) const override;
};

#endif

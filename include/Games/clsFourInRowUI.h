#ifndef FOUR_IN_ROW_UI_H
#define FOUR_IN_ROW_UI_H

#include "BoardGame_Classes.h"

class clsFourInRowUI : public UI<char> {
public:
  clsFourInRowUI();

  Move<char> *get_move(Player<char> *player) override;

  Player<char> *create_player(string &name, char symbol,
                              PlayerType type) override;

  Player<char> **setup_players() override;
};

#endif
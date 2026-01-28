#ifndef SUS_UI_H
#define SUS_UI_H

#include "BoardGame_Classes.h"
#include "clsSUSBoard.h"
class clsSUSUI : public UI<char> {
public:
  clsSUSUI();

  Move<char> *get_move(Player<char> *player) override;

  Player<char> *create_player(string &name, char symbol,
                              PlayerType type) override;

  Player<char> **setup_players() override;
};

#endif
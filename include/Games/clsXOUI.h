#ifndef XO_UI_H
#define XO_UI_H

#include "BoardGame_Classes.h"

class clsXOUI : public UI<char> {
public:
  clsXOUI();

  ~clsXOUI(){};

  Player<char> *create_player(string &name, char symbol, PlayerType type);

  Move<char> *get_move(Player<char> *player);
};

#endif
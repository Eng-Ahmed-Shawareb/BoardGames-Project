#include "XO_UI.h"
#include "BoardGame_Classes.h"
#include "XO_AI_Player.h"
#include "XO_Board.h"
#include <algorithm>
#include <iostream>
#include <vector>

XO_UI::XO_UI() : UI<char>("Weclome to FCAI X-O Game by Dr El-Ramly", 3) {}

Player<char> *XO_UI::create_player(string &name, char symbol, PlayerType type) {
  cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer");
  if (type == PlayerType::COMPUTER) {
    return new XO_AI_Player(name, symbol);
  }
  return new Player<char>(name, symbol, type);
}

Move<char> *XO_UI::get_move(Player<char> *player) {
  int x, y;

  if (player->get_type() == PlayerType::HUMAN) {
    cout << "\nPlease enter your move x and y (0 to 2): ";
    cin >> x >> y;
  } else if (player->get_type() == PlayerType::COMPUTER) {
    XO_AI_Player *AI_Player = dynamic_cast<XO_AI_Player *>(player);
    if (AI_Player) {
      return AI_Player->get_best_move();
    }
  }
  return new Move<char>(x, y, player->get_symbol());
}

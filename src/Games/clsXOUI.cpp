#include "clsXOUI.h"
#include "BoardGame_Classes.h"
#include "clsXOAIPlayer.h"
#include "clsXOBoard.h"
#include <algorithm>
#include <iostream>
#include <vector>

clsXOUI::clsXOUI() : UI<char>("Weclome to FCAI X-O Game by Dr El-Ramly", 3) {}

Player<char> *clsXOUI::create_player(string &name, char symbol,
                                     PlayerType type) {
  cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer");
  if (type == PlayerType::COMPUTER) {
    return new clsXOAIPlayer(name, symbol);
  }
  return new Player<char>(name, symbol, type);
}

Move<char> *clsXOUI::get_move(Player<char> *player) {
  int x, y;

  if (player->get_type() == PlayerType::HUMAN) {
    cout << "\nPlease enter your move x and y (0 to 2): ";
    cin >> x >> y;
  } else if (player->get_type() == PlayerType::COMPUTER) {
    clsXOAIPlayer *AI_Player = dynamic_cast<clsXOAIPlayer *>(player);
    if (AI_Player) {
      return AI_Player->getBestMove();
    }
  }
  return new Move<char>(x, y, player->get_symbol());
}

#include "clsXOUI.h"
#include "BoardGame_Classes.h"
#include "clsXOAIPlayer.h"
#include "clsXOBoard.h"
#include "clsInputValidate.h"
#include <algorithm>
#include <iostream>
#include <vector>

clsXOUI::clsXOUI()
    : clsUI<char>("Weclome to FCAI X-O Game by Dr El-Ramly", 3) {}

clsPlayer<char> *clsXOUI::createPlayer(string &name, char symbol,
                                       enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "computer")
       << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsXOAIPlayer(name, symbol);
  }
  return new clsPlayer<char>(name, symbol, type);
}

clsMove<char> *clsXOUI::getMove(clsPlayer<char> *player) {
  int x, y;

  if (player->getType() == enPlayerType::HUMAN) {
    cout << "Please enter your move x and y (0 to 2): ";
    while ((!clsInputValidate::validIntegerInRange(x, 0, 2)) ||
           (!clsInputValidate::validIntegerInRange(y, 0, 2))) {
      cout << endl
           << "Invalid input , Please enter your move x and y (0 to 2): ";
    }
  } else if (player->getType() == enPlayerType::COMPUTER) {
    clsXOAIPlayer *AI_Player = dynamic_cast<clsXOAIPlayer *>(player);
    if (AI_Player) {
      return AI_Player->getBestMove();
    }
  }
  return new clsMove<char>(x, y, player->getSymbol());
}

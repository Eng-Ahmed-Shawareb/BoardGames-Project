#include "clsXOUI.h"
#include "BoardGame_Classes.h"
#include "clsInputValidate.h"
#include "clsMisereAIPlayer.h"
#include "clsMisereUI.h"
#include <algorithm>
#include <iostream>
#include <vector>

clsMisereUI::clsMisereUI() : clsUI<char>("Welcome to my Misère game!", 3) {}

clsPlayer<char> *clsMisereUI::createPlayer(string &name, char symbol,
                                       enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "computer")
       << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsMisereAIPlayer(name, symbol);
  }
  return new clsPlayer<char>(name, symbol, type);
}

clsMove<char> *clsMisereUI::getMove(clsPlayer<char> *player) {
  int x, y;

  if (player->getType() == enPlayerType::HUMAN) {
    cout << "Please enter your move x and y (0 to 2): ";
    while ((!clsInputValidate::validIntegerInRange(x, 0, 2)) ||
           (!clsInputValidate::validIntegerInRange(y, 0, 2))) {
      cout << endl
           << "Invalid input , Please enter your move x and y (0 to 2): ";
    }
  } else if (player->getType() == enPlayerType::COMPUTER) {
    clsMisereAIPlayer *AI_Player = dynamic_cast<clsMisereAIPlayer *>(player);
    if (AI_Player) {
      return AI_Player->getBestMove();
    }
  }
  return new clsMove<char>(x, y, player->getSymbol());
}

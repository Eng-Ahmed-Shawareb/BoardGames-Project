#include "clsInfinityUI.h"
#include "BoardGame_Classes.h"
#include "clsInputValidate.h"
#include "clsInfinityAIPlayer.h"
#include "clsInfinityBoard.h"
#include <algorithm>
#include <iostream>
#include <vector>

clsInfinityUI::clsInfinityUI() : clsUI<char>("Welcome to my Infinity XO game!", 3) {}

clsPlayer<char> *clsInfinityUI::createPlayer(string &name, char symbol,
                                       enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "computer")
       << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsInfinityAIPlayer(name, symbol);
  }
  return new clsPlayer<char>(name, symbol, type);
}

clsMove<char> *clsInfinityUI::getMove(clsPlayer<char> *player) {
  int x, y;

  if (player->getType() == enPlayerType::HUMAN) {
    cout << "Please enter your move x and y (0 to 2): ";
    while ((!clsInputValidate::validIntegerInRange(x, 0, 2)) ||
           (!clsInputValidate::validIntegerInRange(y, 0, 2))) {
      cout << endl
           << "Invalid input , Please enter your move x and y (0 to 2): ";
    }
  } else if (player->getType() == enPlayerType::COMPUTER) {
    clsInfinityAIPlayer *AI_Player = dynamic_cast<clsInfinityAIPlayer *>(player);
    if (AI_Player) {
      return AI_Player->getBestMove();
    }
  }
  return new clsMove<char>(x, y, player->getSymbol());
}

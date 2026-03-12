#include "clsFiveByFiveUI.h"
#include "BoardGame_Classes.h"
#include "clsInputValidate.h"
#include "clsFiveByFiveBoard.h"
#include "clsFiveByFiveAIPlayer.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>

clsFiveByFiveUI::clsFiveByFiveUI() : clsUI<char>("Welcome to my 5x5 Tic-Tac-Toe game!", 3) {}

clsPlayer<char> *clsFiveByFiveUI::createPlayer(string &name, char symbol,
                                       enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "computer")
       << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsFiveByFiveAIPlayer(name, symbol);
  }
  return new clsPlayer<char>(name, symbol, type);
}

clsMove<char> *clsFiveByFiveUI::getMove(clsPlayer<char> *player) {
  int x, y;

  if (player->getType() == enPlayerType::HUMAN) {
    cout << "Please enter your move x and y (0 to 4): ";
    while ((!clsInputValidate::validIntegerInRange(x, 0, 4)) ||
           (!clsInputValidate::validIntegerInRange(y, 0, 4))) {
      cout << endl
           << "Invalid input , Please enter your move x and y (0 to 4): ";
    }
  } else if (player->getType() == enPlayerType::COMPUTER) {
    clsFiveByFiveAIPlayer *AI_Player = dynamic_cast<clsFiveByFiveAIPlayer *>(player);
    if (AI_Player) {
      return AI_Player->getBestMove();
    }
  }
  return new clsMove<char>(x, y, player->getSymbol());
}

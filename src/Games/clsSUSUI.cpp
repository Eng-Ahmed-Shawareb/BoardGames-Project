#include "clsSUSUI.h"
#include "BoardGame_Classes.h"
#include "clsSUSAIPlayer.h"
#include "clsSUSBoard.h"
#include "clsInputValidate.h"
#include <iostream>
#include <vector>

clsSUSUI::clsSUSUI() : clsUI("Welcome to my SUS game!", 3){};

clsMove<char> *clsSUSUI::getMove(clsPlayer<char> *player) {
  int x;
  int y;
  char symbol = player->getSymbol();

  if (player->getType() == enPlayerType::HUMAN) {

    cout << "Please enter your move x and y (0 to 2): ";
    while ((!clsInputValidate::validIntegerInRange(x, 0, 2)) ||
           (!clsInputValidate::validIntegerInRange(y, 0, 2))) {
      cout << endl
           << "Invalid input , Please enter your move x and y (0 to 2): ";
    }

  }

  else if (player->getType() == enPlayerType::COMPUTER) {

    clsSUSAIPlayer *AIPlayer = dynamic_cast<clsSUSAIPlayer *>(player);
    if (AIPlayer) {
      return AIPlayer->getBestMove();
    }
  }

  return new clsMove<char>(x, y, symbol);
}

clsPlayer<char> *clsSUSUI::createPlayer(string &name, char symbol,
                                        enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "Human" : "Computer")
       << " player : " << name << " (" << symbol << ")" << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsSUSAIPlayer(name, symbol);
  }
  return new clsPlayer(name, symbol, type);
}

clsPlayer<char> **clsSUSUI::setupPlayers() {
  clsPlayer<char> **players = new clsPlayer<char> *[2];
  vector<string> vTypeOptions = {"Human", "Computer"};

  string nameS = getPlayerName("Player S");
  enPlayerType typeS = getPlayerTypeChoice("Player S", vTypeOptions);
  players[0] = createPlayer(nameS, 'S', typeS);

  string nameU = getPlayerName("Player U");
  enPlayerType typeU = getPlayerTypeChoice("Player U", vTypeOptions);
  players[1] = createPlayer(nameU, 'U', typeU);

  return players;
}
#include "clsFourInRowUI.h"
#include "BoardGame_Classes.h"
#include "clsFourInRowAIPlayer.h"
#include "clsFourInRowBoard.h"
#include "clsInputValidate.h"
#include <iostream>

using namespace std;

clsFourInRowUI::clsFourInRowUI()
    : clsUI("Welcome to my Four In Row game!", 3){};

clsMove<char> *clsFourInRowUI::getMove(clsPlayer<char> *player) {
  int x = 0;
  int y;
  char symbol = player->getSymbol();
  if (player->getType() == enPlayerType::HUMAN) {
    cout << "Please enter your move column [0 to 6] : ";
    while (!clsInputValidate::validIntegerInRange(y, 0, 6)) {
      cout << endl
           << "Invalid input , Please enter your move column [0 to 6] : ";
    }
  } else if (player->getType() == enPlayerType::COMPUTER) {
    clsFourInRowAIPlayer *AIPlayer =
        dynamic_cast<clsFourInRowAIPlayer *>(player);
    if (AIPlayer) {
      return AIPlayer->getBestMove();
    }
  }
  return new clsMove<char>(x, y, symbol);
}

clsPlayer<char> *clsFourInRowUI::createPlayer(string &name, char symbol,
                                              enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "Human" : "Computer")
       << " player : " << name << " (" << symbol << ")" << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsFourInRowAIPlayer(name, symbol);
  }
  return new clsPlayer(name, symbol, type);
}

clsPlayer<char> **clsFourInRowUI::setupPlayers() {
  clsPlayer<char> **players = new clsPlayer<char> *[2];
  vector<string> vTypeOptions = {"Human", "Computer"};

  string nameX = getPlayerName("Player X");
  enPlayerType typeX = getPlayerTypeChoice("Player X", vTypeOptions);
  players[0] = createPlayer(nameX, static_cast<char>('X'), typeX);

  string nameO = getPlayerName("Player O");
  enPlayerType typeO = getPlayerTypeChoice("Player O", vTypeOptions);
  players[1] = createPlayer(nameO, static_cast<char>('O'), typeO);

  return players;
}
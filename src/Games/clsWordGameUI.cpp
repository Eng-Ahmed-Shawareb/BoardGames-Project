#include "clsWordGameUI.h"
#include "clsInputValidate.h"
#include "clsWordGameAIPlayer.h"
#include <iostream>
#include <string>
using namespace std;

clsWordGameUI::clsWordGameUI() : clsUI<char>(3) {}

clsPlayer<char> **clsWordGameUI::setupPlayers() {
  clsPlayer<char> **players = new clsPlayer<char> *[2];
  vector<string> typeOptions = {"Human", "Computer"};

  string name1 = getPlayerName("Player 1");
  enPlayerType type1 = getPlayerTypeChoice("Player 1", typeOptions);
  players[0] = createPlayer(name1, '1', type1); // '1' is placeholder

  string name2 = getPlayerName("Player 2");
  enPlayerType type2 = getPlayerTypeChoice("Player 2", typeOptions);
  players[1] = createPlayer(name2, '2', type2); // '2' is placeholder

  return players;
}

clsPlayer<char> *clsWordGameUI::createPlayer(string &name, char symbol,
                                             enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "computer")
       << " player: " << name << "\n";
  if (type == enPlayerType::COMPUTER) {
    return new clsWordGameAIPlayer(name, symbol);
  }
  return new clsPlayer<char>(name, symbol, type);
}

clsMove<char> *clsWordGameUI::getMove(clsPlayer<char> *player) {
  int x, y;
  char letter;

  if (player->getType() == enPlayerType::HUMAN) {
    cout << "\n" << player->getName() << ", please enter your move:\n";
    cout << "Enter row and column numbers separated by space: ";

    while ((!clsInputValidate::validIntegerInRange(x, 0, 2)) ||
           (!clsInputValidate::validIntegerInRange(y, 0, 2))) {
      cout << endl
           << "Invalid input , Please enter your move x and y (0 to 2): ";
    }

    cout << "Enter the letter you want to place: ";
    while (!(cin >> letter) || !isalpha(letter)) {
      cout << "Invalid! Please enter a single alphabetic letter: ";
      cin.clear();
      cin.ignore(10000, '\n');
    }
  } else {
    clsWordGameAIPlayer *AIPlayer = dynamic_cast<clsWordGameAIPlayer *>(player);
    if (AIPlayer) {
      return AIPlayer->getBestMove();
    }
  }

  return new clsMove<char>(x, y, toupper(letter));
}

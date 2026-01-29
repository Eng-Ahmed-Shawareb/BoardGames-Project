#include "clsNumericalUI.h"
#include "clsInputValidate.h"
#include "clsNumericalAIPlayer.h"
#include <iostream>
#include <vector>
using namespace std;

clsNumericalUI::clsNumericalUI()
    : clsUI<int>("Welcome to my Numerical game!", 3){};

void clsNumericalUI::printAvailableNumbers(clsNumericalBoard *currentBoard,
                                           const int &numType) const {
  if (numType % 2) {
    cout << "[ ";
    for (auto it = currentBoard->sAvailableOddNumbers.begin();
         it != currentBoard->sAvailableOddNumbers.end(); ++it) {
      cout << *it << " ";
    }
    cout << "]";

  } else {
    cout << "[ ";
    for (auto it = currentBoard->sAvailableEvenNumbers.begin();
         it != currentBoard->sAvailableEvenNumbers.end(); ++it) {
      cout << *it << " ";
    }
    cout << "]";
  }
}

clsPlayer<int> *clsNumericalUI::createPlayer(string &name, int symbol,
                                             enPlayerType type) {
  string numType = (symbol == 1) ? "Odd" : "Even";

  cout << "Creating " << (type == enPlayerType::HUMAN ? "Human" : "Computer")
       << " player : " << name << " (" << numType << ")" << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsNumericalAIPlayer(name, symbol);
  }
  return new clsPlayer(name, symbol, type);
}

clsMove<int> *clsNumericalUI::getMove(clsPlayer<int> *player) {
  clsNumericalBoard *currentBoard =
      dynamic_cast<clsNumericalBoard *>(player->getBoardPtr());
  int x, y, symbol;
  int numType = player->getSymbol();
  if (player->getType() == enPlayerType::HUMAN) {

    if (numType % 2) {
      cout << "Please enter number from : ";
      printAvailableNumbers(currentBoard, numType);
      cout << endl;

      while ((!clsInputValidate::validInteger(symbol)) ||
             (currentBoard->sAvailableOddNumbers.find(symbol) ==
              currentBoard->sAvailableOddNumbers.end())) {
        cout << "Invalid input. ";
        cout << "Please enter number from : ";
        printAvailableNumbers(currentBoard, numType);
        cout << endl;
      }
      currentBoard->sAvailableOddNumbers.erase(symbol);
    } else {
      cout << "Please enter number from : ";
      printAvailableNumbers(currentBoard, numType);
      cout << endl;

      while ((!clsInputValidate::validInteger(symbol)) ||
             (currentBoard->sAvailableEvenNumbers.find(symbol) ==
              currentBoard->sAvailableEvenNumbers.end())) {
        cout << "Invalid input. ";
        cout << "Please enter number from : ";
        printAvailableNumbers(currentBoard, numType);
        cout << endl;
      }
      currentBoard->sAvailableEvenNumbers.erase(symbol);
    }

    cout << "Please enter your move x and y (0 to 2): ";
    while ((!clsInputValidate::validIntegerInRange(x, 0, 2)) ||
           (!clsInputValidate::validIntegerInRange(y, 0, 2))) {
      cout << endl
           << "Invalid input , Please enter your move x and y (0 to 2): ";
    }

  }

  else if (player->getType() == enPlayerType::COMPUTER) {
    clsNumericalAIPlayer *AIPlayer =
        dynamic_cast<clsNumericalAIPlayer *>(player);
    if (AIPlayer) {

      clsMove<int> *AI_move = AIPlayer->getBestMove();
      if (numType % 2) {
        currentBoard->sAvailableOddNumbers.erase(AI_move->getSymbol());
      } else {
        currentBoard->sAvailableEvenNumbers.erase(AI_move->getSymbol());
      }
      return AI_move;
    }
  }
  return new clsMove<int>(x, y, symbol);
}

clsPlayer<int> **clsNumericalUI::setupPlayers() {
  clsPlayer<int> **players = new clsPlayer<int> *[2];
  vector<string> vTypeOptions = {"Human", "Computer"};

  string nameOdd = getPlayerName("Odd player");
  enPlayerType typeOdd = getPlayerTypeChoice("Odd player", vTypeOptions);
  players[0] = createPlayer(nameOdd, static_cast<int>(1), typeOdd);

  string nameEven = getPlayerName("Even player");
  enPlayerType typeEven = getPlayerTypeChoice("Even player", vTypeOptions);
  players[1] = createPlayer(nameEven, static_cast<int>(0), typeEven);

  return players;
}
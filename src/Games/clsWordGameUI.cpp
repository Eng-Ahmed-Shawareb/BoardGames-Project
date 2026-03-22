#include "clsWordGameUI.h"
#include "clsInputValidate.h"
#include "clsWordGameAIPlayer.h"
#include "clsTUIUtils.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

clsWordGameUI::clsWordGameUI() : clsUI<char>("Welcome to my Word game!" , 3) {}

clsPlayer<char> **clsWordGameUI::setupPlayers() {
  clsPlayer<char> **players = new clsPlayer<char> *[2];
  vector<string> typeOptions = {"Human", "AI"};

  string name1 = getPlayerName("Player 1");
  enPlayerType type1 = getPlayerTypeChoice("Player 1", typeOptions);
  players[0] = createPlayer(name1, '1', type1);

  string name2 = getPlayerName("Player 2");
  enPlayerType type2 = getPlayerTypeChoice("Player 2", typeOptions);
  players[1] = createPlayer(name2, '2', type2);

  return players;
}

clsPlayer<char> *clsWordGameUI::createPlayer(string &name, char symbol,
                                             enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "AI")
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
    clsTUIUtils::color(enTUIColor::BLUE);
    cout << player->getName() << " " << "turn" << endl;
    clsTUIUtils::resetColor();
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

void clsWordGameUI::displayBoardMatrix(const vector<vector<char>> &matrix) const {
  if (matrix.empty() || matrix[0].empty()) return;

  int rows = matrix.size();
  int cols = matrix[0].size();

  cout << "\n    ";
  clsTUIUtils::color(enTUIColor::CYAN);
  for (int j = 0; j < cols; ++j) cout << setw(cellWidth + 1) << j << " ";
  cout << "\n";

  clsTUIUtils::color(enTUIColor::BLUE);
  cout << "   \u250C";
  for (int j = 0; j < cols; ++j) {
    for (int k = 0; k < cellWidth + 1; ++k) cout << "\u2500";
    if (j < cols - 1) cout << "\u252C";
  }
  cout << "\u2510\n";

  for (int i = 0; i < rows; ++i) {
    clsTUIUtils::color(enTUIColor::CYAN);
    cout << setw(2) << i << " ";
    clsTUIUtils::color(enTUIColor::BLUE);
    cout << "\u2502";
    for (int j = 0; j < cols; ++j) {
      cout << " ";

      char val = matrix[i][j];
      if (isalpha(val)) clsTUIUtils::color(enTUIColor::YELLOW);
      else clsTUIUtils::color(enTUIColor::WHITE);

      cout << val;
      clsTUIUtils::color(enTUIColor::BLUE);
      cout << setw(cellWidth - 1) << " " << "\u2502";
    }
    cout << "\n";

    if (i < rows - 1) {
      cout << "   \u251C";
      for (int j = 0; j < cols; ++j) {
        for (int k = 0; k < cellWidth + 1; ++k) cout << "\u2500";
        if (j < cols - 1) cout << "\u253C";
      }
      cout << "\u2524\n";
    }
  }
  cout << "   \u2514";
  for (int j = 0; j < cols; ++j) {
    for (int k = 0; k < cellWidth + 1; ++k) cout << "\u2500";
    if (j < cols - 1) cout << "\u2534";
  }
  cout << "\u2518\n";
  clsTUIUtils::resetColor();
  cout << endl;
}

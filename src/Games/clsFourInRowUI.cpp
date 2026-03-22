#include "clsFourInRowUI.h"
#include "BoardGame_Classes.h"
#include "clsFourInRowAIPlayer.h"
#include "clsFourInRowBoard.h"
#include "clsInputValidate.h"
#include "clsTUIUtils.h"
#include <iomanip>
#include <iostream>

using namespace std;

clsFourInRowUI::clsFourInRowUI()
    : clsUI("Welcome to my Four In Row game!", 3){};

clsMove<char> *clsFourInRowUI::getMove(clsPlayer<char> *player) {
  int x = 0;
  int y;
  char symbol = player->getSymbol();
  if (player->getType() == enPlayerType::HUMAN) {
    clsTUIUtils::color(enTUIColor::BLUE);
    cout << player->getName() << " " << "turn" << endl;
    clsTUIUtils::resetColor();
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
  cout << "Creating " << (type == enPlayerType::HUMAN ? "Human" : "AI")
       << " player : " << name << " (" << symbol << ")" << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsFourInRowAIPlayer(name, symbol);
  }
  return new clsPlayer(name, symbol, type);
}

clsPlayer<char> **clsFourInRowUI::setupPlayers() {
  clsPlayer<char> **players = new clsPlayer<char> *[2];
  vector<string> vTypeOptions = {"Human", "AI"};

  string nameX = getPlayerName("Player X");
  enPlayerType typeX = getPlayerTypeChoice("Player X", vTypeOptions);
  players[0] = createPlayer(nameX, static_cast<char>('X'), typeX);

  string nameO = getPlayerName("Player O");
  enPlayerType typeO = getPlayerTypeChoice("Player O", vTypeOptions);
  players[1] = createPlayer(nameO, static_cast<char>('O'), typeO);

  return players;
}

void clsFourInRowUI::displayBoardMatrix(const vector<vector<char>> &matrix) const {
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
      if (val == 'X') clsTUIUtils::color(enTUIColor::BRIGHT_RED);
      else if (val == 'O') clsTUIUtils::color(enTUIColor::BRIGHT_YELLOW);
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
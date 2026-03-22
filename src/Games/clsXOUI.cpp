#include "clsXOUI.h"
#include "BoardGame_Classes.h"
#include "clsInputValidate.h"
#include "clsXOAIPlayer.h"
#include "clsXOBoard.h"
#include "clsTUIUtils.h"
#include <algorithm>
#include <iostream>
#include <vector>

clsXOUI::clsXOUI() : clsUI<char>("Welcome to my XO game!", 3) {}

clsPlayer<char> *clsXOUI::createPlayer(string &name, char symbol,
                                       enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "AI")
       << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsXOAIPlayer(name, symbol);
  }
  return new clsPlayer<char>(name, symbol, type);
}

clsMove<char> *clsXOUI::getMove(clsPlayer<char> *player) {
  int x, y;

  if (player->getType() == enPlayerType::HUMAN) {
    clsTUIUtils::color(enTUIColor::BLUE);
    cout << player->getName() << " " << "turn" << endl;
    clsTUIUtils::resetColor();
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

void clsXOUI::displayBoardMatrix(const vector<vector<char>> &matrix) const {
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
      else if (val == 'O') clsTUIUtils::color(enTUIColor::BRIGHT_GREEN);
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

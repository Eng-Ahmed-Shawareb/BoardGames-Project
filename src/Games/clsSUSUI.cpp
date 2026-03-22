#include "clsSUSUI.h"
#include "BoardGame_Classes.h"
#include "clsSUSAIPlayer.h"
#include "clsSUSBoard.h"
#include "clsInputValidate.h"
#include "clsTUIUtils.h"
#include <iomanip>
#include <iostream>
#include <vector>

clsSUSUI::clsSUSUI() : clsUI("Welcome to my SUS game!", 3){};

clsMove<char> *clsSUSUI::getMove(clsPlayer<char> *player) {
  int x;
  int y;
  char symbol = player->getSymbol();

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
  cout << "Creating " << (type == enPlayerType::HUMAN ? "Human" : "AI")
       << " player : " << name << " (" << symbol << ")" << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsSUSAIPlayer(name, symbol);
  }
  return new clsPlayer(name, symbol, type);
}

clsPlayer<char> **clsSUSUI::setupPlayers() {
  clsPlayer<char> **players = new clsPlayer<char> *[2];
  vector<string> vTypeOptions = {"Human", "AI"};

  string nameS = getPlayerName("Player S");
  enPlayerType typeS = getPlayerTypeChoice("Player S", vTypeOptions);
  players[0] = createPlayer(nameS, 'S', typeS);

  string nameU = getPlayerName("Player U");
  enPlayerType typeU = getPlayerTypeChoice("Player U", vTypeOptions);
  players[1] = createPlayer(nameU, 'U', typeU);

  return players;
}

void clsSUSUI::displayBoardMatrix(const vector<vector<char>> &matrix) const {
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
      if (val == 'S') clsTUIUtils::color(enTUIColor::BRIGHT_MAGENTA);
      else if (val == 'U') clsTUIUtils::color(enTUIColor::BRIGHT_YELLOW);
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
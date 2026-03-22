#include "clsPyramidUI.h"
#include "BoardGame_Classes.h"
#include "clsInputValidate.h"
#include "clsPyramidAIPlayer.h"
#include "clsPyramidBoard.h"
#include "clsTUIUtils.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

clsPyramidUI::clsPyramidUI() : clsUI<char>("Welcome to my Pyramid Tic-Tac-Toe game!", 3) {}

clsPlayer<char> *clsPyramidUI::createPlayer(string &name, char symbol,
                                            enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "Human" : "AI")
       << " player : " << name << " (" << symbol << ")" << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsPyramidAIPlayer(name, symbol);
  }
  return new clsPlayer(name, symbol, type);
}

clsMove<char> *clsPyramidUI::getMove(clsPlayer<char> *player) {
  int x;
  int y;
  char symbol = player->getSymbol();

  if (player->getType() == enPlayerType::HUMAN) {
    clsTUIUtils::color(enTUIColor::BLUE);
    cout << player->getName() << " " << "turn" << endl;
    clsTUIUtils::resetColor();
    cout << "Please enter your move x and y (0 to 2): ";
    while (((!clsInputValidate::validIntegerInRange(x, 0, 2)) ||
           (!clsInputValidate::validIntegerInRange(y, 0, 4))) || !((x == 0 && y == 2) || (x == 1 && y >= 1 && y <= 3) || (x == 2 && y >= 0 && y <= 4))) {
      cout << endl
           << "Invalid input , Please enter your move x and y (0 to 2): ";
    }

  }

  bool validPos = false;
      if (x == 0 && y == 2) validPos = true;
      else if (x == 1 && y >= 1 && y <= 3) validPos = true;
      else if (x == 2 && y >= 0 && y <= 4) validPos = true;

  else if (player->getType() == enPlayerType::COMPUTER) {

    clsPyramidAIPlayer *AIPlayer = dynamic_cast<clsPyramidAIPlayer *>(player);
    if (AIPlayer) {
      return AIPlayer->getBestMove();
    }
  }

  return new clsMove<char>(x, y, symbol);
}

clsPlayer<char> **clsPyramidUI::setupPlayers() {
  clsPlayer<char>** players = new clsPlayer<char>* [2];
  vector<string> vTypeOptions = {"Human" , "AI"};

  string nameX = getPlayerName("Player X");
  enPlayerType typeX = getPlayerTypeChoice("Player X" , vTypeOptions);
  players[0] = createPlayer(nameX , 'X' , typeX);

  string nameO = getPlayerName("Player O");
  enPlayerType typeO = getPlayerTypeChoice("Player O" , vTypeOptions);
  players[1] = createPlayer(nameO , 'O' , typeO);

  return players;
}

void clsPyramidUI::displayBoardMatrix(const vector<vector<char>> &matrix) const {
  auto printCell = [](char c) {
    if (c == 'X') { clsTUIUtils::color(enTUIColor::BRIGHT_RED); cout << " " << c << " "; }
    else if (c == 'O') { clsTUIUtils::color(enTUIColor::BRIGHT_GREEN); cout << " " << c << " "; }
    else if (c != ' ') { clsTUIUtils::color(enTUIColor::WHITE); cout << " " << c << " "; }
    else { cout << "   "; }
    clsTUIUtils::color(enTUIColor::BLUE);
  };

  cout << "\n";
  clsTUIUtils::color(enTUIColor::BLUE);

  cout << "            \u250C\u2500\u2500\u2500\u2510\n";

  cout << "            \u2502";
  printCell(matrix[0][2]);
  cout << "\u2502\n";

  cout << "        \u250C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u2510\n";

  cout << "        \u2502";
  printCell(matrix[1][1]); cout << "\u2502";
  printCell(matrix[1][2]); cout << "\u2502";
  printCell(matrix[1][3]); cout << "\u2502\n";

  cout << "    \u250C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u253C\u2500\u2500\u2500\u2510\n";

  cout << "    \u2502";
  printCell(matrix[2][0]); cout << "\u2502";
  printCell(matrix[2][1]); cout << "\u2502";
  printCell(matrix[2][2]); cout << "\u2502";
  printCell(matrix[2][3]); cout << "\u2502";
  printCell(matrix[2][4]); cout << "\u2502\n";

  cout << "    \u2514\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2534\u2500\u2500\u2500\u2518\n\n";

  clsTUIUtils::resetColor();
}

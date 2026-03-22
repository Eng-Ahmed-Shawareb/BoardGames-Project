#include "clsFourByFourXOUI.h"
#include "clsFourByFourAIPlayer.h"
#include "clsTUIUtils.h"
#include <iomanip>

clsFourByFourUI::clsFourByFourUI()
    : clsUI<char>("Welcome to my Four In Row game!", 3){};

bool clsFourByFourUI::validDirection(const int &x, const int &y, const char &symbol,
                      clsBoard<char> *currentBoard) {
  if (symbol == 'U' && (x - 1) >= 0 && currentBoard->getCell(x - 1, y) == '.')
    return true;

  if (symbol == 'D' && (x + 1) <= 3 && currentBoard->getCell(x + 1, y) == '.')
    return true;

  if (symbol == 'R' && (y + 1) <= 3 && currentBoard->getCell(x, y+1) == '.')
    return true;

  if (symbol == 'L' && (y - 1) >= 0 && currentBoard->getCell(x, y-1) == '.')
    return true;

  return false;
}

clsMove<char> *clsFourByFourUI::getMove(clsPlayer<char> *player) {
  int x;
  int y;
  char symbol;
  clsBoard<char> *currentBoard = player->getBoardPtr();
  if (player->getType() == enPlayerType::HUMAN) {
    clsTUIUtils::color(enTUIColor::BLUE);
    cout << player->getName() << " " << "turn" << endl;
    clsTUIUtils::resetColor();
    cout << "Please enter your token move x and y (0 to 3): ";
    while ((!clsInputValidate::validIntegerInRange(x, 0, 3)) ||
           (!clsInputValidate::validIntegerInRange(y, 0, 3)) ||
           (currentBoard->getCell(x, y) != player->getSymbol())) {
      cout << endl
           << "Invalid input , Please enter your token move x and y (0 to 3): ";
    }
    cout << endl << "Please enter the move direction [U (up), D (down) , R (right) , L "
            "(left)] ? ";
    cin >> symbol;
    while (!validDirection(x , y , toupper(symbol) , currentBoard)){
      cout << endl << "Invalid direction , Please enter the move direction [U (up), D (down) , R (right) , L "
            "(left)] ? ";
      cin >> symbol;
    }

  } else if (player->getType() == enPlayerType::COMPUTER) {
    clsFourByFourAIPlayer *AI_Player =
        dynamic_cast<clsFourByFourAIPlayer *>(player);
    if (AI_Player) {
      return AI_Player->getBestMove();
    }
  }
  return new clsMove<char>(x, y, toupper(symbol));
}

clsPlayer<char> *clsFourByFourUI::createPlayer(string &name, char symbol,
                                               enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "AI")
       << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsFourByFourAIPlayer(name, symbol);
  }
  return new clsPlayer<char>(name, symbol, type);
}

clsPlayer<char> **clsFourByFourUI::setupPlayers() {
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

void clsFourByFourUI::displayBoardMatrix(const vector<vector<char>> &matrix) const {
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
#include "clsMemoryGameUI.h"
#include "BoardGame_Classes.h"
#include "clsInputValidate.h"
#include "clsXOAIPlayer.h"
#include "clsXOBoard.h"
#include <algorithm>
#include <iostream>
#include <vector>

clsMemoryGameUI::clsMemoryGameUI()
    : clsUI<char>("Welcome to my Memory-XO game!", 3) {}

clsPlayer<char> *clsMemoryGameUI::createPlayer(string &name, char symbol,
                                               enPlayerType type) {
  // Create player based on type
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "computer")
       << endl;

  if (type == enPlayerType::COMPUTER) {
    return new clsXOAIPlayer(name, symbol);
  }
  return new clsPlayer<char>(name, symbol, type);
}

clsMove<char> *clsMemoryGameUI::getMove(clsPlayer<char> *player) {
  int x, y;

  if (player->getType() == enPlayerType::HUMAN) {
    cout << "Please enter your move x and y (0 to 2): ";
    while ((!clsInputValidate::validIntegerInRange(x, 0, 2)) ||
           (!clsInputValidate::validIntegerInRange(y, 0, 2))) {
      cout << endl
           << "Invalid input , Please enter your move x and y (0 to 2): ";
    }
  } else if (player->getType() == enPlayerType::COMPUTER) {
    clsXOAIPlayer *AIPlayer = dynamic_cast<clsXOAIPlayer *>(player);
    if (AIPlayer) {
      return AIPlayer->getBestMove();
    }
  }
  return new clsMove<char>(x, y, player->getSymbol());
}

void clsMemoryGameUI::displayBoardMatrix(
    const vector<vector<char>> &matrix) const {
  if (matrix.empty() || matrix[0].empty())
    return;

  int rows = matrix.size();
  int cols = matrix[0].size();

  cout << "\n    ";
  for (int j = 0; j < cols; ++j)
    cout << setw(cellWidth + 1) << j;
  cout << "\n   " << string((cellWidth + 2) * cols, '-') << "\n";

  for (int i = 0; i < rows; ++i) {
    cout << setw(2) << i << " |";
    for (int j = 0; j < cols; ++j)
      cout << setw(cellWidth)
           << ((matrix[i][j] == 'X' || matrix[i][j] == 'O') ? '?'
                                                            : matrix[i][j])
           << " |";
    cout << "\n   " << string((cellWidth + 2) * cols, '-') << "\n";
  }
  cout << endl;
}
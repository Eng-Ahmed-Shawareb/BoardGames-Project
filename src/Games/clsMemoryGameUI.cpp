#include "clsMemoryGameUI.h"
#include "BoardGame_Classes.h"
#include "clsXOAIPlayer.h"
#include "clsXOBoard.h"
#include <algorithm>
#include <iostream>
#include <vector>

clsMemoryGameUI::clsMemoryGameUI()
    : UI<char>("Welcome to my Memory-XO game!", 3) {}

Player<char> *clsMemoryGameUI::create_player(string &name, char symbol,
                                             PlayerType type) {
  // Create player based on type
  cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer");

  if (type == PlayerType::COMPUTER) {
    return new clsXOAIPlayer(name, symbol);
  }
  return new Player<char>(name, symbol, type);
}

Move<char> *clsMemoryGameUI::get_move(Player<char> *player) {
  int x, y;

  if (player->get_type() == PlayerType::HUMAN) {
    cout << "\nPlease enter your move x and y (0 to 2): ";
    cin >> x >> y;
  } else if (player->get_type() == PlayerType::COMPUTER) {
    clsXOAIPlayer *AIPlayer = dynamic_cast<clsXOAIPlayer *>(player);
    if (AIPlayer) {
      return AIPlayer->getBestMove();
    }
  }
  return new Move<char>(x, y, player->get_symbol());
}

void clsMemoryGameUI::display_board_matrix(
    const vector<vector<char>> &matrix) const {
  if (matrix.empty() || matrix[0].empty())
    return;

  int rows = matrix.size();
  int cols = matrix[0].size();

  cout << "\n    ";
  for (int j = 0; j < cols; ++j)
    cout << setw(cell_width + 1) << j;
  cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";

  for (int i = 0; i < rows; ++i) {
    cout << setw(2) << i << " |";
    for (int j = 0; j < cols; ++j)
      cout << setw(cell_width)
           << ((matrix[i][j] == 'X' || matrix[i][j] == 'O') ? '?'
                                                            : matrix[i][j])
           << " |";
    cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
  }
  cout << endl;
}
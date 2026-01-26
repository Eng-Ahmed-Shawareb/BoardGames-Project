#include "MemoryGame_UI.h"
#include "BoardGame_Classes.h"
#include "XO_AI_Player.h"
#include "XO_Board.h"
#include <algorithm>
#include <iostream>
#include <vector>

MemoryGame_UI::MemoryGame_UI() : UI<char>("Welcome to my Memory-XO game!", 3) {}

Player<char> *MemoryGame_UI::create_player(string &name, char symbol,
                                           PlayerType type) {
  // Create player based on type
  cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer");

  if (type == PlayerType::COMPUTER) {
    return new XO_AI_Player(name, symbol);
  }
  return new Player<char>(name, symbol, type);
}

Move<char> *MemoryGame_UI::get_move(Player<char> *player) {
  int x, y;

  if (player->get_type() == PlayerType::HUMAN) {
    cout << "\nPlease enter your move x and y (0 to 2): ";
    cin >> x >> y;
  } else if (player->get_type() == PlayerType::COMPUTER) {
    XO_AI_Player* AI_player = dynamic_cast<XO_AI_Player*>(player);
    if(AI_player){
      return AI_player->get_best_move();
    }
  }
  return new Move<char>(x, y, player->get_symbol());
}

void MemoryGame_UI::display_board_matrix(
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
#include "XO_AI_Player.h"
using namespace std;

XO_AI_Player::XO_AI_Player(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER) {}

Move<char> *XO_AI_Player::get_best_move() {

  X_O_Board *test_board = new X_O_Board();
  *test_board = *(dynamic_cast<X_O_Board *>(get_board_ptr()));

  Move<char> *best_move = new Move<char>(-1, -1, get_symbol());
  int best_score = -1e5;
  for (int i = 0; i < test_board->get_rows(); ++i)
    for (int j = 0; j < test_board->get_columns(); ++j) {

      if (test_board->get_cell(i, j) == '.') {

        Move<char> current_move(i, j, get_symbol());
        test_board->update_board(&current_move);

        int score = min_max(test_board, 0, false);

        Move<char> undo_move(i, j, 0);
        test_board->update_board(&undo_move);

        if (score > best_score) {
          best_score = score;
          delete best_move;
          best_move = new Move<char>(i, j, get_symbol());
        }
      }
    }

  delete test_board;
  return best_move;
}

int XO_AI_Player::min_max(Board<char> *current_board, int depth, bool is_max) {
  // base case
  char human_symbol = (get_symbol() == 'X') ? 'O' : 'X';
  Player<char> human_Player("human", human_symbol, PlayerType::HUMAN);

  if (current_board->is_win(this)) {
    return 10 - depth;
  }
  if (current_board->is_win(&human_Player)) {
    return -10 + depth;
  }
  if (current_board->is_draw(this)) {
    return 0;
  }

  // transition
  if (is_max) {
    int max_score = -1e5;

    for (int i = 0; i < current_board->get_rows(); ++i)
      for (int j = 0; j < current_board->get_columns(); ++j) {
        if (current_board->get_cell(i, j) == '.') {
          Move<char> current_move(i, j, get_symbol());
          current_board->update_board(&current_move);
          int score = min_max(current_board, depth + 1, false);
          Move<char> undo_move(i, j, 0);
          current_board->update_board(&undo_move);
          max_score = max(score, max_score);
        }
      }
    return max_score;
  } else {
    int min_score = 1e5;

    for (int i = 0; i < current_board->get_rows(); ++i)
      for (int j = 0; j < current_board->get_columns(); ++j) {

        if (current_board->get_cell(i, j) == '.') {
          Move<char> current_move(i, j, human_symbol);
          current_board->update_board(&current_move);
          int score = min_max(current_board, depth + 1, true);
          Move<char> undo_move(i, j, 0);
          current_board->update_board(&undo_move);
          min_score = min(score, min_score);
        }
      }
    return min_score;
  }
}
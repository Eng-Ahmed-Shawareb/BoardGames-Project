#include "FourInRow_AI_Player.h"

FourInRow_AI_Player::FourInRow_AI_Player(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER) {}

Move<char> *FourInRow_AI_Player::get_best_move() {

  FourInRow_Board *test_board = new FourInRow_Board();
  *test_board = *(dynamic_cast<FourInRow_Board *>(get_board_ptr()));

  int best_score = -1e5;

  Move<char> *best_move = new Move<char>(0, 0, get_symbol());

  int column_order[] = {3, 2, 4, 1, 5, 0, 6};

  for (int idx = 0; idx < 7; ++idx) {
    int i = column_order[idx];

    if (test_board->get_cell(0, i) == '.') {
      Move<char> current_move(0, i, get_symbol());
      test_board->update_board(&current_move);

      int score = min_max(test_board, false, 0, best_score, 1e5);

      Move<char> undo_move(0, i, 0);
      test_board->update_board(&undo_move);

      if (score > best_score) {
        best_score = score;
        delete best_move;
        best_move = new Move<char>(0, i, get_symbol());
      }
    }
  }

  delete test_board;
  return best_move;
}

int FourInRow_AI_Player::min_max(Board<char> *current_board, bool is_max,
                                 int depth, int alpha, int beta) {
  // base case
  char human_symbol = (get_symbol() == 'X') ? 'O' : 'X';
  Player<char> AI_player("AI", get_symbol(), PlayerType::COMPUTER);
  AI_player.set_board_ptr(current_board);
  Player<char> human_player("human", human_symbol, PlayerType::HUMAN);
  human_player.set_board_ptr(current_board);

  if (current_board->is_win(&AI_player)) {
    return 10 + (100 - depth);
  }
  if (current_board->is_win(&human_player)) {
    return -10 - (100 - depth);
  }
  if (current_board->is_draw(&AI_player)) {
    return 0;
  }

  if (depth > 8)
    return 0;

  // transition
  if (is_max) {
    int max_score = -1e5;

    for (int i = 0; i < current_board->get_columns(); ++i) {

      if (current_board->get_cell(0, i) == '.') {
        Move<char> current_move(0, i, get_symbol());
        current_board->update_board(&current_move);

        int score = min_max(current_board, false, depth + 1, alpha, beta);

        Move<char> undo_move(0, i, 0);
        current_board->update_board(&undo_move);

        alpha = max(alpha, score);

        max_score = max(score, max_score);

        if (alpha >= beta)
          break;
      }
    }

    return max_score;

  } else {
    int min_score = 1e5;

    for (int i = 0; i < current_board->get_columns(); ++i) {

      if (current_board->get_cell(0, i) == '.') {
        Move<char> current_move(0, i, human_symbol);
        current_board->update_board(&current_move);

        int score = min_max(current_board, true, depth + 1, alpha, beta);

        Move<char> undo_move(0, i, 0);
        current_board->update_board(&undo_move);

        beta = min(beta, score);

        min_score = min(score, min_score);

        if (alpha >= beta)
          break;
      }
    }

    return min_score;
  }
}
#include "SUS_AI_Player.h"

SUS_AI_Player::SUS_AI_Player(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER){};

Move<char> *SUS_AI_Player::get_best_move() {

  SUS_Board *test_board = new SUS_Board();
  *test_board = *(dynamic_cast<SUS_Board *>(get_board_ptr()));

  int best_score = -1e5;
  Move<char> *best_move = new Move<char>(-1, -1, get_symbol());

  for (int i = 0; i < test_board->get_rows(); ++i)
    for (int j = 0; j < test_board->get_columns(); ++j) {

      if (test_board->get_cell(i, j) == '.') {

        Move<char> current_move(i, j, get_symbol());
        test_board->update_board(&current_move);

        int score = min_max(test_board, false);

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

int SUS_AI_Player::min_max(SUS_Board *current_board, bool is_max) {
  // base case
  char human_symbol = (get_symbol() == 'S') ? 'U' : 'S';
  Player<char> AI_player("AI", get_symbol(), PlayerType::COMPUTER);
  Player<char> human_player("human", human_symbol, PlayerType::HUMAN);

  if (current_board->game_is_over(&AI_player)) {

    pair<int, int> scores = current_board->calculate_players_score();

    if (current_board->is_win(&AI_player)) {

      if (get_symbol() == 'U')
        return scores.first - scores.second;
      else
        return scores.second - scores.first;
    }
    if (current_board->is_win(&human_player)) {
      if (human_symbol == 'U')
        return scores.second - scores.first;
      else
        return scores.first - scores.second;
    } else
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

          int score = min_max(current_board, false);

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

          int score = min_max(current_board, true);

          Move<char> undo_move(i, j, 0);
          current_board->update_board(&undo_move);

          min_score = min(score, min_score);
        }
      }

    return min_score;
  }
}
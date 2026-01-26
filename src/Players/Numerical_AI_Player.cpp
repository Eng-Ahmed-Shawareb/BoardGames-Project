#include "Numerical_AI_Player.h"

Numerical_AI_Player::Numerical_AI_Player(string name, int symbol)
    : Player<int>(name, symbol, PlayerType::COMPUTER){};

Move<int> *Numerical_AI_Player::get_best_move() {

  Numerical_Board *test_board = new Numerical_Board();
  *test_board = *(dynamic_cast<Numerical_Board *>(get_board_ptr()));

  int num_type = get_symbol();

  vector<int> choices;
  int symbol_index;
  if (get_symbol() % 2) {
    for (auto &i : test_board->available_odd_numbers)
      choices.push_back(i);
  } else {
    for (auto &i : test_board->available_even_numbers)
      choices.push_back(i);
  }

  Move<int> *best_move = new Move<int>(0, 0, num_type);
  int best_score = -1e5;

  for (int i = 0; i < test_board->get_rows(); ++i)
    for (int j = 0; j < test_board->get_columns(); ++j) {
      if (test_board->get_cell(i, j) == 0) {

        for (int num : choices) {
          Move<int> current_move(i, j, num);
          test_board->update_board(&current_move);

          (get_symbol() % 2) ? test_board->available_odd_numbers.erase(num)
                             : test_board->available_even_numbers.erase(num);

          int score = min_max(test_board, 0, best_score, 1e5, false);

          Move<int> undo_move(i, j, 0);
          test_board->update_board(&undo_move);

          (get_symbol() % 2) ? test_board->available_odd_numbers.insert(num)
                             : test_board->available_even_numbers.insert(num);

          if (score > best_score) {
            best_score = score;
            delete best_move;
            best_move = new Move<int>(i, j, num);
          }
        }
      }
    }
  (get_symbol() % 2)
      ? test_board->available_odd_numbers.erase(best_move->get_symbol())
      : test_board->available_even_numbers.erase(best_move->get_symbol());
  delete test_board;
  return best_move;
}

int Numerical_AI_Player::min_max(Numerical_Board *current_board, int depth,
                                 int alpha, int beta, bool is_max) {
  // base case

  Player<int> temp_player("temp", 0, PlayerType::HUMAN);

  if (current_board->is_win(&temp_player)) {

    if (is_max) {
      return -10 - (100 - depth);
    } else {
      return 10 + (100 - depth);
    }
  }

  if (current_board->is_draw(&temp_player)) {
    return 0;
  }

  if (depth > 8)
    return 0;

  // transition
  int human_type = (get_symbol() % 2 == 0) ? 1 : 0;

  if (is_max) {
    int max_score = -1e5;

    vector<int> choices;
    int symbol_index;
    if (get_symbol() % 2) {
      for (auto &i : current_board->available_odd_numbers)
        choices.push_back(i);
    } else {
      for (auto &i : current_board->available_even_numbers)
        choices.push_back(i);
    }

    for (int i = 0; i < current_board->get_rows(); ++i)
      for (int j = 0; j < current_board->get_columns(); ++j) {
        if (current_board->get_cell(i, j) == 0) {

          for (int num : choices) {
            Move<int> current_move(i, j, num);
            current_board->update_board(&current_move);

            (get_symbol() % 2)
                ? current_board->available_odd_numbers.erase(num)
                : current_board->available_even_numbers.erase(num);

            int score = min_max(current_board, depth + 1, alpha, beta, false);

            Move<int> undo_move(i, j, 0);
            current_board->update_board(&undo_move);

            (get_symbol() % 2)
                ? current_board->available_odd_numbers.insert(num)
                : current_board->available_even_numbers.insert(num);

            max_score = max(max_score, score);

            alpha = max(alpha, score);

            if (alpha >= beta)
              break;
          }
        }
      }

    return max_score;
  }

  else {
    int min_score = 1e5;

    vector<int> choices;
    int symbol_index;
    if (human_type % 2) {
      for (auto &i : current_board->available_odd_numbers)
        choices.push_back(i);
    } else {
      for (auto &i : current_board->available_even_numbers)
        choices.push_back(i);
    }

    for (int i = 0; i < current_board->get_rows(); ++i)
      for (int j = 0; j < current_board->get_columns(); ++j) {
        if (current_board->get_cell(i, j) == 0) {

          for (int num : choices) {
            Move<int> current_move(i, j, num);
            current_board->update_board(&current_move);

            (human_type % 2) ? current_board->available_odd_numbers.erase(num)
                             : current_board->available_even_numbers.erase(num);

            int score = min_max(current_board, depth + 1, alpha, beta, true);

            Move<int> undo_move(i, j, 0);
            current_board->update_board(&undo_move);
            (human_type % 2)
                ? current_board->available_odd_numbers.insert(num)
                : current_board->available_even_numbers.insert(num);

            min_score = min(min_score, score);

            beta = min(beta, score);

            if (alpha >= beta)
              break;
          }
        }
      }

    return min_score;
  }
}
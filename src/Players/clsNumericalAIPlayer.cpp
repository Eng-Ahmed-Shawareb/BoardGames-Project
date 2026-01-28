#include "clsNumericalAIPlayer.h"

clsNumericalAIPlayer::clsNumericalAIPlayer(string name, int symbol)
    : Player<int>(name, symbol, PlayerType::COMPUTER){};

Move<int> *clsNumericalAIPlayer::getBestMove() {

  clsNumericalBoard *testBoard = new clsNumericalBoard();
  *testBoard = *(dynamic_cast<clsNumericalBoard *>(get_board_ptr()));

  int numType = get_symbol();

  vector<int> choices;
  int symbolIndex;
  if (get_symbol() % 2) {
    for (auto &i : testBoard->sAvailableOddNumbers)
      choices.push_back(i);
  } else {
    for (auto &i : testBoard->sAvailableEvenNumbers)
      choices.push_back(i);
  }

  Move<int> *bestMove = new Move<int>(0, 0, numType);
  int bestScore = -1e5;

  for (int i = 0; i < testBoard->get_rows(); ++i)
    for (int j = 0; j < testBoard->get_columns(); ++j) {
      if (testBoard->get_cell(i, j) == 0) {

        for (int num : choices) {
          Move<int> currentMove(i, j, num);
          testBoard->update_board(&currentMove);

          (get_symbol() % 2) ? testBoard->sAvailableOddNumbers.erase(num)
                             : testBoard->sAvailableEvenNumbers.erase(num);

          int score = _minMax(testBoard, 0, bestScore, 1e5, false);

          Move<int> undoMove(i, j, 0);
          testBoard->update_board(&undoMove);

          (get_symbol() % 2) ? testBoard->sAvailableOddNumbers.insert(num)
                             : testBoard->sAvailableEvenNumbers.insert(num);

          if (score > bestScore) {
            bestScore = score;
            delete bestMove;
            bestMove = new Move<int>(i, j, num);
          }
        }
      }
    }
  (get_symbol() % 2)
      ? testBoard->sAvailableOddNumbers.erase(bestMove->get_symbol())
      : testBoard->sAvailableEvenNumbers.erase(bestMove->get_symbol());
  delete testBoard;
  return bestMove;
}

int clsNumericalAIPlayer::_minMax(clsNumericalBoard *currentBoard, int depth,
                                  int alpha, int beta, bool isMax) {
  // base case

  Player<int> tempPlayer("temp", 0, PlayerType::HUMAN);

  if (currentBoard->is_win(&tempPlayer)) {

    if (isMax) {
      return -10 - (100 - depth);
    } else {
      return 10 + (100 - depth);
    }
  }

  if (currentBoard->is_draw(&tempPlayer)) {
    return 0;
  }

  if (depth > 8)
    return 0;

  // transition
  int humanType = (get_symbol() % 2 == 0) ? 1 : 0;

  if (isMax) {
    int maxScore = -1e5;

    vector<int> choices;
    int symbolIndex;
    if (get_symbol() % 2) {
      for (auto &i : currentBoard->sAvailableOddNumbers)
        choices.push_back(i);
    } else {
      for (auto &i : currentBoard->sAvailableEvenNumbers)
        choices.push_back(i);
    }

    for (int i = 0; i < currentBoard->get_rows(); ++i)
      for (int j = 0; j < currentBoard->get_columns(); ++j) {
        if (currentBoard->get_cell(i, j) == 0) {

          for (int num : choices) {
            Move<int> currentMove(i, j, num);
            currentBoard->update_board(&currentMove);

            (get_symbol() % 2) ? currentBoard->sAvailableOddNumbers.erase(num)
                               : currentBoard->sAvailableEvenNumbers.erase(num);

            int score = _minMax(currentBoard, depth + 1, alpha, beta, false);

            Move<int> undoMove(i, j, 0);
            currentBoard->update_board(&undoMove);

            (get_symbol() % 2)
                ? currentBoard->sAvailableOddNumbers.insert(num)
                : currentBoard->sAvailableEvenNumbers.insert(num);

            maxScore = max(maxScore, score);

            alpha = max(alpha, score);

            if (alpha >= beta)
              break;
          }
        }
      }

    return maxScore;
  }

  else {
    int minScore = 1e5;

    vector<int> choices;
    int symbolIndex;
    if (humanType % 2) {
      for (auto &i : currentBoard->sAvailableOddNumbers)
        choices.push_back(i);
    } else {
      for (auto &i : currentBoard->sAvailableEvenNumbers)
        choices.push_back(i);
    }

    for (int i = 0; i < currentBoard->get_rows(); ++i)
      for (int j = 0; j < currentBoard->get_columns(); ++j) {
        if (currentBoard->get_cell(i, j) == 0) {

          for (int num : choices) {
            Move<int> currentMove(i, j, num);
            currentBoard->update_board(&currentMove);

            (humanType % 2) ? currentBoard->sAvailableOddNumbers.erase(num)
                            : currentBoard->sAvailableEvenNumbers.erase(num);

            int score = _minMax(currentBoard, depth + 1, alpha, beta, true);

            Move<int> undoMove(i, j, 0);
            currentBoard->update_board(&undoMove);
            (humanType % 2) ? currentBoard->sAvailableOddNumbers.insert(num)
                            : currentBoard->sAvailableEvenNumbers.insert(num);

            minScore = min(minScore, score);

            beta = min(beta, score);

            if (alpha >= beta)
              break;
          }
        }
      }

    return minScore;
  }
}
#include "clsSUSAIPlayer.h"

clsSUSAIPlayer::clsSUSAIPlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER){};

Move<char> *clsSUSAIPlayer::getBestMove() {

  clsSUSBoard *testBoard = new clsSUSBoard();
  *testBoard = *(dynamic_cast<clsSUSBoard *>(get_board_ptr()));

  int bestScore = -1e5;
  Move<char> *bestMove = new Move<char>(-1, -1, get_symbol());

  for (int i = 0; i < testBoard->get_rows(); ++i)
    for (int j = 0; j < testBoard->get_columns(); ++j) {

      if (testBoard->get_cell(i, j) == '.') {

        Move<char> currentMove(i, j, get_symbol());
        testBoard->update_board(&currentMove);

        int score = _minMax(testBoard, false);

        Move<char> undoMove(i, j, 0);
        testBoard->update_board(&undoMove);

        if (score > bestScore) {
          bestScore = score;
          delete bestMove;
          bestMove = new Move<char>(i, j, get_symbol());
        }
      }
    }

  delete testBoard;
  return bestMove;
}

int clsSUSAIPlayer::_minMax(clsSUSBoard *currentBoard, bool isMax) {
  // base case
  char humanSymbol = (get_symbol() == 'S') ? 'U' : 'S';
  Player<char> AIPlayer("AI", get_symbol(), PlayerType::COMPUTER);
  Player<char> humanPlayer("human", humanSymbol, PlayerType::HUMAN);

  if (currentBoard->game_is_over(&AIPlayer)) {

    pair<int, int> scores = currentBoard->calculatePlayersScore();

    if (currentBoard->is_win(&AIPlayer)) {

      if (get_symbol() == 'U')
        return scores.first - scores.second;
      else
        return scores.second - scores.first;
    }
    if (currentBoard->is_win(&humanPlayer)) {
      if (humanSymbol == 'U')
        return scores.second - scores.first;
      else
        return scores.first - scores.second;
    } else
      return 0;
  }
  // transition
  if (isMax) {
    int maxScore = -1e5;

    for (int i = 0; i < currentBoard->get_rows(); ++i)
      for (int j = 0; j < currentBoard->get_columns(); ++j) {

        if (currentBoard->get_cell(i, j) == '.') {

          Move<char> currentMove(i, j, get_symbol());
          currentBoard->update_board(&currentMove);

          int score = _minMax(currentBoard, false);

          Move<char> undoMove(i, j, 0);
          currentBoard->update_board(&undoMove);

          maxScore = max(score, maxScore);
        }
      }

    return maxScore;

  } else {
    int minScore = 1e5;

    for (int i = 0; i < currentBoard->get_rows(); ++i)
      for (int j = 0; j < currentBoard->get_columns(); ++j) {

        if (currentBoard->get_cell(i, j) == '.') {

          Move<char> currentMove(i, j, humanSymbol);
          currentBoard->update_board(&currentMove);

          int score = _minMax(currentBoard, true);

          Move<char> undoMove(i, j, 0);
          currentBoard->update_board(&undoMove);

          minScore = min(score, minScore);
        }
      }

    return minScore;
  }
}
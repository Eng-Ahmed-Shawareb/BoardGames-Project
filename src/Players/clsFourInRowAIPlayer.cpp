#include "clsFourInRowAIPlayer.h"

clsFourInRowAIPlayer::clsFourInRowAIPlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER) {}

Move<char> *clsFourInRowAIPlayer::getBestMove() {

  clsFourInRowBoard *testBoard = new clsFourInRowBoard();
  *testBoard = *(dynamic_cast<clsFourInRowBoard *>(get_board_ptr()));

  int bestScore = -1e5;

  Move<char> *bestMove = new Move<char>(0, 0, get_symbol());

  int columnOrder[] = {3, 2, 4, 1, 5, 0, 6};

  for (int idx = 0; idx < 7; ++idx) {
    int i = columnOrder[idx];

    if (testBoard->get_cell(0, i) == '.') {
      Move<char> currentMove(0, i, get_symbol());
      testBoard->update_board(&currentMove);

      int score = _minMax(testBoard, false, 0, bestScore, 1e5);

      Move<char> undoMove(0, i, 0);
      testBoard->update_board(&undoMove);

      if (score > bestScore) {
        bestScore = score;
        delete bestMove;
        bestMove = new Move<char>(0, i, get_symbol());
      }
    }
  }

  delete testBoard;
  return bestMove;
}

int clsFourInRowAIPlayer::_minMax(Board<char> *currentBoard, bool isMax,
                                  int depth, int alpha, int beta) {
  // base case
  char humanSymbol = (get_symbol() == 'X') ? 'O' : 'X';
  Player<char> AIPlayer("AI", get_symbol(), PlayerType::COMPUTER);
  AIPlayer.set_board_ptr(currentBoard);
  Player<char> human_player("human", humanSymbol, PlayerType::HUMAN);
  human_player.set_board_ptr(currentBoard);

  if (currentBoard->is_win(&AIPlayer)) {
    return 10 + (100 - depth);
  }
  if (currentBoard->is_win(&human_player)) {
    return -10 - (100 - depth);
  }
  if (currentBoard->is_draw(&AIPlayer)) {
    return 0;
  }

  if (depth > 8)
    return 0;

  // transition
  if (isMax) {
    int maxScore = -1e5;

    for (int i = 0; i < currentBoard->get_columns(); ++i) {

      if (currentBoard->get_cell(0, i) == '.') {
        Move<char> currentMove(0, i, get_symbol());
        currentBoard->update_board(&currentMove);

        int score = _minMax(currentBoard, false, depth + 1, alpha, beta);

        Move<char> undoMove(0, i, 0);
        currentBoard->update_board(&undoMove);

        alpha = max(alpha, score);

        maxScore = max(score, maxScore);

        if (alpha >= beta)
          break;
      }
    }

    return maxScore;

  } else {
    int minScore = 1e5;

    for (int i = 0; i < currentBoard->get_columns(); ++i) {

      if (currentBoard->get_cell(0, i) == '.') {
        Move<char> currentMove(0, i, humanSymbol);
        currentBoard->update_board(&currentMove);

        int score = _minMax(currentBoard, true, depth + 1, alpha, beta);

        Move<char> undoMove(0, i, 0);
        currentBoard->update_board(&undoMove);

        beta = min(beta, score);

        minScore = min(score, minScore);

        if (alpha >= beta)
          break;
      }
    }

    return minScore;
  }
}
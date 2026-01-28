#include "clsXOAIPlayer.h"
using namespace std;

clsXOAIPlayer::clsXOAIPlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::COMPUTER) {}

Move<char> *clsXOAIPlayer::getBestMove() {

  clsXOBoard *testBoard = new clsXOBoard();
  *testBoard = *(dynamic_cast<clsXOBoard *>(get_board_ptr()));

  Move<char> *bestMove = new Move<char>(-1, -1, get_symbol());
  int bestScore = -1e5;
  for (int i = 0; i < testBoard->get_rows(); ++i)
    for (int j = 0; j < testBoard->get_columns(); ++j) {

      if (testBoard->get_cell(i, j) == '.') {

        Move<char> currentMove(i, j, get_symbol());
        testBoard->update_board(&currentMove);

        int score = _minMax(testBoard, 0, false);

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

int clsXOAIPlayer::_minMax(Board<char> *currentBoard, int depth, bool isMax) {
  // base case
  char humanSymbol = (get_symbol() == 'X') ? 'O' : 'X';
  Player<char> humanPlayer("human", humanSymbol, PlayerType::HUMAN);

  if (currentBoard->is_win(this)) {
    return 10 - depth;
  }
  if (currentBoard->is_win(&humanPlayer)) {
    return -10 + depth;
  }
  if (currentBoard->is_draw(this)) {
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
          int score = _minMax(currentBoard, depth + 1, false);
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
          int score = _minMax(currentBoard, depth + 1, true);
          Move<char> undoMove(i, j, 0);
          currentBoard->update_board(&undoMove);
          minScore = min(score, minScore);
        }
      }
    return minScore;
  }
}
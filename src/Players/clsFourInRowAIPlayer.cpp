#include "clsFourInRowAIPlayer.h"

clsFourInRowAIPlayer::clsFourInRowAIPlayer(string name, char symbol)
    : clsPlayer<char>(name, symbol, enPlayerType::COMPUTER) {}

clsMove<char> *clsFourInRowAIPlayer::getBestMove() const {

  clsFourInRowBoard *testBoard = new clsFourInRowBoard();
  *testBoard = *(dynamic_cast<clsFourInRowBoard *>(getBoardPtr()));

  int bestScore = -1e5;

  clsMove<char> *bestMove = new clsMove<char>(0, 0, getSymbol());

  int columnOrder[] = {3, 2, 4, 1, 5, 0, 6};

  for (int idx = 0; idx < 7; ++idx) {
    int i = columnOrder[idx];

    if (testBoard->getCell(0, i) == '.') {
      clsMove<char> currentMove(0, i, getSymbol());
      testBoard->updateBoard(&currentMove);

      int score = _minMax(testBoard, false, 0, bestScore, 1e5);

      clsMove<char> undoMove(0, i, 0);
      testBoard->updateBoard(&undoMove);

      if (score > bestScore) {
        bestScore = score;
        delete bestMove;
        bestMove = new clsMove<char>(0, i, getSymbol());
      }
    }
  }

  delete testBoard;
  return bestMove;
}

int clsFourInRowAIPlayer::_minMax(clsBoard<char> *currentBoard, bool isMax,
                                  int depth, int alpha, int beta) const {

  char humanSymbol = (getSymbol() == 'X') ? 'O' : 'X';
  clsPlayer<char> AIPlayer("AI", getSymbol(), enPlayerType::COMPUTER);
  AIPlayer.setBoardPtr(currentBoard);
  clsPlayer<char> humanPlayer("human", humanSymbol, enPlayerType::HUMAN);
  humanPlayer.setBoardPtr(currentBoard);

  if (currentBoard->isWin(&AIPlayer)) {
    return 10 + (100 - depth);
  }
  if (currentBoard->isWin(&humanPlayer)) {
    return -10 - (100 + depth);
  }
  if (currentBoard->isDraw(&AIPlayer)) {
    return 0;
  }

  if (depth > 8)
    return 0;

  if (isMax) {
    int maxScore = -1e5;

    for (int i = 0; i < currentBoard->getColumns(); ++i) {

      if (currentBoard->getCell(0, i) == '.') {
        clsMove<char> currentMove(0, i, getSymbol());
        currentBoard->updateBoard(&currentMove);

        int score = _minMax(currentBoard, false, depth + 1, alpha, beta);

        clsMove<char> undoMove(0, i, 0);
        currentBoard->updateBoard(&undoMove);

        alpha = max(alpha, score);

        maxScore = max(score, maxScore);

        if (alpha >= beta)
          break;
      }
    }

    return maxScore;

  } else {
    int minScore = 1e5;

    for (int i = 0; i < currentBoard->getColumns(); ++i) {

      if (currentBoard->getCell(0, i) == '.') {
        clsMove<char> currentMove(0, i, humanSymbol);
        currentBoard->updateBoard(&currentMove);

        int score = _minMax(currentBoard, true, depth + 1, alpha, beta);

        clsMove<char> undoMove(0, i, 0);
        currentBoard->updateBoard(&undoMove);

        beta = min(beta, score);

        minScore = min(score, minScore);

        if (alpha >= beta)
          break;
      }
    }

    return minScore;
  }
}
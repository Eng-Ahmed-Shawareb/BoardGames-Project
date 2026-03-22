#include "clsInfinityAIPlayer.h"
using namespace std;

clsInfinityAIPlayer::clsInfinityAIPlayer(string name, char symbol)
    : clsPlayer<char>(name, symbol, enPlayerType::COMPUTER) {}

clsMove<char> *clsInfinityAIPlayer::getBestMove() const {

  clsInfinityBoard *testBoard = new clsInfinityBoard();
  *testBoard = *(dynamic_cast<clsInfinityBoard *>(getBoardPtr()));

  clsMove<char> *bestMove = new clsMove<char>(-1, -1, getSymbol());
  int bestScore = -1e5;
  for (int i = 0; i < testBoard->getRows(); ++i)
    for (int j = 0; j < testBoard->getColumns(); ++j) {

      if (testBoard->getCell(i, j) == '.') {
        clsInfinityBoard* boardCopy = new clsInfinityBoard();
        *boardCopy = *testBoard;
        clsMove<char> currentMove(i, j, getSymbol());
        boardCopy->updateBoard(&currentMove);

        int score = _minMax(boardCopy, 0, false, -1e5, 1e5);
        delete boardCopy;
        if (score > bestScore) {
          bestScore = score;
          delete bestMove;
          bestMove = new clsMove<char>(i, j, getSymbol());
        }
      }
    }

  delete testBoard;
  return bestMove;
}

int clsInfinityAIPlayer::_minMax(clsBoard<char> *currentBoard, int depth,
                                 bool isMax, int alpha, int beta) const {

  char humanSymbol = (getSymbol() == 'X') ? 'O' : 'X';
  clsPlayer<char> humanPlayer("human", humanSymbol, enPlayerType::HUMAN);
  clsPlayer<char> AIPlayer("AI", getSymbol(), enPlayerType::COMPUTER);

  if (currentBoard->isWin(&AIPlayer)) {
    return 1000 - depth;
  }
  if (currentBoard->isWin(&humanPlayer)) {
    return -1000 + depth;
  }

  if (depth > 10)
    return 0;

  if (isMax) {
    int maxScore = -1e5;

    for (int i = 0; i < currentBoard->getRows(); ++i)
      for (int j = 0; j < currentBoard->getColumns(); ++j) {
        if (currentBoard->getCell(i, j) == '.') {
          clsInfinityBoard* boardCopy = new clsInfinityBoard();
          *boardCopy = *(dynamic_cast<clsInfinityBoard*>(currentBoard));
          clsMove<char> currentMove(i, j, getSymbol());
          boardCopy->updateBoard(&currentMove);
          int score = _minMax(boardCopy, depth + 1, false, alpha, beta);
          delete boardCopy;
          maxScore = max(score, maxScore);
          alpha = max(score, alpha);
          if (alpha > beta)
            return maxScore;
        }
      }
    return maxScore;
  } else {
    int minScore = 1e5;

    for (int i = 0; i < currentBoard->getRows(); ++i)
      for (int j = 0; j < currentBoard->getColumns(); ++j) {

        if (currentBoard->getCell(i, j) == '.') {
          clsInfinityBoard* boardCopy = new clsInfinityBoard();
          *boardCopy = *(dynamic_cast<clsInfinityBoard*>(currentBoard));
          clsMove<char> currentMove(i, j, humanSymbol);
          boardCopy->updateBoard(&currentMove);
          int score = _minMax(boardCopy, depth + 1, true, alpha, beta);
          delete boardCopy;
          minScore = min(score, minScore);
          beta = min(beta, score);
          if (alpha > beta)
            return minScore;
        }
      }
    return minScore;
  }
}
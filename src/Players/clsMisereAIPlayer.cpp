#include "clsMisereAIPlayer.h"
using namespace std;

clsMisereAIPlayer::clsMisereAIPlayer(string name, char symbol)
    : clsPlayer<char>(name, symbol, enPlayerType::COMPUTER) {}

clsMove<char> *clsMisereAIPlayer::getBestMove() const {

  clsMisereBoard *testBoard = new clsMisereBoard();
  *testBoard = *(dynamic_cast<clsMisereBoard *>(getBoardPtr()));

  clsMove<char> *bestMove = new clsMove<char>(-1, -1, getSymbol());
  int bestScore = -1e5;
  for (int i = 0; i < testBoard->getRows(); ++i)
    for (int j = 0; j < testBoard->getColumns(); ++j) {

      if (testBoard->getCell(i, j) == '.') {

        clsMove<char> currentMove(i, j, getSymbol());
        testBoard->updateBoard(&currentMove);

        int score = _minMax(testBoard, 0, false);

        clsMove<char> undoMove(i, j, 0);
        testBoard->updateBoard(&undoMove);

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

int clsMisereAIPlayer::_minMax(clsBoard<char> *currentBoard, int depth,
                           bool isMax) const {
  // base case
  char humanSymbol = (getSymbol() == 'X') ? 'O' : 'X';
  clsPlayer<char> humanPlayer("human", humanSymbol, enPlayerType::HUMAN);
  clsPlayer<char> AIPlayer("AI", getSymbol(), enPlayerType::COMPUTER);

  if (currentBoard->isWin(&AIPlayer)) {
    return 10 - depth;
  }
  if (currentBoard->isWin(&humanPlayer)) {
    return -10 + depth;
  }
  if (currentBoard->isDraw(&AIPlayer)) {
    return 0;
  }

  // transition
  if (isMax) {
    int maxScore = -1e5;

    for (int i = 0; i < currentBoard->getRows(); ++i)
      for (int j = 0; j < currentBoard->getColumns(); ++j) {
        if (currentBoard->getCell(i, j) == '.') {
          clsMove<char> currentMove(i, j, getSymbol());
          currentBoard->updateBoard(&currentMove);
          int score = _minMax(currentBoard, depth + 1, false);
          clsMove<char> undoMove(i, j, 0);
          currentBoard->updateBoard(&undoMove);
          maxScore = max(score, maxScore);
        }
      }
    return maxScore;
  } else {
    int minScore = 1e5;

    for (int i = 0; i < currentBoard->getRows(); ++i)
      for (int j = 0; j < currentBoard->getColumns(); ++j) {

        if (currentBoard->getCell(i, j) == '.') {
          clsMove<char> currentMove(i, j, humanSymbol);
          currentBoard->updateBoard(&currentMove);
          int score = _minMax(currentBoard, depth + 1, true);
          clsMove<char> undoMove(i, j, 0);
          currentBoard->updateBoard(&undoMove);
          minScore = min(score, minScore);
        }
      }
    return minScore;
  }
}
#include "clsWordGameAIPlayer.h"
#include "clsWordGameBoard.h"

using namespace std;

clsWordGameAIPlayer::clsWordGameAIPlayer(string name, char symbol)
    : clsPlayer<char>(name, symbol, enPlayerType::COMPUTER) {}

clsMove<char> *clsWordGameAIPlayer::getBestMove() const {
  clsWordGameBoard *testBoard = new clsWordGameBoard();
  *testBoard = *(dynamic_cast<clsWordGameBoard *>(getBoardPtr()));

  clsMove<char> *bestMove = new clsMove<char>(-1, -1, 'A');
  int bestScore = -1e5;

  for (int i = 0; i < testBoard->getRows(); ++i) {
    for (int j = 0; j < testBoard->getColumns(); ++j) {
      if (testBoard->getCell(i, j) == '.') {
        for (char letter = 'A'; letter <= 'Z'; ++letter) {
          clsMove<char> currentMove(i, j, letter);
          testBoard->updateBoard(&currentMove);

          int score = _minMax(testBoard, false, 0, -1e5, 1e5);

          clsMove<char> undoMove(i, j, 0);
          testBoard->updateBoard(&undoMove);

          if (score > bestScore) {
            bestScore = score;
            delete bestMove;
            bestMove = new clsMove<char>(i, j, letter);
          }
        }
      }
    }
  }

  delete testBoard;
  return bestMove;
}

int clsWordGameAIPlayer::_minMax(clsBoard<char> *currentBoard, bool isMax,
                                 int depth, int alpha, int beta) const {

  clsPlayer<char> dummyPlayer("Dummy", 'A', enPlayerType::COMPUTER);
  dummyPlayer.setBoardPtr(currentBoard);

  if (currentBoard->isWin(&dummyPlayer)) {
    if (isMax) {
      return -10 - (100 - depth);
    } else {
      return 10 + (100 - depth);
    }
  }

  if (depth > 1 || currentBoard->isDraw(&dummyPlayer)) {
    return 0;
  }

  if (isMax) {
    int maxScore = -1e5;
    for (int i = 0; i < currentBoard->getRows(); ++i) {
      for (int j = 0; j < currentBoard->getColumns(); ++j) {
        if (currentBoard->getCell(i, j) == '.') {

          for (char letter = 'A'; letter <= 'Z'; ++letter) {
            clsMove<char> currentMove(i, j, letter);
            currentBoard->updateBoard(&currentMove);

            int score = _minMax(currentBoard, false, depth + 1, alpha, beta);

            clsMove<char> undoMove(i, j, 0);
            currentBoard->updateBoard(&undoMove);

            maxScore = max(maxScore, score);
            alpha = max(alpha, score);

            if (alpha >= beta)
              return maxScore;
          }
        }
      }
    }
    return maxScore;
  } else {
    int minScore = 1e5;
    for (int i = 0; i < currentBoard->getRows(); ++i) {
      for (int j = 0; j < currentBoard->getColumns(); ++j) {
        if (currentBoard->getCell(i, j) == '.') {

          for (char letter = 'A'; letter <= 'Z'; ++letter) {
            clsMove<char> currentMove(i, j, letter);
            currentBoard->updateBoard(&currentMove);

            int score = _minMax(currentBoard, true, depth + 1, alpha, beta);

            clsMove<char> undoMove(i, j, 0);
            currentBoard->updateBoard(&undoMove);

            minScore = min(minScore, score);
            beta = min(beta, score);

            if (alpha >= beta)
              return minScore;
          }
        }
      }
    }
    return minScore;
  }
}
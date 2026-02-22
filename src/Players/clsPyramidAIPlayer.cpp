#include "clsPyramidAIPlayer.h"
#include "clsPyramidBoard.h"
#include <algorithm>

using namespace std;

clsPyramidAIPlayer::clsPyramidAIPlayer(string name, char symbol)
    : clsPlayer<char>(name, symbol, enPlayerType::COMPUTER) {}

clsMove<char> *clsPyramidAIPlayer::getBestMove() const {
  clsPyramidBoard *testBoard = new clsPyramidBoard();
  *testBoard = *(dynamic_cast<clsPyramidBoard *>(getBoardPtr()));

  clsMove<char> *bestMove = new clsMove<char>(-1, -1, getSymbol());
  int bestScore = -1e5;

  vector<pair<int, int>> vValidPositions = {
    {0, 2},
    {1, 1}, {1, 2}, {1, 3},
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}
  };

  for (auto pos : vValidPositions) {
    int x = pos.first;
    int y = pos.second;

    if (testBoard->getCell(x, y) == '.') {
      clsMove<char> move(x, y, getSymbol());
      testBoard->updateBoard(&move);

      int score = _minMax(testBoard, 0, false, -1e9, 1e9);

      clsMove<char> undoMove(x, y, 0);
      testBoard->updateBoard(&undoMove);

      if (score > bestScore) {
        bestScore = score;
        delete bestMove;
        bestMove = new clsMove<char>(x, y, getSymbol());
      }
    }
  }

  delete testBoard;
  return bestMove;
}

int clsPyramidAIPlayer::_minMax(clsBoard<char> *currentBoard, int depth,
                                 bool isMax, int alpha, int beta) const {
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

  vector<pair<int, int>> vValidPositions = {
    {0, 2},
    {1, 1}, {1, 2}, {1, 3},
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}
  };

  if (isMax) {
    int maxScore = -1e9;
    for (auto pos : vValidPositions) {
      int x = pos.first;
      int y = pos.second;

      if (currentBoard->getCell(x, y) == '.') {
        clsMove<char> move(x, y, getSymbol());
        currentBoard->updateBoard(&move);

        int score = _minMax(currentBoard, depth + 1, false, alpha, beta);
        maxScore = max(maxScore, score);

        // Alpha-beta pruning
        alpha = max(alpha, score);
        if (beta <= alpha) {
          clsMove<char> undoMove(x, y, 0);
          currentBoard->updateBoard(&undoMove);
          break;
        }

        clsMove<char> undoMove(x, y, 0);
        currentBoard->updateBoard(&undoMove);
      }
    }
    return maxScore;
  } else {
    int minScore = 1e9;
    for (auto pos : vValidPositions) {
      int x = pos.first;
      int y = pos.second;

      if (currentBoard->getCell(x, y) == '.') {
        clsMove<char> move(x, y, humanSymbol);
        currentBoard->updateBoard(&move);

        int score = _minMax(currentBoard, depth + 1, true, alpha, beta);
        minScore = min(minScore, score);

        beta = min(beta, score);
        if (beta <= alpha) {
          clsMove<char> undoMove(x, y, 0);
          currentBoard->updateBoard(&undoMove);
          break;
        }

        clsMove<char> undoMove(x, y, 0);
        currentBoard->updateBoard(&undoMove);
      }
    }
    return minScore;
  }
}

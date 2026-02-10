#include "clsFourByFourAIPlayer.h"
#include "clsFourByFourXOUI.h"

string directions = "UDLR";
string inverseDirection = "DURL";

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

clsFourByFourAIPlayer::clsFourByFourAIPlayer(string name, char symbol)
    : clsPlayer<char>(name, symbol, enPlayerType::COMPUTER) {}

clsMove<char> *clsFourByFourAIPlayer::getBestMove() const {
  clsFourByFourBoard *testBoard = new clsFourByFourBoard();
  *testBoard = *(dynamic_cast<clsFourByFourBoard *>(getBoardPtr()));

  clsMove<char> *bestMove = new clsMove<char>(-1, -1, getSymbol());
  int bestScore = -1e5;
  for (int i = 0; i < testBoard->getRows(); ++i)
    for (int j = 0; j < testBoard->getColumns(); ++j) {

      if (testBoard->getCell(i, j) == getSymbol()) {
        for (int u = 0; u < directions.size(); ++u) {
          if (clsFourByFourUI::validDirection(i, j, directions[u], testBoard)) {
            clsMove<char> currentMove(i, j, directions[u]);
            testBoard->updateBoard(&currentMove);

            int score = _minMax(testBoard, false, 0, -1e5, 1e5);

            clsMove<char> undoMove(i + dx[u], j + dy[u], inverseDirection[u]);
            testBoard->updateBoard(&undoMove);

            if (score > bestScore) {
              bestScore = score;
              delete bestMove;
              bestMove = new clsMove<char>(i, j, directions[u]);
            }
          }
        }
      }
    }

  delete testBoard;
  return bestMove;
}

int clsFourByFourAIPlayer::_minMax(clsBoard<char> *currentBoard, bool isMax,
                                   int depth, int alpha, int beta) const {
  // base case
  char humanSymbol = (getSymbol() == 'X') ? 'O' : 'X';
  clsPlayer<char> AIPlayer("AI", getSymbol(), enPlayerType::COMPUTER);
  AIPlayer.setBoardPtr(currentBoard);
  clsPlayer<char> humanPlayer("human", humanSymbol, enPlayerType::HUMAN);
  humanPlayer.setBoardPtr(currentBoard);

  if (currentBoard->isWin(&AIPlayer)) {
    return 10 + (1000 - depth);
  }
  if (currentBoard->isWin(&humanPlayer)) {
    return -10 - (1000 + depth);
  }

  if (depth > 9)
    return 0;

  // transition
  if (isMax) {
    int maxScore = (int)-1e5;

    for (int i = 0; i < currentBoard->getRows(); ++i)
      for (int j = 0; j < currentBoard->getColumns(); ++j) {

        if (currentBoard->getCell(i, j) == getSymbol()) {
          for (int u = 0; u < directions.size(); ++u) {
            if (clsFourByFourUI::validDirection(i, j, directions[u],
                                                currentBoard)) {
              clsMove<char> currentMove(i, j, directions[u]);
              currentBoard->updateBoard(&currentMove);

              int score = _minMax(currentBoard, false, depth + 1, alpha, beta);

              clsMove<char> undoMove(i + dx[u], j + dy[u], inverseDirection[u]);
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
    int minScore = (int)1e5;

    for (int i = 0; i < currentBoard->getRows(); ++i)
      for (int j = 0; j < currentBoard->getColumns(); ++j) {

        if (currentBoard->getCell(i, j) == humanSymbol) {
          for (int u = 0; u < directions.size(); ++u) {
            if (clsFourByFourUI::validDirection(i, j, directions[u],
                                                currentBoard)) {
              clsMove<char> currentMove(i, j, directions[u]);
              currentBoard->updateBoard(&currentMove);

              int score = _minMax(currentBoard, true, depth + 1, alpha, beta);

              clsMove<char> undoMove(i + dx[u], j + dy[u], inverseDirection[u]);
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
#include "clsSUSAIPlayer.h"

clsSUSAIPlayer::clsSUSAIPlayer(string name, char symbol)
    : clsPlayer<char>(name, symbol, enPlayerType::COMPUTER){};

clsMove<char> *clsSUSAIPlayer::getBestMove() {

  clsSUSBoard *testBoard = new clsSUSBoard();
  *testBoard = *(dynamic_cast<clsSUSBoard *>(getBoardPtr()));

  int bestScore = -1e5;
  clsMove<char> *bestMove = new clsMove<char>(-1, -1, getSymbol());

  for (int i = 0; i < testBoard->getRows(); ++i)
    for (int j = 0; j < testBoard->getColumns(); ++j) {

      if (testBoard->getCell(i, j) == '.') {

        clsMove<char> currentMove(i, j, getSymbol());
        testBoard->updateBoard(&currentMove);

        int score = _minMax(testBoard, false);

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

int clsSUSAIPlayer::_minMax(clsSUSBoard *currentBoard, bool isMax) {
  // base case
  char humanSymbol = (getSymbol() == 'S') ? 'U' : 'S';
  clsPlayer<char> AIPlayer("AI", getSymbol(), enPlayerType::COMPUTER);
  clsPlayer<char> humanPlayer("human", humanSymbol, enPlayerType::HUMAN);

  if (currentBoard->gameIsOver(&AIPlayer)) {

    pair<int, int> scores = currentBoard->calculatePlayersScore();

    if (currentBoard->isWin(&AIPlayer)) {

      if (getSymbol() == 'U')
        return scores.first - scores.second;
      else
        return scores.second - scores.first;
    }
    if (currentBoard->isWin(&humanPlayer)) {
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

    for (int i = 0; i < currentBoard->getRows(); ++i)
      for (int j = 0; j < currentBoard->getColumns(); ++j) {

        if (currentBoard->getCell(i, j) == '.') {

          clsMove<char> currentMove(i, j, getSymbol());
          currentBoard->updateBoard(&currentMove);

          int score = _minMax(currentBoard, false);

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

          int score = _minMax(currentBoard, true);

          clsMove<char> undoMove(i, j, 0);
          currentBoard->updateBoard(&undoMove);

          minScore = min(score, minScore);
        }
      }

    return minScore;
  }
}
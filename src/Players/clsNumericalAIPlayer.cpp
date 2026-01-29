#include "clsNumericalAIPlayer.h"

clsNumericalAIPlayer::clsNumericalAIPlayer(string name, int symbol)
    : clsPlayer<int>(name, symbol, enPlayerType::COMPUTER){};

clsMove<int> *clsNumericalAIPlayer::getBestMove() {

  clsNumericalBoard *testBoard = new clsNumericalBoard();
  *testBoard = *(dynamic_cast<clsNumericalBoard *>(getBoardPtr()));

  int numType = getSymbol();

  vector<int> choices;
  int symbolIndex;
  if (getSymbol() % 2) {
    for (auto &i : testBoard->sAvailableOddNumbers)
      choices.push_back(i);
  } else {
    for (auto &i : testBoard->sAvailableEvenNumbers)
      choices.push_back(i);
  }

  clsMove<int> *bestMove = new clsMove<int>(0, 0, numType);
  int bestScore = -1e5;

  for (int i = 0; i < testBoard->getRows(); ++i)
    for (int j = 0; j < testBoard->getColumns(); ++j) {
      if (testBoard->getCell(i, j) == 0) {

        for (int num : choices) {
          clsMove<int> currentMove(i, j, num);
          testBoard->updateBoard(&currentMove);

          (getSymbol() % 2) ? testBoard->sAvailableOddNumbers.erase(num)
                            : testBoard->sAvailableEvenNumbers.erase(num);

          int score = _minMax(testBoard, 0, bestScore, 1e5, false);

          clsMove<int> undoMove(i, j, 0);
          testBoard->updateBoard(&undoMove);

          (getSymbol() % 2) ? testBoard->sAvailableOddNumbers.insert(num)
                            : testBoard->sAvailableEvenNumbers.insert(num);

          if (score > bestScore) {
            bestScore = score;
            delete bestMove;
            bestMove = new clsMove<int>(i, j, num);
          }
        }
      }
    }
  (getSymbol() % 2)
      ? testBoard->sAvailableOddNumbers.erase(bestMove->getSymbol())
      : testBoard->sAvailableEvenNumbers.erase(bestMove->getSymbol());
  delete testBoard;
  return bestMove;
}

int clsNumericalAIPlayer::_minMax(clsNumericalBoard *currentBoard, int depth,
                                  int alpha, int beta, bool isMax) {
  // base case

  clsPlayer<int> tempPlayer("temp", 0, enPlayerType::HUMAN);

  if (currentBoard->isWin(&tempPlayer)) {

    if (isMax) {
      return -10 - (100 - depth);
    } else {
      return 10 + (100 - depth);
    }
  }

  if (currentBoard->isDraw(&tempPlayer)) {
    return 0;
  }

  if (depth > 8)
    return 0;

  // transition
  int humanType = (getSymbol() % 2 == 0) ? 1 : 0;

  if (isMax) {
    int maxScore = -1e5;

    vector<int> choices;
    int symbolIndex;
    if (getSymbol() % 2) {
      for (auto &i : currentBoard->sAvailableOddNumbers)
        choices.push_back(i);
    } else {
      for (auto &i : currentBoard->sAvailableEvenNumbers)
        choices.push_back(i);
    }

    for (int i = 0; i < currentBoard->getRows(); ++i)
      for (int j = 0; j < currentBoard->getColumns(); ++j) {
        if (currentBoard->getCell(i, j) == 0) {

          for (int num : choices) {
            clsMove<int> currentMove(i, j, num);
            currentBoard->updateBoard(&currentMove);

            (getSymbol() % 2) ? currentBoard->sAvailableOddNumbers.erase(num)
                              : currentBoard->sAvailableEvenNumbers.erase(num);

            int score = _minMax(currentBoard, depth + 1, alpha, beta, false);

            clsMove<int> undoMove(i, j, 0);
            currentBoard->updateBoard(&undoMove);

            (getSymbol() % 2) ? currentBoard->sAvailableOddNumbers.insert(num)
                              : currentBoard->sAvailableEvenNumbers.insert(num);

            maxScore = max(maxScore, score);

            alpha = max(alpha, score);

            if (alpha >= beta)
              break;
          }
        }
      }

    return maxScore;
  }

  else {
    int minScore = 1e5;

    vector<int> choices;
    int symbolIndex;
    if (humanType % 2) {
      for (auto &i : currentBoard->sAvailableOddNumbers)
        choices.push_back(i);
    } else {
      for (auto &i : currentBoard->sAvailableEvenNumbers)
        choices.push_back(i);
    }

    for (int i = 0; i < currentBoard->getRows(); ++i)
      for (int j = 0; j < currentBoard->getColumns(); ++j) {
        if (currentBoard->getCell(i, j) == 0) {

          for (int num : choices) {
            clsMove<int> currentMove(i, j, num);
            currentBoard->updateBoard(&currentMove);

            (humanType % 2) ? currentBoard->sAvailableOddNumbers.erase(num)
                            : currentBoard->sAvailableEvenNumbers.erase(num);

            int score = _minMax(currentBoard, depth + 1, alpha, beta, true);

            clsMove<int> undoMove(i, j, 0);
            currentBoard->updateBoard(&undoMove);
            (humanType % 2) ? currentBoard->sAvailableOddNumbers.insert(num)
                            : currentBoard->sAvailableEvenNumbers.insert(num);

            minScore = min(minScore, score);

            beta = min(beta, score);

            if (alpha >= beta)
              break;
          }
        }
      }

    return minScore;
  }
}
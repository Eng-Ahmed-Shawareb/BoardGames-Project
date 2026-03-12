#include "clsFiveByFiveAIPlayer.h"
#include <iostream>

using namespace std;

clsFiveByFiveAIPlayer::clsFiveByFiveAIPlayer(string name, char symbol)
    : clsPlayer<char>(name, symbol, enPlayerType::COMPUTER) {}

int clsFiveByFiveAIPlayer::evaluateBoard(clsBoard<char> *currentBoard) const {
  // Instead of dynamically casting to get private members, we count on the grid cells via getCell.
  int myCount = 0;
  int oppCount = 0;
  char mySymbol = getSymbol();
  char oppSymbol = (mySymbol == 'X') ? 'O' : 'X';
  
  auto check3 = [&](int r1, int c1, int r2, int c2, int r3, int c3) {
      char v1 = currentBoard->getCell(r1, c1);
      char v2 = currentBoard->getCell(r2, c2);
      char v3 = currentBoard->getCell(r3, c3);
      if (v1 == v2 && v2 == v3) {
          if (v1 == mySymbol) myCount++;
          else if (v1 == oppSymbol) oppCount++;
      }
  };

  // horizontal
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 3; c++) {
      check3(r, c, r, c+1, r, c+2);
    }
  }
  // vertical
  for (int c = 0; c < 5; c++) {
    for (int r = 0; r < 3; r++) {
      check3(r, c, r+1, c, r+2, c);
    }
  }
  // diagonal (top-left to bottom-right)
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      check3(r, c, r+1, c+1, r+2, c+2);
    }
  }
  // diagonal (top-right to bottom-left)
  for (int r = 0; r < 3; r++) {
    for (int c = 2; c < 5; c++) {
      check3(r, c, r+1, c-1, r+2, c-2);
    }
  }

  // Multiply by 10 for heuristic strength
  return (myCount - oppCount) * 10;
}

clsMove<char> *clsFiveByFiveAIPlayer::getBestMove() const {
  clsFiveByFiveBoard *testBoard = new clsFiveByFiveBoard();
  *testBoard = *(dynamic_cast<clsFiveByFiveBoard *>(getBoardPtr()));

  clsMove<char> *bestMove = new clsMove<char>(-1, -1, getSymbol());
  int bestScore = -1e5;
  for (int i = 0; i < testBoard->getRows(); ++i)
    for (int j = 0; j < testBoard->getColumns(); ++j) {

      if (testBoard->getCell(i, j) == '.') {

        clsMove<char> currentMove(i, j, getSymbol());
        testBoard->updateBoard(&currentMove);

        int score = _minMax(testBoard, false, 0, -1e5, 1e5);

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

int clsFiveByFiveAIPlayer::_minMax(clsBoard<char> *currentBoard, bool isMax,
                                   int depth, int alpha, int beta) const {
  char humanSymbol = (getSymbol() == 'X') ? 'O' : 'X';

  // In 5x5, game strictly ends at 24 moves. If game over, evaluate terminal state exactly.
  if (currentBoard->gameIsOver(nullptr)) {
      return evaluateBoard(currentBoard);
  }

  // Depth Limit Check
  if (depth >= 5) {
      return evaluateBoard(currentBoard);
  }

  // transition
  if (isMax) {
    int maxScore = -1e5;

    for (int i = 0; i < currentBoard->getRows(); ++i)
      for (int j = 0; j < currentBoard->getColumns(); ++j) {
        if (currentBoard->getCell(i, j) == '.') {
          clsMove<char> currentMove(i, j, getSymbol());
          currentBoard->updateBoard(&currentMove);
          
          int score = _minMax(currentBoard, false, depth + 1, alpha, beta);
          
          clsMove<char> undoMove(i, j, 0);
          currentBoard->updateBoard(&undoMove);
          
          maxScore = max(score, maxScore);
          alpha = max(alpha, score);
          
          if (alpha >= beta)
              return maxScore;
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
          
          int score = _minMax(currentBoard, true, depth + 1, alpha, beta);
          
          clsMove<char> undoMove(i, j, 0);
          currentBoard->updateBoard(&undoMove);
          
          minScore = min(score, minScore);
          beta = min(beta, score);

          if (alpha >= beta)
              return minScore;          
        }
      }
    return minScore;
  }
}

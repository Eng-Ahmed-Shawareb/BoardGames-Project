#include "clsFiveByFiveBoard.h"
#include "BoardGame_Classes.h"
#include <iostream>

clsFiveByFiveBoard::clsFiveByFiveBoard() : clsBoard(5, 5) {
  for (auto &row : vBoard)
    for (auto &cell : row)
      cell = _blankSymbol;
}

bool clsFiveByFiveBoard::updateBoard(clsMove<char> *move) {
  int x = move->getX();
  int y = move->getY();
  char mark = move->getSymbol();

  // Validate move and apply if valid
  if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
      (vBoard[x][y] == _blankSymbol || mark == 0)) {

    if (mark == 0) {
      nMoves--;
      vBoard[x][y] = _blankSymbol;
    } else {
      nMoves++;
      vBoard[x][y] = toupper(mark);
    }
    return true;
  }
  return false;
}

int clsFiveByFiveBoard::count3InARow(char symbol) {
  int count = 0;
  // horizontal
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 3; c++) {
      if (vBoard[r][c] == symbol && vBoard[r][c+1] == symbol && vBoard[r][c+2] == symbol) {
        count++;
      }
    }
  }
  // vertical
  for (int c = 0; c < 5; c++) {
    for (int r = 0; r < 3; r++) {
      if (vBoard[r][c] == symbol && vBoard[r+1][c] == symbol && vBoard[r+2][c] == symbol) {
        count++;
      }
    }
  }
  // diagonal (top-left to bottom-right)
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      if (vBoard[r][c] == symbol && vBoard[r+1][c+1] == symbol && vBoard[r+2][c+2] == symbol) {
        count++;
      }
    }
  }
  // diagonal (top-right to bottom-left)
  for (int r = 0; r < 3; r++) {
    for (int c = 2; c < 5; c++) {
      if (vBoard[r][c] == symbol && vBoard[r+1][c-1] == symbol && vBoard[r+2][c-2] == symbol) {
        count++;
      }
    }
  }
  return count;
}

bool clsFiveByFiveBoard::isWin(clsPlayer<char> *player) {
  if (nMoves < 24) return false;
  
  char symbol = player->getSymbol();
  char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
  
  return count3InARow(symbol) > count3InARow(opponentSymbol);
}

bool clsFiveByFiveBoard::isLose(clsPlayer<char> *player) {
  if (nMoves < 24) return false;
  
  char symbol = player->getSymbol();
  char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
  
  return count3InARow(symbol) < count3InARow(opponentSymbol);
}

bool clsFiveByFiveBoard::isDraw(clsPlayer<char> *player) {
  if (nMoves < 24) return false;
  
  char symbol = player->getSymbol();
  char opponentSymbol = (symbol == 'X') ? 'O' : 'X';
  
  return count3InARow(symbol) == count3InARow(opponentSymbol);
}

bool clsFiveByFiveBoard::gameIsOver(clsPlayer<char> *player) {
  return nMoves >= 24;
}

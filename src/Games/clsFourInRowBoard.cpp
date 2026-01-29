#include "clsFourInRowBoard.h"
#include "BoardGame_Classes.h"
#include <iostream>

using namespace std;

clsFourInRowBoard::clsFourInRowBoard() : clsBoard(6, 7) {
  for (auto &row : vBoard) {
    for (auto &element : row) {
      element = _blankSymbol;
    }
  }
}

bool clsFourInRowBoard::isValidMove(int y) {
  if (y < 0 || y > 6)
    return false;

  for (int i = 0; i < 6; ++i) {
    if (vBoard[i][y] == _blankSymbol)
      return true;
  }
  return false;
}

bool clsFourInRowBoard::updateBoard(clsMove<char> *move) {
  int x = 0;
  int y = move->getY();
  char symbol = move->getSymbol();

  if (symbol == 0) {
    for (int i = 0; i < rows; ++i) {
      if (vBoard[i][y] != _blankSymbol) {
        vBoard[i][y] = _blankSymbol;
        nMoves--;
        return true;
      }
    }
  }

  if (isValidMove(y)) {
    for (int i = 5; i >= 0; --i) {
      if (vBoard[i][y] == _blankSymbol) {
        vBoard[i][y] = toupper(symbol);
        nMoves++;
        return true;
      }
    }
  }
  return false;
}

bool clsFourInRowBoard::isWin(clsPlayer<char> *player) {
  int rows = player->getBoardPtr()->getRows();
  int columns = player->getBoardPtr()->getColumns();
  char playerSymbol = player->getSymbol();
  string fourSymbol = "";
  for (int i = 0; i < 4; ++i) {
    fourSymbol += playerSymbol;
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (vBoard[i][j] == playerSymbol) {
        string s = "";
        for (int u = j; u < j + 4; ++u) {
          if (u < columns) {
            s += vBoard[i][u];
          }
        }
        if (s == fourSymbol)
          return true;
        s = "";
        for (int u = i; u >= i - 3; --u) {
          if (u >= 0) {
            s += vBoard[u][j];
          }
        }
        if (s == fourSymbol)
          return true;
        s = "";
        for (int u = i, v = j; u >= i - 3 && v < j + 4; --u, ++v) {
          if (u >= 0 && v < columns) {
            s += vBoard[u][v];
          }
        }
        if (s == fourSymbol)
          return true;
        s = "";
        for (int u = i, v = j; u >= i - 3 && v >= j - 3; --u, --v) {
          if (u >= 0 && v >= 0) {
            s += vBoard[u][v];
          }
        }
        if (s == fourSymbol)
          return true;
      }
    }
  }
  return false;
}

bool clsFourInRowBoard::isLose(clsPlayer<char> *player) { return false; }

bool clsFourInRowBoard::isDraw(clsPlayer<char> *player) {
  return (nMoves == 42);
}

bool clsFourInRowBoard::gameIsOver(clsPlayer<char> *player) { return false; }
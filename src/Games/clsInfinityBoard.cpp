#include "clsInfinityBoard.h"
#include "BoardGame_Classes.h"
#include <iostream>

clsInfinityBoard::clsInfinityBoard() : clsBoard(3, 3) {
  for (auto &row : vBoard)
    for (auto &cell : row)
      cell = _blankSymbol;
  vOrderOfMoves.assign(3, vector<int>(3, 0));
}

bool clsInfinityBoard::updateBoard(clsMove<char> *move) {
  int x = move->getX();
  int y = move->getY();
  char symbol = move->getSymbol();

  // Validate move and apply if valid
  if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
      (vBoard[x][y] == _blankSymbol || symbol == 0)) {
    nMoves++;
    vBoard[x][y] = toupper(symbol);
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) {
        if (vBoard[i][j] == symbol) {
          ++vOrderOfMoves[i][j];
          if (vOrderOfMoves[i][j] == 4) {
            vBoard[i][j] = _blankSymbol;
            vOrderOfMoves[i][j] = 0;
            --nMoves;
          }
        }
      }
    return true;
  }
  return false;
}

bool clsInfinityBoard::isWin(clsPlayer<char> *player) {
  const char symbol = player->getSymbol();

  auto allEqual = [&](char a, char b, char c) {
    return a == b && b == c && a != _blankSymbol;
  };

  for (int i = 0; i < rows; ++i) {
    if ((allEqual(vBoard[i][0], vBoard[i][1], vBoard[i][2]) &&
         vBoard[i][0] == symbol) ||
        (allEqual(vBoard[0][i], vBoard[1][i], vBoard[2][i]) &&
         vBoard[0][i] == symbol))
      return true;
  }
  if ((allEqual(vBoard[0][0], vBoard[1][1], vBoard[2][2]) &&
       vBoard[1][1] == symbol) ||
      (allEqual(vBoard[0][2], vBoard[1][1], vBoard[2][0]) &&
       vBoard[1][1] == symbol))
    return true;

  return false;
}

bool clsInfinityBoard::isDraw(clsPlayer<char> *player) { return false; }

bool clsInfinityBoard::isLose(clsPlayer<char> *player) {
  char symbol;
  if (player->getSymbol() == 'X')
    symbol = 'O';
  else
    symbol = 'X';

  auto allEqual = [&](char a, char b, char c) {
    return a == b && b == c && a != _blankSymbol;
  };

  for (int i = 0; i < rows; ++i) {
    if ((allEqual(vBoard[i][0], vBoard[i][1], vBoard[i][2]) &&
         vBoard[i][0] == symbol) ||
        (allEqual(vBoard[0][i], vBoard[1][i], vBoard[2][i]) &&
         vBoard[0][i] == symbol))
      return true;
  }
  if ((allEqual(vBoard[0][0], vBoard[1][1], vBoard[2][2]) &&
       vBoard[1][1] == symbol) ||
      (allEqual(vBoard[0][2], vBoard[1][1], vBoard[2][0]) &&
       vBoard[1][1] == symbol))
    return true;

  return false;
}

bool clsInfinityBoard::gameIsOver(clsPlayer<char> *player) {
  return isWin(player) || isDraw(player);
}

#include "clsXOBoard.h"
#include "BoardGame_Classes.h"
#include <iostream>

clsXOBoard::clsXOBoard() : clsBoard(3, 3) {
  for (auto &row : vBoard)
    for (auto &cell : row)
      cell = _blankSymbol;
}

bool clsXOBoard::updateBoard(clsMove<char> *move) {
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

bool clsXOBoard::isWin(clsPlayer<char> *player) {
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

bool clsXOBoard::isDraw(clsPlayer<char> *player) {
  return (nMoves == 9 && !isWin(player));
}

bool clsXOBoard::isLose(clsPlayer<char> *player) {
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

bool clsXOBoard::gameIsOver(clsPlayer<char> *player) {
  return isWin(player) || isDraw(player);
}

#include "clsNumericalBoard.h"
#include <iostream>
using namespace std;

clsNumericalBoard::clsNumericalBoard() : clsBoard(3, 3) {
  for (auto &row : vBoard) {
    for (auto &element : row) {
      element = _blankSymbol;
    }
  }
  sAvailableEvenNumbers = {2, 4, 6, 8};
  sAvailableOddNumbers = {1, 3, 5, 7, 9};
};

bool clsNumericalBoard::updateBoard(clsMove<int> *move) {
  int x = move->getX();
  int y = move->getY();
  int symbol = move->getSymbol();

  if (symbol == 0 && vBoard[x][y] != _blankSymbol) {
    nMoves--;
    vBoard[x][y] = _blankSymbol;
    return true;
  }

  if (x < 0 || y < 0 || x >= rows || y >= columns ||
      vBoard[x][y] != _blankSymbol)
    return false;
  else {
    nMoves++;
    vBoard[x][y] = symbol;
    return true;
  }
  return false;
}

bool clsNumericalBoard::isWin(clsPlayer<int> *player) {
  for (int i = 0; i < rows; ++i) {

    int sum = vBoard[i][0] + vBoard[i][1] + vBoard[i][2];

    if (vBoard[i][0] == 0 || vBoard[i][1] == 0 || vBoard[i][2] == 0)
      sum = 0;

    if (sum == 15)
      return true;
  }
  for (int i = 0; i < columns; ++i) {

    int sum = vBoard[0][i] + vBoard[1][i] + vBoard[2][i];

    if (vBoard[0][i] == 0 || vBoard[1][i] == 0 || vBoard[2][i] == 0)
      sum = 0;

    if (sum == 15)
      return true;
  }
  int sumDiagonal1 = vBoard[0][0] + vBoard[1][1] + vBoard[2][2];

  if (vBoard[0][0] == 0 || vBoard[1][1] == 0 || vBoard[2][2] == 0)
    sumDiagonal1 = 0;

  int sumDiagonal2 = vBoard[0][2] + vBoard[1][1] + vBoard[2][0];

  if (vBoard[0][2] == 0 || vBoard[1][1] == 0 || vBoard[2][0] == 0)
    sumDiagonal2 = 0;

  if (sumDiagonal1 == 15 || sumDiagonal2 == 15)
    return true;

  return false;
}

bool clsNumericalBoard::isDraw(clsPlayer<int> *player) {
  return (nMoves == 9 && !isWin(player));
}

bool clsNumericalBoard::gameIsOver(clsPlayer<int> *player) {
  return (isWin(player) || isDraw(player));
}

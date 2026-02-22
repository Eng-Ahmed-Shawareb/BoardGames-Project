#include "clsPyramidBoard.h"
#include "BoardGame_Classes.h"
#include <iostream>

using namespace std;

clsPyramidBoard::clsPyramidBoard() : clsBoard(3, 5) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 5; ++j) {
      vBoard[i][j] = _invalidSymbol;
    }
  }
  
  vBoard[0][2] = _blankSymbol;
  
  vBoard[1][1] = _blankSymbol;
  vBoard[1][2] = _blankSymbol;
  vBoard[1][3] = _blankSymbol;

  vBoard[2][0] = _blankSymbol;
  vBoard[2][1] = _blankSymbol;
  vBoard[2][2] = _blankSymbol;
  vBoard[2][3] = _blankSymbol;
  vBoard[2][4] = _blankSymbol;
}

bool clsPyramidBoard::isValidPosition(int x, int y) const {
  if (x < 0 || x >= 3 || y < 0 || y >= 5)
    return false;
  
  if (x == 0) return y == 2;
  if (x == 1) return y >= 1 && y <= 3;
  if (x == 2) return y >= 0 && y <= 4;
  
  return false;
}

bool clsPyramidBoard::updateBoard(clsMove<char> *move) {
  int x = move->getX();
  int y = move->getY();
  char mark = move->getSymbol();
  
  if (mark == 0) {
    if (isValidPosition(x, y) && vBoard[x][y] != _blankSymbol) {
      vBoard[x][y] = _blankSymbol;
      nMoves--;
      return true;
    }
    return false;
  }

  if (!isValidPosition(x, y) || vBoard[x][y] != _blankSymbol) {
    return false;
  }
  
  vBoard[x][y] = mark;
  nMoves++;
  return true;
}

bool clsPyramidBoard::isWin(clsPlayer<char> *player) {
  const char symbol = player->getSymbol();
  
  auto allEqual = [&](char a, char b, char c) {
    return a == symbol && b == symbol && c == symbol;
  };
  
  if (allEqual(vBoard[1][1], vBoard[1][2], vBoard[1][3]))
    return true;
  
  if (allEqual(vBoard[2][0], vBoard[2][1], vBoard[2][2]))
    return true;
  if (allEqual(vBoard[2][1], vBoard[2][2], vBoard[2][3]))
    return true;
  if (allEqual(vBoard[2][2], vBoard[2][3], vBoard[2][4]))
    return true;
  
  if (allEqual(vBoard[0][2], vBoard[1][3], vBoard[2][4]))
    return true;
  

  if (allEqual(vBoard[0][2], vBoard[1][1], vBoard[2][0]))
    return true;
  
  if (allEqual(vBoard[0][2], vBoard[1][2], vBoard[2][2]))
    return true;
  
  return false;
}

bool clsPyramidBoard::isLose(clsPlayer<char> *player) {
  clsPlayer<char> otherPlayer("other" , (player->getSymbol() == 'X' ? 'O' : 'X') , enPlayerType::COMPUTER);
  return isWin(&otherPlayer);
}

bool clsPyramidBoard::isDraw(clsPlayer<char> *player) {
  return nMoves == 9;
}

bool clsPyramidBoard::gameIsOver(clsPlayer<char> *player) {
  return (isWin(player) || isDraw(player));
}

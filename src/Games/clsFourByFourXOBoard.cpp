#include "clsFourByFourXOBoard.h"

clsFourByFourBoard::clsFourByFourBoard() : clsBoard(4, 4) {
  for (auto &row : vBoard) {
    for (auto &element : row) {
      element = _blankSymbol;
    }
  }
  for (int i = 0; i < 4; ++i) {
    if (i % 2) {
      vBoard[0][i] = 'X';
      vBoard[3][i] = 'X';
    } else {
      vBoard[0][i] = 'O';
      vBoard[3][i] = 'O';
    }
  }
}

bool clsFourByFourBoard::updateBoard(clsMove<char> *move) {
  int x = move->getX();
  int y = move->getY();
  char moveSymbol = move->getSymbol();
  char playerSymbol = vBoard[x][y];

  vBoard[x][y] = _blankSymbol;

  if (moveSymbol == 'U')
    --x;
  else if (moveSymbol == 'D')
    ++x;
  else if (moveSymbol == 'L')
    --y;
  else
    ++y;

  vBoard[x][y] = playerSymbol;

  return true;
}

bool clsFourByFourBoard::isWin(clsPlayer<char> *player) {
  int rows = player->getBoardPtr()->getRows();
  int columns = player->getBoardPtr()->getColumns();
  char playerSymbol = player->getSymbol();
  string threeSymbol = "";
  for (int i = 0; i < 3; ++i) {
    threeSymbol += playerSymbol;
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (vBoard[i][j] == playerSymbol) {
        string s = "";
        for (int u = j; u < j + 3; ++u) {
          if (u < columns) {
            s += vBoard[i][u];
          }
        }
        if (s == threeSymbol)
          return true;
        s = "";
        for (int u = i; u >= i - 2; --u) {
          if (u >= 0) {
            s += vBoard[u][j];
          }
        }
        if (s == threeSymbol)
          return true;
        s = "";
        for (int u = i, v = j; u >= i - 2 && v < j + 3; --u, ++v) {
          if (u >= 0 && v < columns) {
            s += vBoard[u][v];
          }
        }
        if (s == threeSymbol)
          return true;
        s = "";
        for (int u = i, v = j; u >= i - 2 && v >= j - 2; --u, --v) {
          if (u >= 0 && v >= 0) {
            s += vBoard[u][v];
          }
        }
        if (s == threeSymbol)
          return true;
      }
    }
  }
  return false;
}

bool clsFourByFourBoard::isLose(clsPlayer<char> *player) {
  clsPlayer<char> otherPlayer("other" , (player->getSymbol() == 'X') ? 'O' : 'X' , enPlayerType::HUMAN);
  otherPlayer.setBoardPtr(player->getBoardPtr());
  return isWin(&otherPlayer);
}

bool clsFourByFourBoard::isDraw(clsPlayer<char> *player) { return false; }

bool clsFourByFourBoard::gameIsOver(clsPlayer<char> *player) {
  clsPlayer<char> otherPlayer("other" , (player->getSymbol() == 'X') ? 'O' : 'X' , enPlayerType::HUMAN);
  otherPlayer.setBoardPtr(player->getBoardPtr());
  return (isWin(player) || isWin(&otherPlayer));
}
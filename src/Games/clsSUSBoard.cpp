#include "clsSUSBoard.h"
#include "BoardGame_Classes.h"
#include <iostream>

clsSUSBoard::clsSUSBoard() : clsBoard(3, 3), _vOrderOfMoves(3, vector<int>(3)) {
  for (auto &row : vBoard) {
    for (auto &element : row) {
      element = _blankSymbol;
    }
  }
  for (auto &row : _vOrderOfMoves)
    for (auto &element : row) {
      element = 0;
    }
}

pair<int, int> clsSUSBoard::calculatePlayersScore() {
  pair<int, int> score = {0, 0};

  for (int i = 0; i < 3; ++i) {
    string s = "";
    for (int j = 0; j < 3; ++j) {
      s += vBoard[i][j];
    }
    if (s == "SUS") {
      (_vOrderOfMoves[i][1] > _vOrderOfMoves[i][0] &&
       _vOrderOfMoves[i][1] > _vOrderOfMoves[i][2])
          ? score.first++
          : score.second++;
    }
  }
  for (int i = 0; i < 3; ++i) {
    string s = "";
    for (int j = 0; j < 3; ++j) {
      s += vBoard[j][i];
    }
    if (s == "SUS") {
      (_vOrderOfMoves[1][i] > _vOrderOfMoves[0][i] &&
       _vOrderOfMoves[1][i] > _vOrderOfMoves[2][i])
          ? score.first++
          : score.second++;
    }
  }
  string diagonal1 = "", diagonal2 = "";
  for (int i = 0; i < 3; ++i) {
    diagonal1 += vBoard[i][i];
    diagonal2 += vBoard[i][2 - i];
  }
  if (diagonal1 == "SUS") {
    (_vOrderOfMoves[1][1] > _vOrderOfMoves[0][0] &&
     _vOrderOfMoves[1][1] > _vOrderOfMoves[2][2])
        ? score.first++
        : score.second++;
  }
  if (diagonal2 == "SUS") {
    (_vOrderOfMoves[1][1] > _vOrderOfMoves[2][0] &&
     _vOrderOfMoves[1][1] > _vOrderOfMoves[2][0])
        ? score.first++
        : score.second++;
  }

  return score;
}

bool clsSUSBoard::isValidMove(int x, int y) {
  return (x >= 0 && x < rows && y >= 0 && y < columns);
}

bool clsSUSBoard::isWin(clsPlayer<char> *player) {
  if (nMoves < 9)
    return false;
  pair<int, int> playersScore = calculatePlayersScore();
  char symbol = player->getSymbol();

  if (toupper(symbol) == 'S') {
    if (playersScore.second > playersScore.first)
      return true;
    else
      return false;
  }
  if (toupper(symbol) == 'U') {
    if (playersScore.second < playersScore.first)
      return true;
    else
      return false;
  }
}

bool clsSUSBoard::isLose(clsPlayer<char> *player) {
  if (nMoves < 9)
    return false;
  pair<int, int> playersScore = calculatePlayersScore();
  char symbol = player->getSymbol();

  if (toupper(symbol) == 'S') {
    if (playersScore.second < playersScore.first)
      return true;
    else
      return false;
  }
  if (toupper(symbol) == 'U') {
    if (playersScore.second > playersScore.first)
      return true;
    else
      return false;
  }
}

bool clsSUSBoard::gameIsOver(clsPlayer<char> *player) { return nMoves == 9; }

bool clsSUSBoard::isDraw(clsPlayer<char> *player) {
  if (nMoves < 9)
    return false;
  pair<int, int> playersScore = calculatePlayersScore();
  if (playersScore.first == playersScore.second)
    return true;
  else
    return false;
}

bool clsSUSBoard::updateBoard(clsMove<char> *move) {
  int x = move->getX();
  int y = move->getY();
  char symbol = move->getSymbol();

  if (isValidMove(x, y)) {
    if (symbol == 0) {
      nMoves--;
      vBoard[x][y] = _blankSymbol;
      _vOrderOfMoves[x][y] = 0;
    } else {
      if (vBoard[x][y] != _blankSymbol)
        return false;
      vBoard[x][y] = toupper(symbol);
      nMoves++;
      _vOrderOfMoves[x][y] = nMoves;
    }
    return true;
  }
  return false;
}
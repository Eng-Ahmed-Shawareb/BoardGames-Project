#include "clsSUSBoard.h"
#include "BoardGame_Classes.h"
#include <iostream>

clsSUSBoard::clsSUSBoard() : Board(3, 3), _vOrderOfMoves(3, vector<int>(3)) {
  for (auto &row : board) {
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
      s += board[i][j];
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
      s += board[j][i];
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
    diagonal1 += board[i][i];
    diagonal2 += board[i][2 - i];
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

bool clsSUSBoard::is_win(Player<char> *player) {
  if (n_moves < 9)
    return false;
  pair<int, int> playersScore = calculatePlayersScore();
  char symbol = player->get_symbol();

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

bool clsSUSBoard::is_lose(Player<char> *player) {
  if (n_moves < 9)
    return false;
  pair<int, int> playersScore = calculatePlayersScore();
  char symbol = player->get_symbol();

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

bool clsSUSBoard::game_is_over(Player<char> *player) { return n_moves == 9; }

bool clsSUSBoard::is_draw(Player<char> *player) {
  if (n_moves < 9)
    return false;
  pair<int, int> playersScore = calculatePlayersScore();
  if (playersScore.first == playersScore.second)
    return true;
  else
    return false;
}

bool clsSUSBoard::update_board(Move<char> *move) {
  int x = move->get_x();
  int y = move->get_y();
  char symbol = move->get_symbol();

  if (isValidMove(x, y)) {
    if (symbol == 0) {
      n_moves--;
      board[x][y] = _blankSymbol;
      _vOrderOfMoves[x][y] = 0;
    } else {
      if (board[x][y] != _blankSymbol)
        return false;
      board[x][y] = toupper(symbol);
      n_moves++;
      _vOrderOfMoves[x][y] = n_moves;
    }
    return true;
  }
  return false;
}
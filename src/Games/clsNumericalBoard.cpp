
#include "clsNumericalBoard.h"
#include <iostream>
using namespace std;

clsNumericalBoard::clsNumericalBoard() : Board(3, 3) {
  for (auto &row : board) {
    for (auto &element : row) {
      element = _blankSymbol;
    }
  }
  sAvailableEvenNumbers = {2, 4, 6, 8};
  sAvailableOddNumbers = {1, 3, 5, 7, 9};
};

bool clsNumericalBoard::update_board(Move<int> *move) {
  int x = move->get_x();
  int y = move->get_y();
  int symbol = move->get_symbol();

  if (symbol == 0 && board[x][y] != _blankSymbol) {
    n_moves--;
    board[x][y] = _blankSymbol;
    return true;
  }

  if (x < 0 || y < 0 || x >= rows || y >= columns ||
      board[x][y] != _blankSymbol)
    return false;
  else {
    n_moves++;
    board[x][y] = symbol;
    return true;
  }
  return false;
}

bool clsNumericalBoard::is_win(Player<int> *player) {
  for (int i = 0; i < rows; ++i) {

    int sum = board[i][0] + board[i][1] + board[i][2];

    if (board[i][0] == 0 || board[i][1] == 0 || board[i][2] == 0)
      sum = 0;

    if (sum == 15)
      return true;
  }
  for (int i = 0; i < columns; ++i) {

    int sum = board[0][i] + board[1][i] + board[2][i];

    if (board[0][i] == 0 || board[1][i] == 0 || board[2][i] == 0)
      sum = 0;

    if (sum == 15)
      return true;
  }
  int sumDiagonal1 = board[0][0] + board[1][1] + board[2][2];

  if (board[0][0] == 0 || board[1][1] == 0 || board[2][2] == 0)
    sumDiagonal1 = 0;

  int sumDiagonal2 = board[0][2] + board[1][1] + board[2][0];

  if (board[0][2] == 0 || board[1][1] == 0 || board[2][0] == 0)
    sumDiagonal2 = 0;

  if (sumDiagonal1 == 15 || sumDiagonal2 == 15)
    return true;

  return false;
}

bool clsNumericalBoard::is_draw(Player<int> *player) {
  return (n_moves == 9 && !is_win(player));
}

bool clsNumericalBoard::game_is_over(Player<int> *player) {
  return (is_win(player) || is_draw(player));
}

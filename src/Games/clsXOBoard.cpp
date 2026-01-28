#include "clsXOBoard.h"
#include "BoardGame_Classes.h"
#include <iostream>

clsXOBoard::clsXOBoard() : Board(3, 3) {
  for (auto &row : board)
    for (auto &cell : row)
      cell = _blankSymbol;
}

bool clsXOBoard::update_board(Move<char> *move) {
  int x = move->get_x();
  int y = move->get_y();
  char mark = move->get_symbol();

  // Validate move and apply if valid
  if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
      (board[x][y] == _blankSymbol || mark == 0)) {

    if (mark == 0) {
      n_moves--;
      board[x][y] = _blankSymbol;
    } else {
      n_moves++;
      board[x][y] = toupper(mark);
    }
    return true;
  }
  return false;
}

bool clsXOBoard::is_win(Player<char> *player) {
  const char symbol = player->get_symbol();

  auto allEqual = [&](char a, char b, char c) {
    return a == b && b == c && a != _blankSymbol;
  };

  for (int i = 0; i < rows; ++i) {
    if ((allEqual(board[i][0], board[i][1], board[i][2]) &&
         board[i][0] == symbol) ||
        (allEqual(board[0][i], board[1][i], board[2][i]) &&
         board[0][i] == symbol))
      return true;
  }
  if ((allEqual(board[0][0], board[1][1], board[2][2]) &&
       board[1][1] == symbol) ||
      (allEqual(board[0][2], board[1][1], board[2][0]) &&
       board[1][1] == symbol))
    return true;

  return false;
}

bool clsXOBoard::is_draw(Player<char> *player) {
  return (n_moves == 9 && !is_win(player));
}

bool clsXOBoard::is_lose(Player<char> *player) {
  char symbol;
  if (player->get_symbol() == 'X')
    symbol = 'O';
  else
    symbol = 'X';

  auto allEqual = [&](char a, char b, char c) {
    return a == b && b == c && a != _blankSymbol;
  };

  for (int i = 0; i < rows; ++i) {
    if ((allEqual(board[i][0], board[i][1], board[i][2]) &&
         board[i][0] == symbol) ||
        (allEqual(board[0][i], board[1][i], board[2][i]) &&
         board[0][i] == symbol))
      return true;
  }
  if ((allEqual(board[0][0], board[1][1], board[2][2]) &&
       board[1][1] == symbol) ||
      (allEqual(board[0][2], board[1][1], board[2][0]) &&
       board[1][1] == symbol))
    return true;

  return false;
}

bool clsXOBoard::game_is_over(Player<char> *player) {
  return is_win(player) || is_draw(player);
}

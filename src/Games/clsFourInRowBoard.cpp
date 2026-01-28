#include "clsFourInRowBoard.h"
#include "BoardGame_Classes.h"
#include <iostream>

using namespace std;

clsFourInRowBoard::clsFourInRowBoard() : Board(6, 7) {
  for (auto &row : board) {
    for (auto &element : row) {
      element = _blankSymbol;
    }
  }
}

bool clsFourInRowBoard::isValidMove(int y) {
  if (y < 0 || y > 6)
    return false;

  for (int i = 0; i < 6; ++i) {
    if (board[i][y] == _blankSymbol)
      return true;
  }
  return false;
}

bool clsFourInRowBoard::update_board(Move<char> *move) {
  int x = 0;
  int y = move->get_y();
  char symbol = move->get_symbol();

  if (symbol == 0) {
    for (int i = 0; i < rows; ++i) {
      if (board[i][y] != _blankSymbol) {
        board[i][y] = _blankSymbol;
        n_moves--;
        return true;
      }
    }
  }

  if (isValidMove(y)) {
    for (int i = 5; i >= 0; --i) {
      if (board[i][y] == _blankSymbol) {
        board[i][y] = toupper(symbol);
        n_moves++;
        return true;
      }
    }
  }
  return false;
}

bool clsFourInRowBoard::is_win(Player<char> *player) {
  int rows = player->get_board_ptr()->get_rows();
  int columns = player->get_board_ptr()->get_columns();
  char playerSymbol = player->get_symbol();
  string fourSymbol = "";
  for (int i = 0; i < 4; ++i) {
    fourSymbol += playerSymbol;
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (board[i][j] == playerSymbol) {
        string s = "";
        for (int u = j; u < j + 4; ++u) {
          if (u < columns) {
            s += board[i][u];
          }
        }
        if (s == fourSymbol)
          return true;
        s = "";
        for (int u = i; u >= i - 3; --u) {
          if (u >= 0) {
            s += board[u][j];
          }
        }
        if (s == fourSymbol)
          return true;
        s = "";
        for (int u = i, v = j; u >= i - 3 && v < j + 4; --u, ++v) {
          if (u >= 0 && v < columns) {
            s += board[u][v];
          }
        }
        if (s == fourSymbol)
          return true;
        s = "";
        for (int u = i, v = j; u >= i - 3 && v >= j - 3; --u, --v) {
          if (u >= 0 && v >= 0) {
            s += board[u][v];
          }
        }
        if (s == fourSymbol)
          return true;
      }
    }
  }
  return false;
}

bool clsFourInRowBoard::is_lose(Player<char> *player) { return false; }

bool clsFourInRowBoard::is_draw(Player<char> *player) { return (n_moves == 42); }

bool clsFourInRowBoard::game_is_over(Player<char> *player) { return false; }
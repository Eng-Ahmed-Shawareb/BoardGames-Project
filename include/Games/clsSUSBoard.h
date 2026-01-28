#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include "BoardGame_Classes.h"

class clsSUSBoard : public Board<char> {
private:
  char _blankSymbol = '.';
  vector<vector<int>> _vOrderOfMoves;

public:
  clsSUSBoard();

  pair<int, int> calculatePlayersScore();

  bool isValidMove(int x, int y);

  bool is_win(Player<char> *player) override;

  bool is_lose(Player<char> *player) override;

  bool game_is_over(Player<char> *player) override;

  bool is_draw(Player<char> *player) override;

  bool update_board(Move<char> *move) override;
};

#endif
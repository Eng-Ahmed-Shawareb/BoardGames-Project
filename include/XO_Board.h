#ifndef XO_BOARD_H
#define XO_BOARD_H

#include"BoardGame_Classes.h"

class X_O_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    X_O_Board();

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*);

    bool is_draw(Player<char>* player);
    
    bool game_is_over(Player<char>* player);
};

#endif
#ifndef MEMORY_GAME_BOARD_H
#define MEMORY_GAME_BOARD_H

#include"BoardGame_Classes.h"

class MemoryGame_Board : public Board<char>{

private:
    char blank_symbol = '.';
    vector<vector<char>>fact_board;

public:
    MemoryGame_Board();

    bool update_board(Move<char>* move);

    bool is_win(Player<char>* player);

    bool is_lose(Player<char>*) { return false; };

    bool is_draw(Player<char>* player);
    
    bool game_is_over(Player<char>* player);
};

#endif
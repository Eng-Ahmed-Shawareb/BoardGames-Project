#ifndef FOUR_IN_ROW_BOARD_H
#define FOUR_IN_ROW_BOARD_H

#include"BoardGame_Classes.h"

class FourInRow_Board : public Board<char>{
private : 
    char Blank_Symbol = '.';
public : 
    FourInRow_Board();

    bool valid_move( int y );

    bool update_board( Move<char>* move ) override;

    bool is_win( Player<char>* player ) override;

    bool is_lose( Player<char>* player ) override;

    bool is_draw( Player<char>* player ) override;

    bool game_is_over( Player<char>* player ) override;

};

#endif
#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include"BoardGame_Classes.h"

class SUS_Board : public Board<char>{
private :
    char Blank_Symbol = '.';
    vector<vector<int>>order_of_moves;
public : 
    SUS_Board();
    pair< int , int > calculate_players_score();
    bool valid_move( int x , int y );
    bool is_win( Player<char>* player ) override;
    bool is_lose( Player<char>* player ) override;
    bool game_is_over( Player<char>* player ) override;
    bool is_draw( Player<char>* player ) override;
    bool update_board( Move<char>* move ) override;
};

#endif
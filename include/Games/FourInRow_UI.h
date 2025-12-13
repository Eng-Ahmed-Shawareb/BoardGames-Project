#ifndef FOUR_IN_ROW_UI_H
#define FOUR_IN_ROW_UI_H

#include"BoardGame_Classes.h"

class FourInRow_UI : public UI<char>{
public : 
    FourInRow_UI();

    int min_max(Board<char>* current_board , bool is_max , int depth , int alpha , int beta , char AI_symbol , char human_symbol);

    Move<char>* get_AI_move(Player<char>* AI_player);

    Move<char>* get_move(Player<char>* player) override;

    Player<char>* create_player(string& name , char symbol , PlayerType type) override;

    Player<char>** setup_players() override;


};

#endif
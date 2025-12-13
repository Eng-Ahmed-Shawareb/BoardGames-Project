#ifndef SUS_UI_H
#define SUS_UI_H

#include"BoardGame_Classes.h"
#include"SUS_Board.h"
class SUS_UI : public UI<char>{
public : 
    SUS_UI();

    int min_max(SUS_Board* current_board ,bool is_max , char AI_symbol , char human_symbol);

    Move<char>* get_AI_move(Player<char>* player);

    Move<char>* get_move(Player<char>* player) override;

    Player<char>* create_player(string& name , char symbol , PlayerType type) override;

    Player<char>** setup_players() override;
    
};

#endif
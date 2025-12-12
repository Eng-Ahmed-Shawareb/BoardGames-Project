#ifndef NUMERICAL_UI_H
#define NUMERICAL_UI_H

#include<iostream>
#include<set>
#include"BoardGame_Classes.h"

using namespace std;

class Numerical_UI : public UI<int>{
private :

    set<int> avaliable_even_numbers;
    set<int> avaliable_odd_numbers;
    
public : 

    Numerical_UI();

    void print_avaliable_numbers(int num_type);

    Player<int>* create_player(string& name , int symbol , PlayerType type) override;

    Move<int>* get_move(Player<int>* player) override;

    Player<int>** setup_players() override;

    int min_max(Board<int>* current_board , int depth , int alpha , int beta , bool is_max , int AI_type , int human_type);

    Move<int>* get_AI_move(Player<int>* AI_player);

};

#endif
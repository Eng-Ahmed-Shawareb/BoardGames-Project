#ifndef NUMERICAL_UI_H
#define NUMERICAL_UI_H

#include<iostream>
#include"BoardGame_Classes.h"

using namespace std;

class Numerical_UI : public UI<int>{
    
public : 

    Numerical_UI();

    Player<int>* create_player(string& name , int symbol , PlayerType type) override;

    Move<int>* get_move(Player<int>* player) override;

    Player<int>** setup_players() override;

};

#endif
#ifndef XO_UI_H
#define XO_UI_H

#include"BoardGame_Classes.h"

class XO_UI : public UI<char> {
public:
    XO_UI();

    ~XO_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);

    int min_max(Board<char>* current_board , int depth , bool is_max , char AI_symbol , char human_symbol);

    Move<char>* get_AI_move(Player<char>* AI_player);

    Move<char>* get_move(Player<char>* player);
};


#endif
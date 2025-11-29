#include<iostream>
#include"BoardGame_Classes.h"
#include"MemoryGame_UI.h"

MemoryGame_UI::MemoryGame_UI() : UI<char>("Welcome to my Memory-XO game!", 3) {}

Player<char>* MemoryGame_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer");
    
    return new Player<char>(name, symbol, type);
}

Move<char>* MemoryGame_UI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

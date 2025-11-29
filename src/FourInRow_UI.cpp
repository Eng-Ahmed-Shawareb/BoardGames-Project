#include<iostream>
#include"BoardGame_Classes.h"
#include"FourInRow_UI.h"

using namespace std;

FourInRow_UI::FourInRow_UI() : UI("Welcome to my Four In Row game!" , 3) {};

Move<char>* FourInRow_UI::get_move(Player<char>* player){
    int x = 0;
    int y;
    char symbol = player->get_symbol();
    if( player->get_type() == PlayerType::HUMAN ){
        cout << "Please enter your move column [0 to 6] : ";
        cin >> y;
    }
    else if( player->get_type() == PlayerType::COMPUTER ){
        int columns = player->get_board_ptr()->get_columns();

        y = rand() % columns;

    }
    return new Move<char>( x , y , symbol );
}

Player<char>* FourInRow_UI::create_player(string& name , char symbol , PlayerType type){
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player : " << name << " (" << symbol << ")" << endl;
    return new Player(name , symbol , type);
}

Player<char>** FourInRow_UI::setup_players(){
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, static_cast<char>('X'), typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, static_cast<char>('O'), typeO);

    return players;
}
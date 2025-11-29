#include<iostream>
#include<vector>
#include"BoardGame_Classes.h"
#include"SUS_UI.h"
#include"SUS_Board.h"

SUS_UI::SUS_UI() : UI("Welcome to my SUS game!" , 3) {};

Move<char>* SUS_UI::get_move(Player<char>* player){
    int x;
    int y; 
    char symbol = player->get_symbol();

    if(player->get_type() == PlayerType::HUMAN){
        cout << "Please enter your move x and y [0 to 2] : ";
        cin >> x >> y;
    }

    else if(player->get_type() == PlayerType::COMPUTER){
        int rows = player->get_board_ptr()->get_rows();
        int columns = player->get_board_ptr()->get_columns();
        x = rand() % rows;
        y = rand() % columns;
    }

    return new Move<char>( x , y , symbol );
}

Player<char>* SUS_UI::create_player(string& name , char symbol , PlayerType type){
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player : " << name << " (" << symbol << ")" << endl;
    return new Player(name , symbol , type);
}

Player<char>** SUS_UI::setup_players(){
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameS = get_player_name("Player S");
    PlayerType typeS = get_player_type_choice("Player S", type_options);
    players[0] = create_player(nameS, 'S', typeS);

    string nameU = get_player_name("Player U");
    PlayerType typeU = get_player_type_choice("Player U", type_options);
    players[1] = create_player(nameU, 'U', typeU);

    return players;
}
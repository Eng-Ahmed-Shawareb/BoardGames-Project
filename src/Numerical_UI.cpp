#include<iostream>
#include<vector>
#include"Numerical_UI.h"
using namespace std;

Numerical_UI::Numerical_UI() : UI<int>("Welcome to my Numerical game!" , 3){};

Player<int>* Numerical_UI::create_player(string& name , int symbol , PlayerType type){
    string num_type = (symbol == 1) ? "Odd" : "Even";

    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player : " << name << " (" << num_type << ")" << endl;
    return new Player(name , symbol , type);
}

Move<int>* Numerical_UI::get_move(Player<int>* player){
    int x , y , symbol;
    int num_type = player->get_symbol();
    if(player->get_type() == PlayerType::HUMAN){
        cout << endl << "Please enter the number : ";
        ( num_type == 1 ) ? cout << " choose from [1 , 3 , 5 , 7 , 9]. " : cout << " choose from [2 , 4 , 6 , 8]. " << endl;
        cin >> symbol;
        while( ( symbol % 2 ) != ( num_type % 2 ) || symbol < 1 || symbol > 9 ){
            cout << "Invalid symbol , please enter another symbol : ";
            ( num_type == 1 ) ? cout << " choose from [1 , 3 , 5 , 7 , 9]. " : cout << " choose from [2 , 4 , 6 , 8]. " << endl;
            cin >> symbol;
        }
        int symbol = player->get_symbol();
        cout << "Please enter your move x and y [0 to 2] : ";
        cin >> x >> y;
        
    }
    else if(player->get_type() == PlayerType::COMPUTER){
        vector<int>choices;
        int symbol_index;
        for( int i = 1 ; i <= 9 ; ++i ){
            if( ( i % 2 ) == ( num_type % 2 ) ){
                choices.push_back(i);
            }
        }
        symbol_index = rand() % ( (int) choices.size() );
        symbol = choices[symbol_index - 1];
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<int>(x, y, symbol);
}

Player<int>** Numerical_UI::setup_players(){
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameEven = get_player_name("Even player");
    PlayerType typeEven = get_player_type_choice("Even player", type_options);
    players[0] = create_player(nameEven, static_cast<int>(2), typeEven);

    string nameOdd = get_player_name("Odd player");
    PlayerType typeOdd = get_player_type_choice("Odd player", type_options);
    players[1] = create_player(nameOdd, static_cast<int>(1), typeOdd);

    return players;
}
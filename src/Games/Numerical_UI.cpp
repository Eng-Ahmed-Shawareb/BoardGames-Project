#include<iostream>
#include<vector>
#include"Numerical_UI.h"
#include"Numerical_Board.h"
using namespace std;

Numerical_UI::Numerical_UI() : UI<int>("Welcome to my Numerical game!" , 3){
    avaliable_even_numbers = {2 , 4 , 6 , 8};
    avaliable_odd_numbers = {1 , 3 , 5 , 7 , 9};
};

void Numerical_UI::print_avaliable_numbers(int num_type){
    if( num_type % 2 ){
            cout << "[ ";
            for(auto it = avaliable_odd_numbers.begin() ; it != avaliable_odd_numbers.end() ; ++it){
                cout << *it << " ";

            }
            cout << "]";

    }else{
        cout << "[ ";
        for(auto it = avaliable_even_numbers.begin() ; it != avaliable_even_numbers.end() ; ++it){
                cout << *it << " ";

        }
        cout << "]";
    }
}

Player<int>* Numerical_UI::create_player(string& name , int symbol , PlayerType type){
    string num_type = (symbol == 1) ? "Odd" : "Even";

    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
        << " player : " << name << " (" << num_type << ")" << endl;
    return new Player(name , symbol , type);
}

Move<int>* Numerical_UI::get_move(Player<int>* player){
    int x , y , symbol;
    int num_type = player->get_symbol();
    if( player->get_type() == PlayerType::HUMAN ){
        
        if( num_type % 2 ){
            cout << "Please enter number from : ";
            print_avaliable_numbers(num_type);
            cout << endl;
            cin >> symbol;

            while( avaliable_odd_numbers.find(symbol) == avaliable_odd_numbers.end() ){
                cout << "Invalid number. ";
                cout << "Please enter number from : ";
                print_avaliable_numbers(num_type);
                cout << endl;
                cin >> symbol;
            }
            avaliable_odd_numbers.erase(symbol);
        }else{
            cout << "Please enter number from : ";
            print_avaliable_numbers(num_type);
            cout << endl;
            cin >> symbol;

            while( avaliable_even_numbers.find(symbol) == avaliable_even_numbers.end() ){
                cout << "Invalid number. ";
                cout << "Please enter number from : ";
                print_avaliable_numbers(num_type);
                cout << endl;
                cin >> symbol;
            }
            avaliable_even_numbers.erase(symbol);
        }

        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
        
    }
    
    else if( player->get_type() == PlayerType::COMPUTER ){
        /*vector<int>choices;
        int symbol_index;
        for( int i = 1 ; i <= 9 ; ++i ){
            if( ( i % 2 ) == ( num_type % 2 ) ){
                choices.push_back(i);
            }
        }
        symbol_index = rand() % ( (int) choices.size() );
        symbol = choices[symbol_index];
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();*/
        return get_AI_move(player);
    }
    return new Move<int>(x, y, symbol);
}

Player<int>** Numerical_UI::setup_players(){
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameOdd = get_player_name("Odd player");
    PlayerType typeOdd = get_player_type_choice("Odd player", type_options);
    players[0] = create_player(nameOdd, static_cast<int>(1), typeOdd);

    string nameEven = get_player_name("Even player");
    PlayerType typeEven = get_player_type_choice("Even player", type_options);
    players[1] = create_player(nameEven, static_cast<int>(0), typeEven);

    return players;
}

int Numerical_UI::min_max(Board<int>* current_board , int depth , int alpha , int beta , bool is_max , int AI_type , int human_type){
    //base case

    Player<int> temp_player("temp", 0, PlayerType::HUMAN);

    if( current_board->is_win(&temp_player) ){

        if (is_max) {
            return -10 - (100 - depth); 
        } else {
            return 10 + (100 - depth);
        }
    }

    if( current_board->is_draw(&temp_player) ){
        return 0;
    }

    if( depth > 8 )
        return 0;

    //transition

    if( is_max ){
        int max_score = -1e5;

        vector<int>choices;
        int symbol_index;
        if( AI_type % 2 ){
            for(auto& i : avaliable_odd_numbers)
                choices.push_back(i);
        }else{
            for(auto& i : avaliable_even_numbers)
                choices.push_back(i);
        }

        for(int i = 0 ; i < current_board->get_rows() ; ++i)
            for(int j = 0 ; j < current_board->get_columns() ; ++j){
                if( current_board->get_cell(i , j) == 0 ){

                    for(int num : choices){
                        Move<int> current_move(i , j , num);
                        current_board->update_board(&current_move);

                        ( AI_type % 2 ) ? avaliable_odd_numbers.erase(num) : avaliable_even_numbers.erase(num);


                        int score = min_max(current_board, depth+1 , alpha , beta , false , AI_type , 1 - AI_type);

                        Move<int> undo_move(i , j , 0);
                        current_board->update_board(&undo_move);

                        ( AI_type % 2 ) ? avaliable_odd_numbers.insert(num) : avaliable_even_numbers.insert(num);

                        max_score = max(max_score , score);

                        alpha = max(alpha , score);

                        if( alpha >= beta )
                            break;
                                            
                    }

                }
            }
        
        return max_score;
    }

    else{
        int min_score = 1e5;

        vector<int>choices;
        int symbol_index;
        if( human_type % 2 ){
            for(auto& i : avaliable_odd_numbers)
                choices.push_back(i);
        }else{
            for(auto& i : avaliable_even_numbers)
                choices.push_back(i);
        }

        for(int i = 0 ; i < current_board->get_rows() ; ++i)
            for(int j = 0 ; j < current_board->get_columns() ; ++j){
                if( current_board->get_cell(i , j) == 0 ){

                    for(int num : choices){
                        Move<int> current_move(i , j , num);
                        current_board->update_board(&current_move);

                        ( human_type % 2 ) ? avaliable_odd_numbers.erase(num) : avaliable_even_numbers.erase(num);

                        int score = min_max(current_board , depth+1, alpha , beta , true , AI_type , 1 - AI_type);

                        Move<int> undo_move(i , j , 0);
                        current_board->update_board(&undo_move);
                        ( human_type % 2 ) ? avaliable_odd_numbers.insert(num) : avaliable_even_numbers.insert(num);

                        min_score = min(min_score , score);

                        beta = min(beta , score);

                        if( alpha >= beta )
                            break;
                                            
                    }

                }
            }
        
        return min_score;
    }

}

Move<int>* Numerical_UI::get_AI_move(Player<int>* AI_player){
    Board<int>* test_board = new Numerical_Board();
    *test_board = *AI_player->get_board_ptr();

    int num_type = AI_player->get_symbol();

    vector<int>choices;
    int symbol_index;
    if( AI_player->get_symbol() % 2 ){
        for(auto& i : avaliable_odd_numbers)
            choices.push_back(i);
    }else{
        for(auto& i : avaliable_even_numbers)
            choices.push_back(i);
    }

    Move<int>* best_move = new Move<int>(0 , 0 , num_type);
    int best_score = -1e5;

    for(int i = 0 ; i < test_board->get_rows() ; ++i)
        for(int j = 0 ; j < test_board->get_columns() ; ++j){
            if( test_board->get_cell(i , j) == 0 ){

                for(int num : choices){
                    Move<int> current_move(i , j , num);
                    test_board->update_board(&current_move);

                    ( AI_player->get_symbol() % 2 ) ? avaliable_odd_numbers.erase(num) : avaliable_even_numbers.erase(num);

                    int score = min_max(test_board , 0 , best_score , 1e5 , false , num_type , 1 - num_type);

                    Move<int> undo_move(i , j , 0);
                    test_board->update_board(&undo_move);

                    ( AI_player->get_symbol() % 2 ) ? avaliable_odd_numbers.insert(num) : avaliable_even_numbers.insert(num);


                    if( score > best_score ){
                        best_score = score;
                        delete best_move;
                        best_move = new Move<int>(i , j , num);
                    }
                                        
                }

            }
        }
    ( AI_player->get_symbol() % 2 ) ? avaliable_odd_numbers.erase(best_move->get_symbol()) 
        : avaliable_even_numbers.erase(best_move->get_symbol());
    delete test_board;
    return best_move;
}
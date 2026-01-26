#include "Numerical_UI.h"
#include "Numerical_AI_Player.h"
#include <iostream>
#include <vector>
using namespace std;

Numerical_UI::Numerical_UI() : UI<int>("Welcome to my Numerical game!", 3){};

void Numerical_UI::print_avaliable_numbers(Numerical_Board *current_board,
                                           int num_type) {
  if (num_type % 2) {
    cout << "[ ";
    for (auto it = current_board->avaliable_odd_numbers.begin();
         it != current_board->avaliable_odd_numbers.end(); ++it) {
      cout << *it << " ";
    }
    cout << "]";

  } else {
    cout << "[ ";
    for (auto it = current_board->avaliable_even_numbers.begin();
         it != current_board->avaliable_even_numbers.end(); ++it) {
      cout << *it << " ";
    }
    cout << "]";
  }
}

Player<int> *Numerical_UI::create_player(string &name, int symbol,
                                         PlayerType type) {
  string num_type = (symbol == 1) ? "Odd" : "Even";

  cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
       << " player : " << name << " (" << num_type << ")" << endl;
  if (type == PlayerType::COMPUTER) {
    return new Numerical_AI_Player(name, symbol);
  }
  return new Player(name, symbol, type);
}

Move<int> *Numerical_UI::get_move(Player<int> *player) {
  Numerical_Board *current_board =
      dynamic_cast<Numerical_Board *>(player->get_board_ptr());
  int x, y, symbol;
  int num_type = player->get_symbol();
  if (player->get_type() == PlayerType::HUMAN) {

    if (num_type % 2) {
      cout << "Please enter number from : ";
      print_avaliable_numbers(current_board, num_type);
      cout << endl;
      cin >> symbol;

      while (current_board->avaliable_odd_numbers.find(symbol) ==
             current_board->avaliable_odd_numbers.end()) {
        cout << "Invalid number. ";
        cout << "Please enter number from : ";
        print_avaliable_numbers(current_board, num_type);
        cout << endl;
        cin >> symbol;
      }
      current_board->avaliable_odd_numbers.erase(symbol);
    } else {
      cout << "Please enter number from : ";
      print_avaliable_numbers(current_board, num_type);
      cout << endl;
      cin >> symbol;

      while (current_board->avaliable_even_numbers.find(symbol) ==
             current_board->avaliable_even_numbers.end()) {
        cout << "Invalid number. ";
        cout << "Please enter number from : ";
        print_avaliable_numbers(current_board, num_type);
        cout << endl;
        cin >> symbol;
      }
      current_board->avaliable_even_numbers.erase(symbol);
    }

    cout << "\nPlease enter your move x and y (0 to 2): ";
    cin >> x >> y;

  }

  else if (player->get_type() == PlayerType::COMPUTER) {
    Numerical_AI_Player *AI_Player =
        dynamic_cast<Numerical_AI_Player *>(player);
    if (AI_Player) {

      Move<int> *AI_move = AI_Player->get_best_move();
      if (num_type % 2) {
        current_board->avaliable_odd_numbers.erase(AI_move->get_symbol());
      } else {
        current_board->avaliable_even_numbers.erase(AI_move->get_symbol());
      }
      return AI_move;
    }
  }
  return new Move<int>(x, y, symbol);
}

Player<int> **Numerical_UI::setup_players() {
  Player<int> **players = new Player<int> *[2];
  vector<string> type_options = {"Human", "Computer"};

  string nameOdd = get_player_name("Odd player");
  PlayerType typeOdd = get_player_type_choice("Odd player", type_options);
  players[0] = create_player(nameOdd, static_cast<int>(1), typeOdd);

  string nameEven = get_player_name("Even player");
  PlayerType typeEven = get_player_type_choice("Even player", type_options);
  players[1] = create_player(nameEven, static_cast<int>(0), typeEven);

  return players;
}
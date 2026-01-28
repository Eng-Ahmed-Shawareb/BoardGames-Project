#include "clsNumericalUI.h"
#include "clsNumericalAIPlayer.h"
#include <iostream>
#include <vector>
using namespace std;

clsNumericalUI::clsNumericalUI()
    : UI<int>("Welcome to my Numerical game!", 3){};

void clsNumericalUI::printAvailableNumbers(clsNumericalBoard *currentBoard,
                                           int numType) {
  if (numType % 2) {
    cout << "[ ";
    for (auto it = currentBoard->sAvailableOddNumbers.begin();
         it != currentBoard->sAvailableOddNumbers.end(); ++it) {
      cout << *it << " ";
    }
    cout << "]";

  } else {
    cout << "[ ";
    for (auto it = currentBoard->sAvailableEvenNumbers.begin();
         it != currentBoard->sAvailableEvenNumbers.end(); ++it) {
      cout << *it << " ";
    }
    cout << "]";
  }
}

Player<int> *clsNumericalUI::create_player(string &name, int symbol,
                                           PlayerType type) {
  string numType = (symbol == 1) ? "Odd" : "Even";

  cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
       << " player : " << name << " (" << numType << ")" << endl;
  if (type == PlayerType::COMPUTER) {
    return new clsNumericalAIPlayer(name, symbol);
  }
  return new Player(name, symbol, type);
}

Move<int> *clsNumericalUI::get_move(Player<int> *player) {
  clsNumericalBoard *currentBoard =
      dynamic_cast<clsNumericalBoard *>(player->get_board_ptr());
  int x, y, symbol;
  int numType = player->get_symbol();
  if (player->get_type() == PlayerType::HUMAN) {

    if (numType % 2) {
      cout << "Please enter number from : ";
      printAvailableNumbers(currentBoard, numType);
      cout << endl;
      cin >> symbol;

      while (currentBoard->sAvailableOddNumbers.find(symbol) ==
             currentBoard->sAvailableOddNumbers.end()) {
        cout << "Invalid number. ";
        cout << "Please enter number from : ";
        printAvailableNumbers(currentBoard, numType);
        cout << endl;
        cin >> symbol;
      }
      currentBoard->sAvailableOddNumbers.erase(symbol);
    } else {
      cout << "Please enter number from : ";
      printAvailableNumbers(currentBoard, numType);
      cout << endl;
      cin >> symbol;

      while (currentBoard->sAvailableEvenNumbers.find(symbol) ==
             currentBoard->sAvailableEvenNumbers.end()) {
        cout << "Invalid number. ";
        cout << "Please enter number from : ";
        printAvailableNumbers(currentBoard, numType);
        cout << endl;
        cin >> symbol;
      }
      currentBoard->sAvailableEvenNumbers.erase(symbol);
    }

    cout << "\nPlease enter your move x and y (0 to 2): ";
    cin >> x >> y;

  }

  else if (player->get_type() == PlayerType::COMPUTER) {
    clsNumericalAIPlayer *AIPlayer =
        dynamic_cast<clsNumericalAIPlayer *>(player);
    if (AIPlayer) {

      Move<int> *AI_move = AIPlayer->getBestMove();
      if (numType % 2) {
        currentBoard->sAvailableOddNumbers.erase(AI_move->get_symbol());
      } else {
        currentBoard->sAvailableEvenNumbers.erase(AI_move->get_symbol());
      }
      return AI_move;
    }
  }
  return new Move<int>(x, y, symbol);
}

Player<int> **clsNumericalUI::setup_players() {
  Player<int> **players = new Player<int> *[2];
  vector<string> vTypeOptions = {"Human", "Computer"};

  string nameOdd = get_player_name("Odd player");
  PlayerType typeOdd = get_player_type_choice("Odd player", vTypeOptions);
  players[0] = create_player(nameOdd, static_cast<int>(1), typeOdd);

  string nameEven = get_player_name("Even player");
  PlayerType typeEven = get_player_type_choice("Even player", vTypeOptions);
  players[1] = create_player(nameEven, static_cast<int>(0), typeEven);

  return players;
}
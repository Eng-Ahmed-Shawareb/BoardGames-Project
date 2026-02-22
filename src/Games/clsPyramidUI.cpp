#include "clsPyramidUI.h"
#include "BoardGame_Classes.h"
#include "clsInputValidate.h"
#include "clsPyramidAIPlayer.h"
#include "clsPyramidBoard.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

clsPyramidUI::clsPyramidUI() : clsUI<char>("Welcome to my Pyramid Tic-Tac-Toe game!", 3) {}

clsPlayer<char> *clsPyramidUI::createPlayer(string &name, char symbol,
                                            enPlayerType type) {
  cout << "Creating " << (type == enPlayerType::HUMAN ? "human" : "computer")
       << endl;
  if (type == enPlayerType::COMPUTER) {
    return new clsPyramidAIPlayer(name, symbol);
  }
  return new clsPlayer<char>(name, symbol, type);
}

clsMove<char> *clsPyramidUI::getMove(clsPlayer<char> *player) {
  int x, y;

  if (player->getType() == enPlayerType::HUMAN) {
    cout << "Please enter your move (x: 0-2, y: based on row):" << endl;
    cout << "Row 0: y can be 2" << endl;
    cout << "Row 1: y can be 1-3" << endl;
    cout << "Row 2: y can be 0-4" << endl;
    
    while (true) {
      cout << "Enter x (row): ";
      if (!clsInputValidate::validIntegerInRange(x, 0, 2))
        continue;
      
      cout << "Enter y (column): ";
      if (!clsInputValidate::validIntegerInRange(y, 0, 4))
        continue;
      

      bool validPos = false;
      if (x == 0 && y == 2) validPos = true;
      else if (x == 1 && y >= 1 && y <= 3) validPos = true;
      else if (x == 2 && y >= 0 && y <= 4) validPos = true;
      
      if (validPos) break;
      
      cout << "Invalid position for this row! Try again." << endl;
    }
  } else {

    clsPyramidAIPlayer* AIPlayer = dynamic_cast<clsPyramidAIPlayer*>(player);
    if (AIPlayer) {
      return AIPlayer->getBestMove();
    }
  }
  
  return new clsMove<char>(x, y, player->getSymbol());
}

clsPlayer<char> **clsPyramidUI::setupPlayers() {
  clsPlayer<char> **players = new clsPlayer<char> *[2];
  vector<string> playerTypes = {"Human", "Computer"};
  
  for (int i = 0; i < 2; ++i) {
    string playerName;
    char symbol = (i == 0) ? 'X' : 'O';
    
    cout << "\nPlayer " << (i + 1) << " Configuration:" << endl;
    
    int typeChoice;
    cout << "Select player type (1: Human, 2: Computer): ";
    while (!clsInputValidate::validIntegerInRange(typeChoice, 1, 2)) {
      cout << "Invalid choice. Please enter 1 or 2: ";
    }
    
    cout << "Enter player name: ";
    cin.ignore();
    getline(cin, playerName);
    
    enPlayerType type = (typeChoice == 1) ? enPlayerType::HUMAN : enPlayerType::COMPUTER;
    players[i] = createPlayer(playerName, symbol, type);
  }
  
  return players;
}

void clsPyramidUI::displayBoardMatrix(const vector<vector<char>> &matrix) const {
  cout << "\n";
  cout << "        " << matrix[0][2] << "\n";
  cout << "      " << matrix[1][1] << " " << matrix[1][2] << " " << matrix[1][3] << "\n";
  cout << "    " << matrix[2][0] << " " << matrix[2][1] << " " << matrix[2][2] << " " << matrix[2][3] << " " << matrix[2][4] << "\n";
  cout << "\n";
}

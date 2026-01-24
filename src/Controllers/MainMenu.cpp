#include "MainMenu.h"
#include "AppController.h"
#include <iostream>
#include <string>
using namespace std;

void MainMenu::implementUserChoice(UserChoice choice) {
  switch (choice) {
  case UserChoice::XOGAME:
    system("clear");
    AppController::playXOGame();
    break;
  case UserChoice::NUMERICALGAME:
    system("clear");
    AppController::playNumericalGame();
    break;
  case UserChoice::SUSGAME:
    system("clear");
    AppController::playSUSGame();
    break;
  case UserChoice::FOURINROWGAME:
    system("clear");
    AppController::playFourInRowGame();
    break;
  case UserChoice::MEMORYGAME:
    system("clear");
    AppController::playMemoryGame();
    break;
  }
}

void MainMenu::printMainMenuScreen() {
  cout << "\t\t\t\t" << "=============================================" << endl;
  cout << "\t\t\t\t" << "     Welcome to our Board Games Program!" << endl;
  cout << "\t\t\t\t" << "=============================================" << endl;
  cout << "\t\t\t\t\t  " << "[1] XO Game." << endl;
  cout << "\t\t\t\t\t  " << "[2] Numerical Game." << endl;
  cout << "\t\t\t\t\t  " << "[3] SUS Game." << endl;
  cout << "\t\t\t\t\t  " << "[4] Four In Row Game." << endl;
  cout << "\t\t\t\t\t  " << "[5] XO Memory Game." << endl;
  cout << "\t\t\t\t" << "=============================================" << endl;
}

void MainMenu::startBoardGameProgram() {
  char playAgain;

  do {
    system("clear");
    int choice;
    printMainMenuScreen();
    cout << "\t\t\t\t" << "     Please enter your choice ? [1 : 5] ? " << endl;
    cin >> choice;
    while (choice > 5 || choice < 1) {
      cout << "Invalid choice. please enter another one ? [1 : 5] ? " << endl;
      cin >> choice;
    }
    implementUserChoice((UserChoice)choice);
    cout << "Good Game!" << endl;
    cout << "Do you want to play again ? [Y : N] ? " << endl;
    cin >> playAgain;
  } while (toupper(playAgain) == 'Y');

  system("clear");
  cout << "Good Bye!" << endl;
}
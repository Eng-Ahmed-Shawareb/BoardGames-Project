#include "clsMainMenu.h"
#include "clsAppController.h"
#include "clsInputValidate.h"
#include <iostream>
#include <string>
using namespace std;

void clsMainMenu::implementUserChoice(_enUserChoice choice) {
  switch (choice) {
  case _enUserChoice::XOGAME:
    system("clear");
    clsAppController::playXOGame();
    break;
  case _enUserChoice::NUMERICALGAME:
    system("clear");
    clsAppController::playNumericalGame();
    break;
  case _enUserChoice::SUSGAME:
    system("clear");
    clsAppController::playSUSGame();
    break;
  case _enUserChoice::FOURINROWGAME:
    system("clear");
    clsAppController::playFourInRowGame();
    break;
  case _enUserChoice::MEMORYGAME:
    system("clear");
    clsAppController::playMemoryGame();
    break;
  case _enUserChoice::MISEREGAME:
    system("clear");
    clsAppController::playMisereGame();
    break;
  }
}

void clsMainMenu::printMainMenuScreen() {
  cout << "\t\t\t\t" << "=============================================" << endl;
  cout << "\t\t\t\t" << "     Welcome to our Board Games Program!" << endl;
  cout << "\t\t\t\t" << "=============================================" << endl;
  cout << "\t\t\t\t\t  " << "[1] XO Game." << endl;
  cout << "\t\t\t\t\t  " << "[2] Numerical Game." << endl;
  cout << "\t\t\t\t\t  " << "[3] SUS Game." << endl;
  cout << "\t\t\t\t\t  " << "[4] Four In Row Game." << endl;
  cout << "\t\t\t\t\t  " << "[5] XO Memory Game." << endl;
  cout << "\t\t\t\t\t  " << "[6] XO Misère Game." << endl;
  cout << "\t\t\t\t" << "=============================================" << endl;
}

void clsMainMenu::startBoardGameProgram() {
  char playAgain;

  do {
    system("clear");
    int choice;
    printMainMenuScreen();
    cout << "\t\t\t\t" << "     Please enter your choice ? [1 : 6] ? " << endl;
    while (!clsInputValidate::validIntegerInRange(choice, 1, 6)) {
      cout << "Invalid choice. please enter another one ? [1 : 6] ? " << endl;
    }
    implementUserChoice((_enUserChoice)choice);
    cout << "Good Game!" << endl;
    cout << "Do you want to play again ? [Y : N] ? " << endl;
    cin >> playAgain;
  } while (toupper(playAgain) == 'Y');

  system("clear");
  cout << "Good Bye!" << endl;
}
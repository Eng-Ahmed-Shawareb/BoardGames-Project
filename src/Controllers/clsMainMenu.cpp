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
  case _enUserChoice::FOURBYFOURGAME:
    system("clear");
    clsAppController::playFourByFourGame();
    break;
  case _enUserChoice::INFINITYGAME:
    system("clear");
    clsAppController::playInfinityGame();
    break;
  case _enUserChoice::PYRAMIDGAME:
    system("clear");
    clsAppController::playPyramidGame();
    break;
  case _enUserChoice::FIVEBYFIVEGAME:
    system("clear");
    clsAppController::playFiveByFiveGame();
    break;
  case _enUserChoice::WORDGAME:
    system("clear");
    clsAppController::playWordGame();
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
  cout << "\t\t\t\t\t  " << "[7] XO Four by Four Game." << endl;
  cout << "\t\t\t\t\t  " << "[8] Infinity XO Game." << endl;
  cout << "\t\t\t\t\t  " << "[9] Pyramid Tic-Tac-Toe Game." << endl;
  cout << "\t\t\t\t\t  " << "[10] 5x5 Tic-Tac-Toe Game." << endl;
  cout << "\t\t\t\t\t  " << "[11] Word Tic-Tac-Toe Game." << endl;
  cout << "\t\t\t\t" << "=============================================" << endl;
}

void clsMainMenu::startBoardGameProgram() {
  char playAgain;

  do {
    system("clear");
    int choice;
    printMainMenuScreen();
    cout << "\t\t\t\t" << "     Please enter your choice ? [1 : 11] ? " << endl;
    while (!clsInputValidate::validIntegerInRange(choice, 1, 11)) {
      cout << "Invalid choice. please enter another one ? [1 : 11] ? " << endl;
    }
    implementUserChoice((_enUserChoice)choice);
    cout << "Good Game!" << endl;
    cout << "Do you want to play again ? [Y : N] ? " << endl;
    cin >> playAgain;
  } while (toupper(playAgain) == 'Y');

  system("clear");
  cout << "Good Bye!" << endl;
}
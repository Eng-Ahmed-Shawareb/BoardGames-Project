#include<iostream>
#include<string>
#include"MainScreen.h"
#include"PlayGameFunctions.h"
using namespace std;

void MainScreen::implementUserChoice(UserChoice choice){
    switch (choice)
    {
    case UserChoice::XOGAME :
        system("clear");
        PlayGameFunctions::playXOGame();
        break;
    case UserChoice::NUMERICALGAME :
        system("clear");
        PlayGameFunctions::playNumericalGame();
        break;
    case UserChoice::SUSGAME : 
        system("clear");
        PlayGameFunctions::playSUSGame();
        break;
    case UserChoice::FOURINROWGAME : 
        system("clear");
        PlayGameFunctions::playFourInRowGame();
        break;
    case UserChoice::MEMORYGAME : 
        system("clear");
        PlayGameFunctions::playMemoryGame();
        break;
    }
}

void MainScreen::printMainMenuScreen(){
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

void MainScreen::startBoardGameProgram(){
    char playAgain;

    do
    {
        system("clear");
        int choice;
        printMainMenuScreen();
        cout << "\t\t\t\t" << "     Please enter your choice ? [1 : 5] ? " << endl;
        cin >> choice;
        while( choice > 5 || choice < 1 ){
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
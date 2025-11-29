#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

class MainScreen{

private : 
    enum class UserChoice { XOGAME = 1 , NUMERICALGAME = 2 , SUSGAME = 3 , FOURINROWGAME = 4 };
public :

    static void implementUserChoice(UserChoice choice);

    static void printMainMenuScreen();

    static void startBoardGameProgram();
};

#endif
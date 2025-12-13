#ifndef MAIN_MENU_H
#define MAIN_MENU_H

class MainMenu{

private : 
    enum class UserChoice { XOGAME = 1 , NUMERICALGAME = 2 , SUSGAME = 3 , FOURINROWGAME = 4 , MEMORYGAME = 5 };
public :

    static void implementUserChoice(UserChoice choice);

    static void printMainMenuScreen();

    static void startBoardGameProgram();
};

#endif
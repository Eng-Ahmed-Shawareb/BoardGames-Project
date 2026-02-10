#ifndef MAIN_MENU_H
#define MAIN_MENU_H

class clsMainMenu {

private:
  enum class _enUserChoice {
    XOGAME = 1,
    NUMERICALGAME = 2,
    SUSGAME = 3,
    FOURINROWGAME = 4,
    MEMORYGAME = 5,
    MISEREGAME = 6,
    FOURBYFOURGAME = 7
  };

public:
  static void implementUserChoice(_enUserChoice choice);

  static void printMainMenuScreen();

  static void startBoardGameProgram();
};

#endif
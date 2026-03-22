
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

class clsMainMenu {

private:

  enum class _enUserChoice {
    XO_GAME = 1,
    NUMERICAL_GAME = 2,
    SUS_GAME = 3,
    FOURINROW_GAME = 4,
    MEMORY_GAME = 5,
    MISERE_GAME = 6,
    FOUR_BY_FOUR_GAME = 7,
    INFINITY_GAME = 8,
    PYRAMID_GAME = 9,
    FIVE_BY_FIVE_GAME = 10,
    WORD_GAME = 11,
    EXIT = 12
  };

  static void implementUserChoice(_enUserChoice choice);

  static _enUserChoice readChoiceArrow();

  static void showLoadingAnimation();

  static void drawGameIcons(int startX, int startY);

public:

  static void startBoardGameProgram();
};

#endif
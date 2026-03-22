#include "clsTUIUtils.h"
#include <iostream>
#include <cstdio>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif

using namespace std;

void clsTUIUtils::gotoxy(int x, int y) {
#ifdef _WIN32
    COORD c;
    c.X = static_cast<SHORT>(x);
    c.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
#else
    cout << "\033[" << y << ";" << x << "H";
    cout.flush();
#endif
}

void clsTUIUtils::color(enTUIColor colorCode) {
    cout << "\033[" << static_cast<int>(colorCode) << "m";
}

void clsTUIUtils::resetColor() {
    cout << "\033[0m";
}

void clsTUIUtils::hideCursor() {
#ifdef _WIN32
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
#else
    cout << "\033[?25l";
    cout.flush();
#endif
}

void clsTUIUtils::showCursor() {
#ifdef _WIN32
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
#else
    cout << "\033[?25h";
    cout.flush();
#endif
}

void clsTUIUtils::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int clsTUIUtils::getch() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    if (ch == 27) {

        struct termios nonblock;
        tcgetattr(STDIN_FILENO, &nonblock);
        nonblock.c_cc[VMIN] = 0;
        nonblock.c_cc[VTIME] = 1;
        tcsetattr(STDIN_FILENO, TCSANOW, &nonblock);

        int ch2 = getchar();
        if (ch2 == 91) {
            int ch3 = getchar();
            if (ch3 == 65) ch = 72;
            else if (ch3 == 66) ch = 80;
            else if (ch3 == 67) ch = 77;
            else if (ch3 == 68) ch = 75;
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

void clsTUIUtils::printCentered(int y, const string& text, int totalWidth, int offsetX) {
    int pad = (totalWidth - (int)text.length()) / 2;
    if (pad < 0) pad = 0;
    gotoxy(offsetX + pad, y);
    cout << text;
}

void clsTUIUtils::drawHLine(int x, int y, int length, string ch) {
    gotoxy(x, y);
    for (int i = 0; i < length; i++) cout << ch;
}

void clsTUIUtils::flushInput() {

    std::cin.clear();

#ifdef _WIN32

    while (_kbhit()) {
        _getch();
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
#else

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while (getchar() != EOF) {

    }

    clearerr(stdin);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    tcflush(STDIN_FILENO, TCIFLUSH);
#endif
}

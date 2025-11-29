#include<iostream>
#include"MainScreen.h"
using namespace std;

int main(){
    
    srand(static_cast<unsigned int>(time(0)));

    MainScreen::startBoardGameProgram();

    return 0;
}
#include "maze-game.h"
string version="0.1.0";
char input;
void menu(){
    cout<<"Maze v"<<version<<'\n'\
        <<"===\n"\
        <<"1=Start Adventure\n"\
        <<"2=Random Maze\n"\
        <<"0=Exit\n"\
        <<"Choose>>[ ]\033[2D";
    cin>>input;
    if(input=='0')exit(0);
    cls;
    if(input=='1')level_menu();
}
void level_menu(){
    cout<<"1-1 Hello Maze\n"\
        <<"1-2 Simple Maze\n"\
        <<"Choose>>[ - ]\033[4D";
    unsigned short level;
    cin>>input;
    level=10*(input-'0');
    cin>>input;
    level+=(input-'0');
}
#ifndef rra_maze_base
#define rra_maze_base
#include <iostream>
#include <string>
#include <vector>
#include "paint.h"
using std::cin;
using std::cout;
using std::endl;
using std::vector;
enum blocktype{
    blank=0,
    wall=1,
        unbreakable_wall=100,
        stone_wall,
    creature=2,
        //player=200,
    text=3,
        texts=300,
    space=4,
        air=400,
        smoke,
        money,
    machine=5,
        upstairs=500,
        downstairs,
        portal,
        button,
        entrance,
        exitb,
    laser=6,
    gate=7,
};
class block{
    public:
    unsigned short id,info;
    block();
    void set(char in);
    char push_block(PAINT &color);
    void settext(char in);
    bool issolid();
};
class entity{
    public:
    static const unsigned short healthcon[];
    short id,x,y,health;
    string name;
    vector<short>memory;
    entity();
    entity(unsigned short iid,unsigned short hhealth,string nname);
    void puthealth();
};
string tos(unsigned short x);
unsigned short tou(string s);
short sign(short i);
#endif

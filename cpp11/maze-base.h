#ifndef rra_maze_base
#define rra_maze_base
#include <iostream>
#include <string>
#include "paint.h"
using std::string;
using std::cin;
using std::cout;
using std::endl;
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
    private:
    unsigned short id,info;
    public:
    block();
    void set(char in);
    char push_block(PAINT &color);
    void settext(char in);
};
class entity{
    public:
    unsigned short id,health,x,y;
    string name;
    entity();
    entity(unsigned short iid,unsigned short hhealth,string nname);
    void die();
};
#endif

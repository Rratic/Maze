#include "maze-base.h"
block::block() { id = blank; }
char block::push_block(PAINT &color)
{
    auto te=id%100;
    switch(te)
    {
        case blank:color.second=lb(p_white);break;
        case wall:color.first=df(p_yellow);break;
        case creature:color.first=df(p_purple);break;
        case text:color.first=df(p_black);color.second=db(p_white);break;
        case space:color.first=lf(p_purple);color.second=db(p_black);break;
        case machine:color.first=lf(p_green);break;
    }
    switch(id){
        case blank:return ' ';
        case unbreakable_wall:return '#';
        case stone_wall:return 'X';
        case texts:return char(info);
        case air:return '.';
        case smoke:return ':';
        case money:return '$';
        case exitb:return '%';
    }
    return ' ';
}
void block::set(char in){
    switch(in){
        case ' ':id=blank;break;
        case '#':id=unbreakable_wall;break;
        case 'X':id=stone_wall;break;
        case '.':id=air;break;
        case ':':id=smoke;break;
        case '%':id=exitb;break;
        default:{
            id=texts;
            info=in;
        }
    }
}
void block::settext(char in){
    id=texts;
    info=in;
}
entity::entity(){id=0;}
entity::entity(unsigned short iid,unsigned short hhealth,string nname){
    id=iid;
    health=hhealth;
    name=nname;
}

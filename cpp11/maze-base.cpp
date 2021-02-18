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
    }
    switch(id){
        case blank:return ' ';break;
        case unbreakable_wall:return '#';break;
        case stone_wall:return 'X';break;
        case texts:return char(info);break;
        case air:return '.';break;
        case smoke:return ':';break;
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

#include "maze-chunk.h"
chunk::chunk(){
    player=nullptr;
}
chunk::chunk(const chunk &other){
    player=new entity;
    *player=*(other.player);
    for(unsigned short i=0;i<16;++i){
        for(unsigned short j=0;j<16;++j)blocks[i][j]=other.blocks[i][j];
    }
}
chunk::~chunk(){
    player=nullptr;
}
void chunk::putchunk(){
    for(unsigned short i=0;i<16;++i){
        for(unsigned short j=0;j<16;++j){
            PAINT brush;
            char ch=blocks[i][j].push_block(brush);
            if(player->x!=i||player->y!=j){
                cout<<putbrush(brush);
            }
            cout<<ch;
        }
        cout<<'\n';
    }
}
bool chunk::toline(string s,unsigned short line){
    if(line>=16)return false;
    size_t t=s.length(),c=0;
    for(size_t i=0;i<t;++i){
        if(s[i]=='\\'){
            ++i;
            blocks[line][c].settext(s[i]);
            ++c;
            continue;
        }
        if(s[i]=='@'){
            if(player!=nullptr)return false;
            player=new entity;
            player->x=line;
            player->y=c;
        }
        else{
            blocks[line][c].set(s[i]);
        }
        ++c;
    }
    return true;
}

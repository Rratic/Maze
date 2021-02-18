#include "maze-chunk.h"
chunk::chunk(){
    player=nullptr;
}
chunk::chunk(chunk &other){
    player=new entity;
    *player=*(other.player);
    for(unsigned short i=0;i<16;++i){
        for(unsigned short j=0;j<16;++j)blocks[i][j]=other.blocks[i][j];
    }
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
    size_t t=s.length(),c=0;
    for(size_t i=0;i<t;++i){
        if(s[i]=='\\'){
            ++i;
            blocks[line][c].settext(s[i]);
            ++c;
            continue;
        }
        if(s[i]=='@'){
            player->x=line;
            player->y=i-c;
        }
        else{
            blocks[line][c].set(s[i]);
        }
        ++c;
    }
}

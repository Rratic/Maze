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

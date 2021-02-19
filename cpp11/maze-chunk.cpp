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
            PAINT brush=make_pair(0,0);
            char ch=blocks[i][j].push_block(brush);
            if(player==nullptr||player->x!=i||player->y!=j){
                cout<<putbrush(brush);
                cout<<ch;
            }
            else{
                cout<<'!';
            }
        }
        cout<<"\033[m\n";
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
unsigned short chunk::work(unsigned short &info,string words){
    cls;
    putchunk();
    cout<<words<<'\n';
    char in;
    cin>>in;
    switch(in){
        case 'q':return 4;
        case 'r':return 3;
    }
    /*
    w,a,s,d move
    r replay
    q quit
    e "use"
    */
}
/*
状态码 | 含义 | 实参
0       胜利    获得金币数
1       死亡    死法
2       跳转    跳转区块ID
3       重玩    无
4       退出    无
5       错误    错误码
6       备用    暂无

死法
0   虚空
1   未知（用在雾中）
2   卡住
*/

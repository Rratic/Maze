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
    l=other.l;
    w=other.w;
}
chunk::~chunk(){
    if(player!=nullptr)delete player;
}
void chunk::putchunk(){
    for(unsigned short i=0;i<l;++i){
        for(unsigned short j=0;j<w;++j){
            PAINT brush=make_pair(37,40);
            char ch=blocks[i][j].push_block(brush);
            if(player==nullptr||player->x!=i||player->y!=j){
                cout<<putbrush(brush);
                cout<<ch;
            }
            else{
                bool flag=false;
                for(entity k:monsters){
                    if(k.x==i&&k.y==j){
                        flag=true;
                        cout<<"\033[91m&";
                    }
                }
                if(flag)continue;
                cout<<putcolor(lf(p_cyan));
                if(blocks[i][j].id/100==machine)cout<<putcolor(db(p_green));
                else cout<<putcolor(db(p_black));
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
        if(s[i]=='&'){
            entity te;
            string ss;
            for(i+=2;s[i]!=',';++i){ss+=s[i];}
            te.id=tou(ss);
            ss="";
            for(++i;s[i]!='}';++i){
                if(s[i]=='\\')++i;
                ss+=s[i];
            }
            te.name=ss;
            te.x=line;
            te.y=c;
            te.health=te.healthcon[te.id];
            monsters.push_back(te);
            blocks[line][c].id=air;
        }
        else if(s[i]=='@'){
            if(player!=nullptr)return false;
            player=new entity;
            player->x=line;
            player->y=c;
            player->health=10;
            player->id=0;
            blocks[line][c].id=air;
        }
        else{
            blocks[line][c].set(s[i]);
        }
        ++c;
    }
    return true;
}
bool chunk::canmove(unsigned short x,unsigned short y,short xx,short yy){
    if(blocks[x+xx][y+yy].issolid()||blocks[x][y].issolid())return false;
    return true;
}
bool chunk::workmonsters(entity &i){
    switch(i.id){
        case 1:{
            if(blocks[i.x][i.y].issolid()){
                --i.health;
                break;
            }
            short xx,yy;
            for(size_t j=0;j<8;++j){
                if(i.x+mox[j]==player->x&&i.y+moy[j]==player->y){
                    player->health-=7;
                }
            }
        }
        case 2:{
            unsigned short pos=0,face=1;
            if(i.memory.size()==0){
                i.memory.push_back(pos);
                i.memory.push_back(face);
            }
            else{
                pos=i.memory[0];
                face=i.memory[1];
            }
        }
    }
    if(i.health<=0)return true;
    return false;
}
unsigned short chunk::work(unsigned short &info,string words){
    while(true){
        cls;
        putchunk();
        player->puthealth();
        cout<<'\n'<<words<<'\n';
        char in;
        cin>>in;
        char xx=0,yy=0,x=player->x,y=player->y;
        switch(in){
            case 'q':return 4;
            case 'r':return 3;
            case 'e':{
                if(blocks[player->x][player->y].id==exitb)return 0;
                break;
            }
            case 'w':xx=-1;break;
            case 's':xx=1;break;
            case 'a':yy=-1;break;
            case 'd':yy=1;break;
        }
        x+=xx;y+=yy;
        if(x<0||y<0||x>15||y>15||blocks[x][y].id==blank){
            info=0;
            return 1;
        }
        if(blocks[x][y].id/100==wall)continue;
        if(blocks[x][y].id==money){
            ++info;
            blocks[x][y].id=air;
        }
        if(blocks[x][y].id==texts){
            if(blocks[x+xx][y+yy].id/100!=space)continue;
            blocks[x+xx][y+yy]=blocks[x][y];
            blocks[x][y].id=air;
        }
        player->x=x;player->y=y;
    /*
    w,a,s,d move
    r replay
    q quit
    e "use"
    */
        for(vector<entity>::iterator it=monsters.begin();it!=monsters.end();++it){
            if(workmonsters(*it)){
                monsters.erase(it);
                if(it==monsters.end())break;
            }
        }
        if(player->health<=0){
            if(blocks[player->x][player->y].id==smoke)info=1;
            else info=3;
            return 1;
        }
    }
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
3   怪物
*/

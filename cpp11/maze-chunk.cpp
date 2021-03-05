#include "maze-chunk.h"
char in;
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
    monsters=other.monsters;
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
                for(entity k:monsters){
                    if(k.x==i&&k.y==j){
                        ch=k.look(brush);
                        break;
                    }
                }
                cout<<putbrush(brush);
                cout<<ch;
            }
            else{
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
bool chunk::canmove(short x,short y,short xx,short yy){
    x+=xx;y+=yy;
    if(x<0||y<0||x>=l||y>=w||blocks[x][y].issolid()\
    ||(blocks[x][y].id==gate_east_west&&xx!=0)\
    ||(blocks[x][y].id==gate_north_south&&yy!=0))return false;
    return true;
}
bool chunk::workmonsters(entity &i){
    switch(i.id){
        case 1:{
            if(blocks[i.x][i.y].issolid()){
                --i.health;
                break;
            }
            if(blocks[i.x][i.y].id==blank){
                cout<<i.name<<lang.search("die-0");
                return true;
            }
            short xx,yy;
            for(size_t j=0;j<4;++j){
                if(i.x+mox[j]==player->x&&i.y+moy[j]==player->y){
                    player->health-=7;
                }
            }
            xx=player->x-i.x;
            yy=player->y-i.y;
            if(abs(xx)>=abs(yy)){
                yy=0;
                xx=sign(xx);
            }else{
                xx=0;
                yy=sign(yy);
            }
            if(canmove(i.x,i.y,xx,yy)){
                i.x+=xx;
                i.y+=yy;
            }
            break;
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
            short xx=mox[face],yy=moy[face],j=0;
            while(!canmove(i.x,i.y,xx,yy)){
                ++face;
                if(face==4)face=0;
                xx=mox[face];
                yy=moy[face];
                if(j==3){
                    blocks[i.x][i.y].id=texts;
                    blocks[i.x][i.y].info=i.name[pos];
                    return true;
                }
                ++j;
            }
            blocks[i.x][i.y].id=texts;
            blocks[i.x][i.y].info=i.name[pos];
            ++pos;
            if(pos==i.name.length()){
                return true;
            }
            i.x+=xx;i.y+=yy;
            i.memory[0]=pos;
            i.memory[1]=face;
            break;
        }
        case 3:{
            short xx=0,yy=0,x=i.x,y=i.y;
            switch(in){
                case 'w':xx=-1;break;
                case 's':xx=1;break;
                case 'a':yy=-1;break;
                case 'd':yy=1;break;
            }
            x+=xx;y+=yy;
            if(x<0||y<0||x>15||y>15||blocks[x][y].id==blank)return true;
            if(blocks[x][y].id/100==wall)break;
            if(blocks[x][y].id==texts){
                if(blocks[x+xx][y+yy].id/100!=space)break;
                blocks[x+xx][y+yy]=blocks[x][y];
                blocks[x][y].id=air;
            }
            i.x=x;i.y=y;
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
        cin>>in;
        short xx=0,yy=0,x=player->x,y=player->y;
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
        if(blocks[x][y].id/100==wall)goto movemonsters;
        if(blocks[x][y].id==money){
            ++info;
            blocks[x][y].id=air;
        }
        if(blocks[x][y].id==texts){
            if(blocks[x+xx][y+yy].id/100!=space)goto movemonsters;
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
        movemonsters:;
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

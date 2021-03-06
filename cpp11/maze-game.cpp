#include "maze-game.h"
string input,input2;
void init(){
    if(!setting.fill("save/setting.txt")){
        setting.tag["level-data"]="data/levels.data";
        setting.tag["lang-data"]="data/lang/en.txt";
        setting.tag["saving"]="save/saving.txt";
        setting.tag["count-data"]="data/count.data";
        if(!setting.save("save/setting.txt")){
            cout<<"Error saving setting!\nTarget file path:save/setting.txt\n";
            cin>>input;
        }
    }
    if(setting.without("user-name")){
        cout<<"Please input your name:";
        bool flag=true;
        while(flag){
            cin>>input;
            size_t l=input.length();
            flag=false;
            for(size_t i=0;i<l;++i){
                if(input[i]<=' '){
                    flag=true;
                    break;
                }
            }
            if(flag)cout<<"Illegal user name!\nUser names should look like \"Rratic\"\n";
        }
        setting.tag["user-name"]=input;
        setting.save("save/setting.txt");
    }
    if(!lang.fill(setting.tag["lang-data"])){
        cout<<"Language package unfound!\nExpected file path:"<<setting.tag["lang-data"]<<"\nPlease check save/setting.txt,and then continue.\n";
        cin>>input;
    }
    savedgame.fill(setting.tag["saving"]);
    count_levels.fill(setting.tag["count-data"]);
    srand(time(nullptr));
}
bool game::set(string filename,string find){
    ifstream fin;
    fin.open(filename,ios::in);
    if(!fin.is_open())return false;
    name=find;
    string s;
    find='$'+find;
    unsigned short num,len,wid;
    bool flag=true;
    while(getline(fin,s)){
        if(s==find){
            flag=false;
            break;
        }
    }
    if(flag)return false;
    fin>>num>>len>>wid;
    for(unsigned short i=0;i<num;++i){
        getline(fin,s);
        chunk te;
        te.l=len;
        te.w=wid;
        for(unsigned short j=0;j<len;++j){
            getline(fin,s);
            if(s.find("@")!=s.npos){
                if(flag)return false;
                focusing=i;
                flag=true;
            }
            if(!te.toline(s,j))return false;
        }
        chunks.push_back(te);
    }
    if(!flag)return false;
    return true;
}
void end_with(string s){
    cout<<s<<'\n'<<lang.search("pause")<<'\n';
    char c;
    cin>>c;
}
unsigned short game::work(){
    unsigned short a,b=0;
    while(true){
        a=chunks[focusing].work(b,help_words);
        switch(a){
            case 0:{
                end_with(lang.search("win")+'\n'+lang.search("score")+':'+tos(b));
                savedgame.tag[name]=tos(b);
                savedgame.save(setting.tag["saving"]);
                return 0;
            }
            case 1:end_with(setting.search("user-name")+lang.search("die-"+tos(b)));return 1;
            case 4:return 4;
        }
    }
    return 0;
}
void menu(){
    cout<<putcolor(lf(p_green))<<lang.search("game-name")<<'\n'\
        <<putcolor(lf(p_yellow))<<"===\n"<<normalcolor\
        <<"1="<<lang.search("menu-first")<<'\n'\
        <<"2="<<lang.search("menu-second")<<'\n'\
        <<"0="<<lang.search("exit")<<'\n'\
        <<"s="<<lang.search("menu-setting")<<'\n'\
        <<lang.search("menu-choice")<<">>[ ]"<<cursorleft(2);
    cin>>input;
    if(input=="0")exit(0);
    cls;
    if(input=="1")world_menu();
    else if(input=="2")rand_game();
    else if(input=="s")set_game();
}
void game::clear(){
    chunks.clear();
}
void world_menu(){
    for(unsigned short i=1;i<=tou(count_levels.tag["worlds"]);++i){
        cout<<i<<'='<<lang.search("title-"+tos(i))<<'\n';
    }
    cout<<"0="<<lang.search("exit")<<'\n'<<lang.search("menu-choice")<<">>[ ]"<<cursorleft(2);
    cin>>input;
    if(count_levels.without("world-"+input)||input=="0")return;
    cls;
    level_menu(tou(input));
}
void level_menu(unsigned short i){
    game all;
    while(true){
        //for(unsigned short i=1;i<=tou(count_levels.tag["worlds"]);++i){
            string tee=tos(i);
            for(unsigned short j=1;j<=tou(count_levels.tag["world-"+tee]);++j){
                string te=tee+'-'+tos(j);
                cout<<i<<'-'<<j<<' '<<lang.search("name-"+te)<<' ';
                if(savedgame.without(te))cout<<putcolor(lf(p_red))<<lang.search("level-uncompleted")<<normalcolor;
                else cout<<putcolor(lf(p_green))<<lang.search("score")<<':'<<savedgame.tag[te]<<normalcolor;
                cout<<'\n';
            }
        //}
        cout<<"0 "<<lang.search("exit")<<"\n"\
            <<lang.search("menu-choice")<<">>[   ]"<<cursorleft(4);
        cin>>input;
        if(input=="0")return;
        if(all.set(setting.tag["level-data"],input)){
            if(lang.without("help-"+input))all.help_words=lang.search("no-help");
            else all.help_words=lang.tag["help-"+input];
            cls;
            if(!lang.without("story-"+input))show_story(lang.tag["story-"+input]);
            all.work();
            cls;
        }
        else{
            cls;
            cout<<putcolor(lf(p_red))<<lang.search("level-unfound")<<normalcolor<<"\n";
        }
        all.clear();
    }
}
void set_game(){
    for(auto i:setting.tag){
        cout<<"Value of "<<i.first<<":"<<i.second<<'\n';
    }
    cout<<"Input what you want to set:\n[Tag name] [Tag value]\nUse q to quit.\n";
    cin>>input;
    if(input=="q")return;
    cin>>input2;
    if(setting.tag.find(input)==setting.tag.end()){
        cout<<"Illegal tag name!\nPress any key to continue.\n";
        cin>>input;
        return;
    }
    setting.tag[input]=input2;
    if(input=="lang-data")lang.fill(input2);
    if(input=="saving")savedgame.fill(input2);
    setting.save("save/setting.txt");
}
void show_story(string s){
    size_t t=s.length();
    time_t nowtime;
    tm*newtime;
    time(&nowtime);
    newtime=localtime(&nowtime);
    for(size_t i=0;i<t;++i){
        if(s[i]=='$'){
            string ss;
            ++i;
            for(++i;s[i]!='}';++i)ss+=s[i];
            if(ss=="name")cout<<setting.tag["user-name"];
            else if(ss=="time")cout<<newtime->tm_hour<<':'<<newtime->tm_min<<':'<<newtime->tm_sec;
            else if(ss=="date")cout<<newtime->tm_year+1900<<'/'<<newtime->tm_mon<<'/'<<newtime->tm_mday;
            else if(ss=="ESC"){
                unsigned short x=0;
                for(++i;s[i]!=')';++i){
                    x+=(s[i]-'0');
                    x*=10;
                }
                ++i;
                cout<<putcolor(x);
            }
            else if(ss=="head")cout<<lang.search("letter-from")<<lang.search("letter-sender")<<'\n'<<lang.search("letter-to")<<setting.tag["user-name"];
            //2038年失效qaq
            else cout<<'['<<ss<<']';
            continue;
        }
        if(s[i]=='\\'){
            ++i;
            if(s[i]=='n'){
                cout<<'\n';
                continue;
            }
        }
        cout<<s[i];
    }
    cout<<"\n>>[ ]"<<cursorleft(2);
    cin>>input;
}
void rand_game(){
    unsigned short m=rand()%6+11,n=rand()%6+11;
    array<array<unsigned short,16>,16>a;
    prim(m,n,a);
    game all;
    all.help_words="";
    all.focusing=0;
    chunk temp;
    temp.l=m;temp.w=n;
    for(size_t i=0;i<m;++i){
        for(size_t j=0;j<n;++j){
            switch(a[i][j]){
                case '#':temp.blocks[i][j].setdirect(unbreakable_wall);break;
                case '@':{
                    temp.player=new entity;
                    temp.player->x=i;
                    temp.player->y=j;
                    temp.player->health=10;
                    temp.player->id=0;
                    temp.player->name=setting.tag["user-name"];
                }
                case '.':temp.blocks[i][j].setdirect(air);break;
                case '%':temp.blocks[i][j].setdirect(exitb);break;
                case '$':temp.blocks[i][j].setdirect(money);break;
            }
        }
    }
    all.chunks.push_back(temp);
    all.work();
}

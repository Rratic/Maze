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
    cout<<"\033[92m"<<lang.search("game-name")<<'\n'\
        <<"\033[93m===\n\033[m"\
        <<"1="<<lang.search("menu-first")<<'\n'\
        <<"2="<<lang.search("menu-second")<<'\n'\
        <<"0="<<lang.search("exit")<<'\n'\
        <<"s="<<lang.search("menu-setting")<<'\n'\
        <<lang.search("menu-choice")<<">>[ ]\033[2D";
    cin>>input;
    if(input=="0")exit(0);
    cls;
    if(input=="1")world_menu();
    else if(input=="s")set_game();
}
void game::clear(){
    chunks.clear();
}
void world_menu(){
    for(unsigned short i=1;i<=tou(count_levels.tag["worlds"]);++i){
        cout<<i<<'='<<lang.search("title-"+tos(i))<<'\n';
    }
    cout<<"0="<<lang.search("exit")<<'\n'<<lang.search("menu-choice")<<">>[ ]\033[2D";
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
                if(savedgame.without(te))cout<<"\033[91m"<<lang.search("level-uncompleted")<<"\033[m";
                else cout<<putcolor(lf(p_green))<<lang.search("score")<<':'<<savedgame.tag[te]<<"\033[m";
                cout<<'\n';
            }
        //}
        cout<<"0 "<<lang.search("exit")<<"\n"\
            <<lang.search("menu-choice")<<">>[   ]\033[4D";
        cin>>input;
        if(input=="0")return;
        if(all.set(setting.tag["level-data"],input)){
            all.help_words=lang.search("help-"+input);
            cls;
            if(!lang.without("story-"+input))show_story(lang.tag["story-"+input]);
            all.work();
            cls;
        }
        else{
            cls;
            cout<<"\033[91m"<<lang.search("level-unfound")<<"\033[m\n";
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
    for(size_t i=0;i<t;++i){
        if(s[i]=='$'){
            string ss;
            ++i;
            for(++i;s[i]!='}';++i)ss+=s[i];
            if(ss=="name")cout<<setting.tag["user-name"];
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
    cout<<"\n>>[ ]\033[2D";
    cin>>input;
}

#include "maze-game.h"
string input;
void init(){
    if(!setting.fill("save/setting.txt")){
        setting.tag["level-data"]="data/levels.data";
        setting.tag["lang-data"]="data/lang/en.txt";
        if(!setting.save("save/setting.txt")){
            cout<<"Error saving setting!\nTarget file path:save/setting.txt\n";
            cin>>input;
        }
    }
    if(!lang.fill(setting.tag["lang-data"])){
        cout<<"Language package unfound!\nExpected file path:"<<setting.tag["lang-data"]<<"\nPlease check save/setting.txt,and then continue.\n";
        cin>>input;
    }
}
bool game::set(string filename,string find){
    ifstream fin;
    fin.open(filename,ios::in);
    if(!fin.is_open())return false;
    string s;
    find='$'+find;
    unsigned short num,len;
    bool flag=true;
    while(getline(fin,s)){
        if(s==find){
            flag=false;
            break;
        }
    }
    if(flag)return false;
    fin>>num>>len;
    for(unsigned short i=0;i<num;++i){
        getline(fin,s);
        chunk te;
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
    cout<<s<<'\n'<<lang.tag["pause"]<<'\n';
    char c;
    cin>>c;
}
unsigned short game::work(){
    unsigned short a,b=focusing;
    while(true){
        a=chunks[focusing].work(b,help_words);
        switch(a){
            case 0:end_with(lang.tag["win"]);return 0;
            case 1:end_with(lang.tag["die-0"]);return 1;
            case 4:return 4;
        }
    }
    return 0;
}
void menu(){
    cout<<"\033[92m"<<lang.tag["game-name"]<<" v"<<version<<'\n'\
        <<"\033[93m===\n\033[m"\
        <<"1="<<lang.tag["menu-first"]<<'\n'\
        <<"2="<<lang.tag["menu-second"]<<'\n'\
        <<"0="<<lang.tag["exit"]<<'\n'\
        <<"s="<<lang.tag["menu-setting"]<<'\n'\
        <<lang.tag["menu-choice"]<<">>[ ]\033[2D";
    cin>>input;
    if(input=="0")exit(0);
    cls;
    if(input=="1")level_menu();
}
void game::clear(){
    chunks.clear();
}
void level_menu(){
    game all;
    while(true){
        for(string i="1-1";i!="1-4";++i[2]){
            cout<<i<<' '<<lang.tag["name-"+i]<<'\n';
        }
        cout<<"0 "<<lang.tag["exit"]<<"\n"\
            <<lang.tag["menu-choice"]<<">>[   ]\033[4D";
        cin>>input;
        if(input=="0")return;
        if(all.set("data/levels.data",input)){
            all.help_words=lang.tag["help-"+input];
            all.work();
            cls;
        }
        else{
            cls;
            cout<<"\033[91m"<<lang.tag["level-unfound"]<<"\033[m\n";
        }
        all.clear();
    }
}

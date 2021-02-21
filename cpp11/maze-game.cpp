#include "maze-game.h"
string input,input2;
void init(){
    if(!setting.fill("save/setting.txt")){
        setting.tag["level-data"]="data/levels.data";
        setting.tag["lang-data"]="data/lang/en.txt";
        setting.tag["saving"]="save/saving.txt";
        if(!setting.save("save/setting.txt")){
            cout<<"Error saving setting!\nTarget file path:save/setting.txt\n";
            cin>>input;
        }
    }
    if(!lang.fill(setting.tag["lang-data"])){
        cout<<"Language package unfound!\nExpected file path:"<<setting.tag["lang-data"]<<"\nPlease check save/setting.txt,and then continue.\n";
        cin>>input;
    }
    savedgame.fill(setting.tag["saving"]);
}
bool game::set(string filename,string find){
    ifstream fin;
    fin.open(filename,ios::in);
    if(!fin.is_open())return false;
    name=find;
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
        te.l=len;
        for(unsigned short j=0;j<len;++j){
            getline(fin,s);
            if(j==0)te.w=s.length();
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
            case 1:end_with(lang.search("die-0"));return 1;
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
    if(input=="1")level_menu();
    else if(input=="s")set_game();
}
void game::clear(){
    chunks.clear();
}
void level_menu(){
    game all;
    while(true){
        for(unsigned short i=1;i!=5;++i){
            string te="1-"+tos(i);
            cout<<"1-"<<i<<' '<<lang.search("name-"+te)<<' ';
            if(savedgame.without(te))cout<<lang.search("level-uncompleted");
            else cout<<lang.search("score")<<':'<<savedgame.tag[te];
            cout<<'\n';
        }
        cout<<"0 "<<lang.search("exit")<<"\n"\
            <<lang.search("menu-choice")<<">>[   ]\033[4D";
        cin>>input;
        if(input=="0")return;
        if(all.set(setting.tag["level-data"],input)){
            all.help_words=lang.search("help-"+input);
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
    cout<<"Input what you want to set:\n[Tag name] [Tag value]\n";
    cin>>input>>input2;
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

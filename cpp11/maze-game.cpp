#include "maze-game.h"
string version="0.1.0";
string input;
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
    cout<<s<<'\n'<<"Press any key to continue."<<'\n';
    char c;
    cin>>c;
}
unsigned short game::work(){
    unsigned short a,b=focusing;
    while(true){
        a=chunks[focusing].work(b,help_words);
        switch(a){
            case 0:end_with("Success!");return 0;
            case 1:end_with("You fell into the void!");return 1;
            case 4:return 4;
        }
    }
    return 0;
}
void menu(){
    cout<<"\033[92mMaze v"<<version<<'\n'\
        <<"\033[93m===\n\033[m"\
        <<"1=Start Adventure\n"\
        <<"2=Random Maze\n"\
        <<"0=Exit\n"\
        <<"Input your choice,and then press Enter\n>>[ ]\033[2D";
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
        cout<<"1-1 Hello Maze\n"\
            <<"1-2 Simple Maze\n"\
            <<"0 Exit\n"\
            <<"Choose>>[   ]\033[4D";
        cin>>input;
        if(input=="0")return;
        if(all.set("data/levels.data",input)){
            all.help_words="Use w,a,s,d to move.";
            all.work();
            cls;
        }
        else{
            cls;
            cout<<"\033[91mError opening level :(\033[m\n";
        }
        all.clear();
    }
}

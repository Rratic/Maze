#include "file-control.h"
bool tags::fill(string filename){
    ifstream fin;
    fin.open(filename,ios::in);
    if(!fin.is_open())return false;
    string s;
    while(getline(fin,s)){
        if(s.find(":")==s.npos)continue;
        size_t l=s.length();
        string a,b;
        bool flag=false;
        for(size_t i=0;i<l;++i){
            if(s[i]==':'&&!flag){
                flag=true;
                continue;
            }
            if(flag)b+=s[i];
            else a+=s[i];
        }
        tag[a]=b;
    }
    return true;
}
string tags::search(string tagname){
    if(tag.find(tagname)==tag.end()){
        if(tag.find("default")==tag.end())return "Err_unfound";
        return tag["default"];
    }
    return tag[tagname];
}
bool tags::save(string filename){
    ofstream fout;
    fout.open(filename,ios::out);
    if(!fout.is_open())return false;
    for(auto i:tag){
        fout<<i.first<<':'<<i.second<<endl;
    }
    return true;
}
bool tags::without(string x){
    return tag.find(x)==tag.end();
}
tags lang,setting,savedgame,count_levels;

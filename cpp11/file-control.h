#ifndef rra_file_control
#define rra_file_control
#include <fstream>
#include <unordered_map>
#include "maze-base.h"
using std::ifstream;
using std::ofstream;
using std::ios;
using std::unordered_map;
class tags{
    public:
    unordered_map<string,string>tag;
    bool fill(string filename);
    string search(string tagname);
    bool save(string filename);
    bool without(string x);
};
extern tags lang,setting,savedgame;
#endif
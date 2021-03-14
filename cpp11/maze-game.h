#ifndef rra_maze_game
#define rra_maze_game
#include "maze-generate.h"
#include <ctime>
using std::time_t;
using std::time;
using std::tm;
using std::localtime;
using std::rand;
using std::srand;
extern string input;
class game{
    public:
    unsigned short focusing;
    vector<chunk>chunks;
    string name,help_words;
    bool set(string filename,string find);
    unsigned short work();
    void clear();
};
void init();
void menu();
void world_menu();
void level_menu(unsigned short i);
void set_game();
void show_story(string s);
void rand_game();
#endif

#ifndef rra_maze_game
#define rra_maze_game
#include "maze-chunk.h"
extern string input;
class game{
    private:
    unsigned short focusing;
    vector<chunk>chunks;
    public:
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
#endif

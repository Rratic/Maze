#ifndef rra_maze_game
#define rra_maze_game
#include "maze-chunk.h"
#include "file-control.h"
#define version "0.2.0"
extern string input;
class game{
    private:
    unsigned short focusing;
    vector<chunk>chunks;
    public:
    string help_words;
    bool set(string filename,string find);
    unsigned short work();
    void clear();
};
void init();
void menu();
void level_menu();
void set_game();
#endif
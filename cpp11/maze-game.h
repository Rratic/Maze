#ifndef rra_maze_game
#define rra_maze_game
#include "maze-chunk.h"
extern string version;
extern string input;
class game{
    private:
    unsigned short focusing;
    string help_words;
    vector<chunk>chunks;
    public:
    bool set(string filename,string find);
    unsigned short work();
    void clear();
};
void menu();
void level_menu();
#endif
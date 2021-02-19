#ifndef rra_maze_game
#define rra_maze_game
#include "maze-chunk.h"
extern string version;
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
void menu();
void level_menu();
#endif
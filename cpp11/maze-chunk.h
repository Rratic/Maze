#ifndef rra_maze_map
#define rra_maze_map
#include <array>
#include <vector>
#include <fstream>
#include "maze-base.h"
using std::array;
using std::vector;
using std::ifstream;
using std::ofstream;
class chunk
{
    public:
    entity *player;
    array<array<block,16>,16>blocks;
    chunk();
    chunk(chunk &other);
    void putchunk();
    bool toline(string s,unsigned short line);
    bool set(string filename,string find);
    unsigned short work();
};
#endif

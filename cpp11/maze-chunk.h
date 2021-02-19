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
using std::ios;
class chunk
{
    public:
    entity *player;
    array<array<block,16>,16>blocks;
    chunk();
    chunk(const chunk &other);
    ~chunk();
    void putchunk();
    bool toline(string s,unsigned short line);
    unsigned short work(unsigned short &info,string words);
};
#endif

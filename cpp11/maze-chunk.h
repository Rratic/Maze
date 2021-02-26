#ifndef rra_maze_map
#define rra_maze_map
#include <array>
#include <vector>
#include "maze-base.h"
using std::array;
using std::vector;
class chunk
{
    public:
    entity *player;
    vector<entity>monsters;
    array<array<block,16>,16>blocks;
    unsigned short l,w;
    chunk();
    chunk(const chunk &other);
    ~chunk();
    void putchunk();
    bool toline(string s,unsigned short line);
    bool canmove(unsigned short x,unsigned short y,short xx,short yy);
    bool workmonsters(unsigned short id);
    unsigned short work(unsigned short &info,string words);
};
#endif

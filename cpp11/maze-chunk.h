#ifndef rra_maze_map
#define rra_maze_map
#include <array>
#include "maze-base.h"
#include "file-control.h"
using std::array;
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
    bool canmove(short x,short y,short xx,short yy);
    bool workmonsters(entity &i);
    unsigned short work(unsigned short &info,string words);
};
#endif

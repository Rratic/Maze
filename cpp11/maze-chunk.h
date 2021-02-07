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
    array<array<block,16>,16>blocks;
    chunk();
    chunk(chunk &other);
    void putchunk();
};
#endif

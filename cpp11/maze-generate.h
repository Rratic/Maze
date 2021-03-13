#ifndef rra_maze_generate
#define rra_maze_generate
#include "maze-chunk.h"
template<unsigned short l=15,unsigned short w=15>
void prim(unsigned short maze_len,unsigned short maze_wid,array<array<unsigned short,l>,w>&a);
#endif

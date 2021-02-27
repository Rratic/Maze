#ifndef rra_paint
#define rra_paint
#include <utility>
#include <string>
using std::pair;
using std::string;
using std::make_pair;
typedef pair<unsigned short, unsigned short> PAINT;
#define p_black 0
#define p_red 1
#define p_green 2
#define p_yellow 3
#define p_blue 4
#define p_purple 5
#define p_cyan 6
#define p_white 7
#define df(a) a + 30
#define lf(a) a + 90
#define db(a) a + 40
#define lb(a) a + 100
#define putcolor(a) "\033["<<a<<'m'
#define cls cout<<"\033[2J\033[H"
#define putbrush(a) putcolor(a.first)<<putcolor(a.second)
/*
d=dark
l=light
f=font
b=background
*/
extern string heart,heart2,star,arroww,arrowa,arrows,arrowd,arrow2w,arrow2a,arrow2s,arrow2d;
extern short mox[8],moy[8];
#endif

#ifndef rra_paint
#define rra_paint
#include <utility>
#include <string>
#include <cstdlib>
using std::pair;
using std::string;
using std::make_pair;
using std::system;
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
#define f_to_b(a) a + 10

// #define cls cout<<"\033[2J\033[H"
#ifndef _WIN32
#define cls system("clear")
#endif

#ifdef _WIN32
#define cls system("cls")
#endif

#ifndef DISABLE_COLOR
#define putcolor(a) "\033["<<a<<'m'
#define normalcolor "\033[m"
#define cursorleft(a) "\033["<<a<<"D"
#endif

#ifdef DISABLE_COLOR
#define putcolor(a) ""
#define normalcolor ""
#define cursorleft(a) ""
#endif

#define putbrush(a) putcolor(a.first)<<putcolor(a.second)


/*
d=dark
l=light
f=font
b=background
*/
extern string heart,heart2,star,arroww,arrowa,arrows,arrowd,arrow2w,arrow2a,arrow2s,arrow2d,death,whole_block;
extern short mox[8],moy[8];
#endif

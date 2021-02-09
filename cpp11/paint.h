#ifndef rra_paint
#define rra_paint
#include <utility>
using std::pair;
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
#define putcolor(a) cout << "\033[" << a << 'm'
/*
d=dark
l=light
f=font
b=background
*/
extern PAINT uni_paint;
void clearpaint();
#endif

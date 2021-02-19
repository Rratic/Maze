#include <cstdlib>
#include "maze-game.h"
using std::system;
int main(){
#ifdef _WIN32
    system("chcp 65001");//windows默认不是utf-8
    system("mode con lines=30");
#endif
    while(true){
        cls;
        menu();
    }
    return 0;
}

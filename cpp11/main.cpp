#include <cstdlib>
using namespace std;
int main(){
#ifdef _WIN32
    system("chcp 65001");//windows默认不是utf-8
#endif
    return 0;
}

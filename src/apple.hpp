#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <memory>
#include <curses.h>
#include <signal.h>

namespace snake{

class apple{
    public:
        apple(int _x,int _y):_x(x),_y(y){}

    private:
        int x;
        int y;
};
}

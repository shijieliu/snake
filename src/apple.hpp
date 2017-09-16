#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <memory>
#include <curses.h>
#include <signal.h>
#include <utility>

namespace snake{

class apple{
    public:
        apple(int _x,int _y):x(_x),y(_y){}

        int _x(){return x;}
        int _y(){return y;}

        void change();


    private:
        int get_random(int i){
            srand(time(NULL));
            return rand() % i;
        }

        int x;
        int y;
};

void apple::change(){
    x = get_random(LINES);
    y = get_random(COLS);
}
}

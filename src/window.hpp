#include <pthread.h>
#include <sys/time.h>
#include <signal.h>
#include <curses.h>
#include <unistd.h>
#include <pthread.h>

namespace snake{

class window{
    public:
        window(){init();}
        void run();
        void join();
    private:
        static void* clock(void* args);
        void init();//init屏幕设置
        pthread_t num;
};

void window::run(){
    //this->init();
    pthread_create(&num,NULL,clock,NULL);
}

void window::join(){
    void* thread_result;
    pthread_join(num,&thread_result);
}

void* window::clock(void* args){
    while(1){
        //alarm(1);
        int i = alarm(1);
        //printf("clock %d\n",i);
        sleep(1);
    }
}

void window::init(){
    initscr();
    cbreak();
    nonl();
    noecho();
    intrflush(stdscr,true);
    keypad(stdscr,true);
    refresh();
}

}

#ifndef GAME_H
#define GAME_H
#include "src/snake.hpp"
#include "src/window.hpp"
#include "src/apple.hpp"
#include "src/boomer.hpp"
#include "src/monitor.hpp"
#include "src/template.hpp"
#include <curses.h>
#include <memory>
#include <ctime>
#include <signal.h>
#include <pthread.h>

namespace snake{

class game{
    public:
        typedef std::shared_ptr<snake> ptr_snake;
        typedef std::shared_ptr<window> ptr_window;
        typedef std::shared_ptr<apple> ptr_apple;
        game();
        int run();

        template <typename T>
            void initial(T& tmp);
    private:
        ptr_snake one_snake;
        ptr_apple one_apple;
        //shared_ptr<boomer> many_boomer;
        //shared_ptr<monitor> one_monitor;
        ptr_window one_window;

        void mask_sig();
        sigset_t sigmask;

        int get_random(int i){
            srand(time(NULL));
            return rand() % i;
        }
};

template <>
void game::initial(ptr_window& tmp){//初始化window
    tmp = std::make_shared<window>();
}

game::game(){
    mask_sig();
    initial(one_window);
    initial(one_snake);
    initial(one_apple);
    //initial(many_boomer);
    //initial(one_monitor);
}

void game::mask_sig(){
    sigemptyset(&sigmask);
    sigaddset(&sigmask,SIGALRM);
    if( pthread_sigmask(SIG_SETMASK,&sigmask,NULL) != 0){
        perror("error in pthread_sigmask");
        exit(-1);
    }
}

int game::run(){
    one_window->run();
    one_snake->run();
    one_window->join();
    one_snake->join();
}

template <typename T>
void game::initial(T& tmp){
    int x = get_random(LINES);
    int y = get_random(COLS);
    tmp = std::make_shared<
        typename initial_trait<T>::value >(x,y);
}

}
/*
template <>
void game::initial(std::shared_ptr<boomer> & tmp){//初始化boomer
    int num = 10;
    tmp = make_shared<boomer>(num);
}

template <>
void game::initial(std::shared_ptr<monitor> const & tmp){//初始化monitor
    score_t score(0);
    level_t level(0);
    tmp = std::make_shared<monitor>(score,level);
}
*/


#endif

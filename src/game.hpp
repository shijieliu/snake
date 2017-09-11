#ifndef GAME_H
#define GAME_H
#include "src/snake.hpp"
#include "src/window.hpp"
#include "src/apple.hpp"
#include "src/boomer.hpp"
#include "src/monitor.hpp"
#include "src/template.hpp"
#include <curses.h>
#include <memeory>
#include <ctime>
#include <signal.h>

namespace snake{

class game{
    public:
        game();
        void start();
        int run();

        template <typename T>
            void initial(T const & tmp);
    private:
        shared_ptr<snake> one_snake;
        shared_ptr<apple> one_apple;
        shared_ptr<boomer> many_boomer;
        shared_ptr<monitor> one_monitor;
        shared_ptr<window> one_window;
        int get_random(int i){
            srand(time(NULL));
            return rand() % i;
        }
};

game::game(){
    initial(one_snake);
    initial(one_apple);
    initial(many_boomer);
    initial(one_monitor);
    initial(one_window);
}

template <typename T>
void game::initial(T const & tmp){
    int x = get_random(LINES);
    int y = get_random(COLS);
    tmp = make_shared<initial_trait<T>::value>(x,y);
}

template <>
void game::initial(shared_ptr<boomer> & tmp){//初始化boomer
    int num = 10;
    tmp = make_shared<boomer>(num);
}

template <>
void game::initial(shared_ptr<monitor> const & tmp){//初始化monitor
    score_t score(0);
    level_t level(0);
    tmp = make_shared<monitor>(score,level);
}

template <>
void game::initial(shared_ptr<window> const & tmp){//初始化window
    tmp = make_shared<window>();
}

}

void game::start(){
    //安装信号
    //子线程更新snake,apple,boomer
    //主线程catch 失败信号
}
void game::run(){}
}
#endif

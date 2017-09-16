#ifndef SNAKE_H
#define SNAKE_H

#include <memory>
#include <list>
#include <curses.h>
#include <signal.h>
#include <pthread.h>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <curses.h>
#include "src/apple.hpp"

namespace snake{

class snake{
    public:
        typedef void (*callback)(int);
        typedef std::shared_ptr<apple> ptr_apple;
        snake();
        snake(int const x, int const y);

        int run();
        void change_direction();
        void join();

    private:
        enum DIRR {UP,DOWN,LEFT,RIGHT};//方向
        std::list< 
            std::pair<int,int> > position;
        ptr_apple one_apple;
        enum DIRR direction; 
        pthread_t run_num;
        pthread_t listen_num;
        sigset_t _mask;
        static void* __run(void* args);//线程必须是全局函数
        static void* __listen(void* args);
        //void continue_run();//回调函数必须是全局函数或者静态成员函数
        void display();
        void adddisplay();
        void addnode(const std::pair<int,int>& node);
        void changeapple();
};

snake::snake(){
    position.clear();
    direction = DIRR::UP;
}

snake::snake(int const x, int const y){
    std::pair<int,int> node = std::make_pair(x,y);
    position.clear();
    position.push_back(node);
    position.push_back(std::make_pair(node.first-1,node.second));
    position.push_back(std::make_pair(node.first-2,node.second));
    direction = DIRR::UP;
    one_apple = std::make_shared<apple>(10,20);
}

int snake::run(){//启动snake线程
    if( 0 != pthread_create(&run_num,NULL,__run,(void*) this))
        exit(EXIT_FAILURE);
    if( 0 != pthread_create(&listen_num,NULL,__listen,(void*) this))
        exit(EXIT_FAILURE);
}

void snake::join(){
    void* thread_result;
    pthread_join(run_num,&thread_result);
    pthread_join(listen_num,&thread_result);
}

void* snake::__listen(void* args){//listen键盘输入
    snake* _this = static_cast<snake*>(args);
    char ch = '\0';
    do{
        ch = getch();
        if(ch == -1)continue;

        switch(ch){
            case 'w':
                _this->direction = DIRR::UP;break;
            case 's':
                _this->direction = DIRR::DOWN;break;
            case 'd':
                _this->direction = DIRR::RIGHT;break;
            case 'a':
                _this->direction = DIRR::LEFT;break;
            case 'q':
                pthread_exit(NULL);
            default:
                break;
        }
    }while(1);
}

void* snake::__run(void* args){
    snake* _this = static_cast<snake*>(args);

    int signo;
    //加入屏蔽信号集
    sigaddset(&(_this->_mask),SIGALRM);
    while(1){
        if(sigwait(&(_this->_mask),&signo) != 0){
            printf("error in sigwait");
            perror("error in sigwait");
            exit(-1);
        }
        if (signo == SIGALRM){
            std::pair<int,int> oldhead = _this->position.front();
            switch(_this->direction){
                case _this -> DIRR::UP:
                    oldhead.first -= 1;break;
                case _this -> DIRR::DOWN:
                    oldhead.first += 1;break;
                case _this -> DIRR::LEFT:
                    oldhead.second -= 1;break;
                case _this -> DIRR::RIGHT:
                    oldhead.second += 1;break;
                default:
                    perror("wrong direction");
                    exit(EXIT_FAILURE);
            }
            //处理吃苹果的过程
            if(oldhead.first == _this->one_apple->_x()
                    && oldhead.second == _this->one_apple->_y()){
                _this->addnode(oldhead);
                _this->adddisplay();
                _this->changeapple();
            }
            else{
                //蛇移动

                auto begin = _this->position.rbegin();
                auto next = ++begin;
                begin = _this->position.rbegin();
                while(next != _this->position.rend()){
                    *begin = *next;               
                    ++begin;
                    ++next;
                }

                
                    //begin->first = next->first;
                    //begin->second = next->second;
                _this -> position.front() = oldhead;
            //std::for_each(this->position.begin(),
            //        this->position.end(),
            //        [&](std::pair<int,int> i){
            //        printf("col %d, lines %d\n",i.first,i.second);});
                _this->display();
            }
        }
    }
 
}

void snake::changeapple(){
    one_apple->change();
}

void snake::addnode(const std::pair<int,int>& node){
    this->position.push_front(node);
}

void snake::adddisplay(){
    clear();
    std::for_each(this->position.begin(), 
            this->position.end(), 
            [ & ](const std::pair<int,int>& i){
            move(i.first, i.second);
            addstr("@");
            });
    refresh();
 
}

void snake::display(){
    clear();
    move(one_apple->_x(),one_apple->_y());
    addstr("*");
    std::for_each(this->position.begin(), 
            this->position.end(), 
            [ & ](std::pair<int,int> i){
            move(i.first, i.second);
            addstr("@");
            });
    refresh();
 
}
}
#endif

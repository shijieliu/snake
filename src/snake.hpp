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

namespace snake{

class snake{
    public:
        typedef void (*callback)(int);
        snake();
        snake(int const x, int const y);

        int run();
        void change_direction();
        void join();

    private:
        enum DIRR {UP,DOWN,LEFT,RIGHT};//方向
        std::list< 
            std::pair<int,int> > position;
        enum DIRR direction; 
        pthread_t run_num;
        pthread_t listen_num;
        sigset_t _mask;
        static void* __run(void* args);//线程必须是全局函数
        static void* __listen(void* args);
        void continue_run();//回调函数必须是全局函数或者静态成员函数
        void display();
};

snake::snake(){
    position.clear();
    direction = DIRR::UP;
}

snake::snake(int const x, int const y){
    std::pair<int,int> node = std::make_pair(x,y);
    position.clear();
    position.push_back(node);
    direction = DIRR::UP;
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

    //安装信号，接受时continue_run
    //先屏蔽信号，然后sigwait
    //屏蔽信号

    //if( pthread_sigmask(SIG_BLOCK,&(_this->_mask),NULL) != 0){
    //    perror("error in pthread_sigmask");
    //    exit(-1);
    //}
    
    //处理阻塞的信号
    _this->continue_run();

}

void snake::continue_run(){
    int signo;
    //加入屏蔽信号集
    sigaddset(&(this->_mask),SIGALRM);
    while(1){
        //printf("continue_run\n");
        if(sigwait(&_mask,&signo) != 0){
            printf("error in sigwait");
            perror("error in sigwait");
            exit(-1);
        }
        if (signo == SIGALRM){
            //printf("direction:%d\n",this->direction);
            std::pair<int,int> oldhead = this->position.front();
            switch(this->direction){
                case this -> DIRR::UP:
                    oldhead.first -= 1;break;
                case this -> DIRR::DOWN:
                    oldhead.first += 1;break;
                case this -> DIRR::LEFT:
                    oldhead.second -= 1;break;
                case this -> DIRR::RIGHT:
                    oldhead.second += 1;break;
                default:
                    perror("wrong direction");
                    exit(EXIT_FAILURE);
            }

            for (auto begin = this -> position.rbegin(),
                    next = ++begin;
                    next != this -> position.rend();
                    ++begin,++next){
                *next = *begin;
            }
            this -> position.front() = oldhead;
            //std::for_each(this->position.begin(),
            //        this->position.end(),
            //        [&](std::pair<int,int> i){
            //        printf("col %d, lines %d\n",i.first,i.second);});
            display();
        }
    }
        
}

void snake::display(){
    clear();
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

#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <memory>
#include "src/snake.hpp"
#include "src/apple.hpp"

namespace snake{

template <typename T>
class initial_trait{//trait出shared_ptr的原有类型
    public:
        typedef T value;
};

template <>
class initial_trait<std::shared_ptr<snake>>{
    public:
        typedef snake value;
};

//template <>
//class initial_trait<std::shared_ptr<apple>>{
//    public:
//        typedef apple value;
//};

struct score_t{
    int _value;
    score_t(int _x):_value(_x){}
    int value() const {return _value;}
};

struct level_t{
    int _value;
    level_t(int x):_value(x){}
    int value() const {return _value;}
};
}

#endif

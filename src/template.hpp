#ifndef TEMPLATE_H
#define TEMPLATE_H

namespace snake{

template <typename T>
class initial_trait{//trait出shared_ptr的原有类型
    public:
        typedef T value;
}

template <>
class initial_trait<shared_ptr<snake>>{
    public:
        typedef snake value;
}

template <>
class initial_trait<shared_ptr<apple>>{
    public:
        typedef apple value;
}

struct score_t{
    int value;
    score_t(int _x):value(_x){}
    int value() const {return value;}
};

struct level_t{
    int value;
    level_t(int x):value(x){}
    int value() const {return value;}
};
}

#endif

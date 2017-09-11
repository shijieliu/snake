#ifndef SNAKE_H
#define SNAKE_H

#include <memory>
#include <vector>
#include <curses.h>

namespace snake{

class snake{
    public:
        snake():_x(0),_y(0),_length(0){}
        snake(int const & x, int const &y,int const& size):
            _x(x),_y(y),_length(size){}

        int size() const {return _length;}
        int get_x() const {return _x;}
        int get_y() const {return _y;}

    private:
        int _length;
        int _x;
        int _y;
};
}
#endif

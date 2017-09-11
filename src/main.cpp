#include "src/game.hpp"
#include <memory>

int main(){
    shared_ptr<snake::game> one_game = make_shared<snake::game>();
    one_game->start();
    while(one_game->run()){}
}


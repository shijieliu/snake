#include "src/game.hpp"
#include <memory>

int main(){
    std::shared_ptr<snake::game> one_game = std::make_shared<snake::game>();
    one_game->run();
}


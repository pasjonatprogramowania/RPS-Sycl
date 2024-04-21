#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <sycl/sycl.hpp>

class GameEngine{
    sycl::queue q;

    GameEngine();
    virtual ~GameEngine() = 0;

    std::vector<std::vector<Tile>> getNewState(std::vector<std::vector<Tile>>&);
};
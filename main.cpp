#include <iostream>
#include <memory>

#include "src/game.hpp"

int main()
{
    {
        std::vector<std::vector<bool>> grid = {
            {false, false, false, false, false, false, false, false, false, false},
            {false, false, false, true, false, false, false, false, false, false},
            {false, false, false, false, true, false, false, false, false, false},
            {false, false, true, true, true, false, false, false, false, false},
            {false, false, false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false, false, false},
        };

        int row_limit;
        int col_limit;
        int generation;
        int latency;

        std::cout << "Welcome to Conway\'s Game Of life." << std::endl;
        std::cout << "What is the axis X limit ?" << std::endl;
        std::cin >> col_limit;
        std::cout << "What is the axis Y limit ?" << std::endl;
        std::cin >> row_limit;
        std::cout << "How many generation ?" << std::endl;
        std::cin >> generation;
        std::cout << "What latency you want between each generation ? (in ms)" << std::endl;
        std::cin >> latency;

        std::unique_ptr<gameoflife::game> g = std::make_unique<gameoflife::game>(row_limit, col_limit, latency);
        g->start(generation);
    }
    return 0;
}
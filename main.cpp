#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "gui.hpp"
#include "life.hpp"

void render(int generation, std::vector<std::vector<std::shared_ptr<cell>>> const &grid)
{
    system("clear");
    std::cout << "Generation: " << std::to_string(generation) << std::endl;
    for (int row = 0; row < grid.size(); row++)
    {
        for (int col = 0; col < grid[0].size(); col++)
        {
            if (grid[row][col]->alive)
            {
                std::cout << 'X';
            }
            else
            {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
}

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

        life *main_life = new life(25, 25);
        render(0, main_life->get_grid());
        for (int i = 0; i < 20; i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            int generation = main_life->next_generation();
            render(generation, main_life->get_grid());
        }
    }
    return 0;
}
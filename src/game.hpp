#pragma once

#include <memory>
#include <thread>

#include "assets/life.hpp"
#include "gui/gui.hpp"

namespace gameoflife
{
    class game
    {
        std::unique_ptr<life> LIFE;
        std::shared_ptr<gui> GUI;

    public:
        game(int const &row_limit, int const &col_limit, int const &latency) : LIFE(std::make_unique<life>(row_limit, col_limit)), GUI(std::make_shared<gui>(latency)) {}
        game(std::vector<std::vector<bool>> const &grid, int const &latency) : LIFE(std::make_unique<life>(grid)), GUI(std::make_shared<gui>(latency)) {}

        void start(int const &n)
        {
            std::thread life_thread([&]()
                                    { LIFE->process_n_generations(n, GUI); });
            std::thread gui_thread(&gui::process, GUI);
            life_thread.join();
            gui_thread.join();
        }
    };
}
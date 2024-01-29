#pragma once

#include <iostream>
#include <thread>
#include <queue>
#include <string>
#include <vector>
#include <mutex>
#include <chrono>
#include <condition_variable>

#include "../assets/life.hpp"

namespace gameoflife
{
    class gui
    {
        std::mutex mutex;
        std::condition_variable condition;
        std::queue<std::pair<int, std::vector<std::vector<std::shared_ptr<cell>>>>> generations_to_render;
        bool calculation = true;
        int latency;

    public:
        gui(int const &latency) : latency(latency) {}
        bool const
        is_generations_to_render_empty()
        {
            return generations_to_render.empty();
        }

        void add_generation(int const &generation_n, std::vector<std::vector<std::shared_ptr<cell>>> const &generation)
        {
            std::unique_lock<std::mutex> lock(mutex);
            generations_to_render.push({generation_n, generation});
            if (generation_n == -1)
            {
                calculation = false;
            }
            lock.unlock();
            condition.notify_one();
        }

        void render(int const &generation_n, std::vector<std::vector<std::shared_ptr<cell>>> const &generation_to_render)
        {
            system("clear");
            std::cout << "Generation: " << std::to_string(generation_n) << (calculation ? '*' : ' ') << std::endl;
            for (int row = 0; row < generation_to_render.size(); row++)
            {
                for (int col = 0; col < generation_to_render[0].size(); col++)
                {
                    if (generation_to_render[row][col]->is_alive())
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

        void process()
        {
            while (true)
            {
                std::unique_lock<std::mutex> lock(mutex);
                condition.wait(lock, [this]
                               { return !is_generations_to_render_empty(); });

                auto [generation_n, generation_to_render] = generations_to_render.front();
                if (generation_n == -1)
                {
                    lock.unlock();
                    break;
                }
                generations_to_render.pop();

                lock.unlock();

                render(generation_n, generation_to_render);
                std::this_thread::sleep_for(std::chrono::milliseconds(latency));
            }
        }
    };
}
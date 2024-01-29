#pragma once

#include <vector>
#include <memory>

#include "cell.hpp"
#include "../gui/gui.hpp"

namespace gameoflife
{
    class life
    {
        int generation = 0;
        int const row_limit;
        int const col_limit;
        std::vector<std::vector<std::shared_ptr<cell>>> grid;

    public:
        life(int const &row_limit, int const &col_limit) : row_limit(row_limit), col_limit(col_limit)
        {
            initialize_random_generation();
        }

        life(std::vector<std::vector<bool>> const &grid_start) : row_limit(grid_start.size()), col_limit(grid_start[0].size())
        {
            if (grid_start.empty())
            {
                throw std::invalid_argument("Start Grid cannot be empty!");
            }
            for (int row = 0; row < row_limit; row++)
            {
                grid.push_back({});
                for (int col = 0; col < col_limit; col++)
                {
                    grid[row].emplace_back(std::make_shared<cell>(grid_start[row][col]));
                }
            }
        }

        std::vector<std::vector<std::shared_ptr<cell>>> const get_grid() { return grid; }
        int const get_generation() { return generation; }

        void initialize_random_generation()
        {
            std::srand(time(0));
            for (int row = 0; row < row_limit; row++)
            {
                grid.push_back({});
                for (int col = 0; col < col_limit; col++)
                {
                    int random_int = std::rand() % 4;
                    bool random_bool = random_int == 1;
                    grid[row].emplace_back(std::make_shared<cell>(random_bool)); // 25% to be alive
                }
            }
        }
        bool is_inbound(int const &row, int const &col)
        {
            return 0 <= row && row < grid.size() && 0 <= col && col < grid[0].size();
        }
        int calculate_cell_alive_neighbours(int const &row, int const &col)
        {
            int alive_neighbours = 0;
            // Check neighbours create a score.
            std::vector<std::pair<int, int>> neighbours_moves = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
            for (auto const &[move_row, move_col] : neighbours_moves)
            {
                int neighbour_row = row + move_row;
                int neighbour_col = col + move_col;
                if (!is_inbound(neighbour_row, neighbour_col))
                    continue;
                alive_neighbours += grid[neighbour_row][neighbour_col]->is_alive() ? 1 : 0;
            }
            return alive_neighbours;
        }

        int next_generation()
        {
            std::vector<std::vector<std::shared_ptr<cell>>> tmp_grid;

            for (int row = 0; row < row_limit; row++)
            {
                tmp_grid.push_back({});
                for (int col = 0; col < col_limit; col++)
                {
                    tmp_grid[row].emplace_back(std::make_shared<cell>(grid[row][col]->is_alive()));
                }
            }

            for (int row = 0; row < row_limit; row++)
            {
                for (int col = 0; col < col_limit; col++)
                {
                    int alive_neighbours = calculate_cell_alive_neighbours(row, col);
                    if (grid[row][col]->is_alive() && (alive_neighbours < 2 || alive_neighbours > 3))
                    {
                        tmp_grid[row][col]->dies();
                    }
                    else if (!grid[row][col]->is_alive() && alive_neighbours == 3)
                    {
                        tmp_grid[row][col]->lives();
                    }
                }
            }
            grid.swap(tmp_grid);
            return ++generation;
        }

        void process_n_generations(int const &n, std::shared_ptr<gui> const &GUI)
        {
            for (int i = 0; i < n; i++)
            {
                next_generation();
                GUI->add_generation(i, grid);
            }
            GUI->add_generation(-1, grid);
        }
    };
}
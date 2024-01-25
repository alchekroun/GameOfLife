#include <vector>
#include <memory>

struct cell
{
    bool alive;

    cell(bool initial_state) : alive(initial_state) {}
    void dies() { alive = false; }
    void lives() { alive = true; }
    void react() { alive = !alive; }
};

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

    life(int const &row_limit, int const &col_limit, std::vector<std::vector<bool>> const &start) : row_limit(row_limit), col_limit(col_limit)
    {
        for (int row = 0; row < row_limit; row++)
        {
            grid.push_back({});
            for (int col = 0; col < col_limit; col++)
            {
                grid[row].emplace_back(std::make_shared<cell>(start[row][col]));
            }
        }
    }

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

    std::vector<std::vector<std::shared_ptr<cell>>> const get_grid() { return grid; }
    int const get_generation() { return generation; }

    bool isInbound(int const &row, int const &col)
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
            if (!isInbound(neighbour_row, neighbour_col))
                continue;
            alive_neighbours += grid[neighbour_row][neighbour_col]->alive ? 1 : 0;
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
                tmp_grid[row].emplace_back(std::make_shared<cell>(grid[row][col]->alive));
            }
        }

        for (int row = 0; row < row_limit; row++)
        {
            for (int col = 0; col < col_limit; col++)
            {
                int alive_neighbours = calculate_cell_alive_neighbours(row, col);
                if (grid[row][col]->alive && (alive_neighbours < 2 || alive_neighbours > 3))
                {
                    tmp_grid[row][col]->dies();
                }
                else if (!grid[row][col]->alive && alive_neighbours == 3)
                {
                    tmp_grid[row][col]->lives();
                }
            }
        }
        grid.swap(tmp_grid);
        return ++generation;
    }
};
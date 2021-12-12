//Advent of Code 2021
//Day 11: Dumbo Octopus
//Part 1
#include "../Shared.h"

constexpr int32_t SIMULATE_STEPS = 100;
constexpr int32_t GRID_ROW_SIZE = 10;
constexpr int32_t GRID_COL_SIZE = 10;

std::array<std::array<int32_t, GRID_COL_SIZE>, GRID_ROW_SIZE> grid{};
std::array<std::array<bool, GRID_COL_SIZE>, GRID_ROW_SIZE> flashed{};

//-------------------------------------------------------------------------------------------------------------------//

void UpdateOctopus(const int32_t x, const int32_t y,
                    std::array<std::array<int32_t, GRID_COL_SIZE>, GRID_ROW_SIZE>& grid)
{
    grid[y][x]++;

    if(grid[y][x] == 10)
    {
        int32_t startX = (x - 1 >= 0) ? (x - 1) : 0;
        int32_t startY = (y - 1 >= 0) ? (y - 1) : 0;
        int32_t endX = (x + 1 > grid.size() - 1) ? (grid.size() - 1) : (x + 1);
        int32_t endY = (y + 1 > grid[0].size() - 1) ? (grid[0].size() - 1) : (y + 1);

        for(int32_t idx = startX; idx <= endX; ++idx)
        {
            for(int32_t idy = startY; idy <= endY; ++idy)
                UpdateOctopus(idx, idy, grid);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t main()
{
    const std::vector<std::string> lines = ReadTextFile("input.txt");
    if(lines.empty())
        return -1;

    //Fill grid
    for(int32_t y = 0; y < lines.size(); ++y)
    {
        for(int32_t x = 0; x < lines[0].size(); ++x)
            grid[y][x] = lines[y][x] - '0';
    }

    //Logic
    int32_t flashes = 0;
    for(int32_t i = 0; i < SIMULATE_STEPS; ++i)
    {
        for(int32_t y = 0; y < grid.size(); ++y)
        {
            for(int32_t x = 0; x < grid[0].size(); ++x)
                UpdateOctopus(x, y, grid);
        }

        //Count flashes
        for(int32_t y = 0; y < grid.size(); ++y)
        {
            for(int32_t x = 0; x < grid[0].size(); ++x)
            {
                if(grid[y][x] > 9)
                {
                    ++flashes;
                    grid[y][x] = 0;
                }
            }
        }
    }

    std::cout << "Total flashes after " << SIMULATE_STEPS << " steps: " << flashes << std::endl;

    return 0;
}
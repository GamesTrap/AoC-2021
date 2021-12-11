//Advent of Code 2021
//Day 9: Smoke Basin
//Part 2
#include "../Shared.h"

#include <algorithm>

struct Point
{
    int32_t X;
    int32_t Y;
};

//-------------------------------------------------------------------------------------------------------------------//

bool IsLowPoint(const int32_t x, const int32_t y, const std::vector<std::vector<int32_t>>& points)
{
    int32_t ySize = points.size();
    int32_t xSize = points[0].size();

    int32_t up = (x == 0) ? 10 : points[y][x - 1];
    int32_t left = (y == 0) ? 10 : points[y - 1][x];

    int32_t down = (x == xSize - 1) ? 10 : points[y][x + 1];
    int32_t right = (y == ySize - 1) ? 10 : points[y + 1][x];

    if(points[y][x] >= up || points[y][x] >= left ||
       points[y][x] >= down || points[y][x] >= right)
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t GetBasinSize(const int32_t x, const int32_t y, const std::vector<std::vector<int32_t>>& points,
                     std::vector<std::vector<int32_t>>& bitMask)
{
    if(x == -1 || y == -1 || y == points.size() || x == points[0].size())
        return 0;
    if(points[y][x] == 9 || bitMask[y][x] == 1)
        return 0;

    bitMask[y][x] = 1;

    return GetBasinSize(x, y - 1, points, bitMask) + GetBasinSize(x - 1, y, points, bitMask) +
           GetBasinSize(x, y + 1, points, bitMask) + GetBasinSize(x + 1, y, points, bitMask) + 1;
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t main()
{
    const std::vector<std::string> lines = ReadTextFile("input.txt");
    if(lines.empty())
        return -1;

    //Load numbers
    std::vector<std::vector<int32_t>> points{};
    for(const auto& line : lines)
    {
        std::vector<int32_t> row{};
        for(const auto c : line)
            row.push_back(c - '0');
        points.push_back(row);
    }

    //Logic
    std::vector<std::vector<int32_t>> bitMask = std::vector(points.size(), std::vector<int32_t>(points[0].size(), 0));
    std::vector<int32_t> basins{};
    std::vector<Point> lowPoints{};
    for(int32_t y = 0; y < points.size(); ++y) //Get all low points
    {
        for(int32_t x = 0; x < points[0].size(); ++x)
        {
            if(IsLowPoint(x, y, points))
                lowPoints.push_back({x, y});
        }
    }
    for(const auto& lP : lowPoints) //Get all basins
        basins.push_back(GetBasinSize(lP.X, lP.Y, points, bitMask));
    std::sort(basins.begin(), basins.end(), std::greater()); //Sort basins

    std::cout << "Product of 3 largest basins: " << basins[0] * basins[1] * basins[2] << std::endl;

    return 0;
}
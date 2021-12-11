//Advent of Code 2021
//Day 9: Smoke Basin
//Part 1
#include "../Shared.h"

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
    int32_t riskLevelSum = 0;
    for(int32_t y = 0; y < points.size(); ++y)
    {
        for(int32_t x = 0; x < points[0].size(); ++x)
        {
            if(IsLowPoint(x, y, points))
                riskLevelSum += points[y][x] + 1;
        }
    }

    std::cout << "Sum of risk levels: " << riskLevelSum << std::endl;

    return 0;
}
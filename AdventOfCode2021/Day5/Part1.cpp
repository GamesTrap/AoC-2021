//Advent of Code 2021
//Day 5: Hydrothermal Venture
//Part 1
#include "../Shared.h"

struct Point
{
    int32_t X;
    int32_t Y;
};
struct Line
{
    Point A;
    Point B;
};
std::vector<std::vector<int32_t>> map;

//-------------------------------------------------------------------------------------------------------------------//

void PrintMap(const std::vector<std::vector<int32_t>>& map)
{
    for(const auto row : map)
    {
        for(const auto col : row)
        {
            if(col == 0)
                std::cout << ".";
            else
                std::cout << col;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<Line> ParsePoints(const std::vector<std::string>& lines)
{
    std::vector<Line> result{};

    for(const auto& line : lines)
    {
        if(line.empty())
            continue;

        const auto pointSplit = SplitString(line, " -> ");

        if(pointSplit.size() != 2)
        {
            std::cerr << "Failed to parse line: " << line << std::endl;
            continue;
        }

        const auto num1Split = SplitString(pointSplit[0], ",");
        const auto num2Split = SplitString(pointSplit[1], ",");

        if(num1Split.size() != 2 || num2Split.size() != 2)
        {
            std::cerr << "Failed to parse line: " << line << std::endl;
            continue;
        }

        Line l;
        l.A.X = std::stoi(num1Split[0]);
        l.A.Y = std::stoi(num1Split[1]);
        l.B.X = std::stoi(num2Split[0]);
        l.B.Y = std::stoi(num2Split[1]);

        result.push_back(l);
    }

    return result;
}

//-------------------------------------------------------------------------------------------------------------------//

Point GetMaxPoint(const std::vector<Line>& lines)
{
    Point p{};

    for(const auto row : lines)
    {
        if(row.A.X > p.X)
            p.X = row.A.X;
        else if(row.A.Y > p.Y)
            p.Y = row.A.Y;
        else if(row.B.X > p.X)
            p.X = row.B.X;
        else if(row.B.Y > p.Y)
            p.Y = row.B.Y;
    }

    return p;
}

//-------------------------------------------------------------------------------------------------------------------//

void DrawLine(const Line& line)
{
    if(line.A.X == line.B.X)
    {
        int32_t aY = line.A.Y, bY = line.B.Y;
        if(aY > bY)
            std::swap(aY, bY);

        for(int32_t y = aY; y <= bY; ++y)
            map[y][line.A.X]++;
    }
    else if(line.A.Y == line.B.Y)
    {
        int32_t aX = line.A.X, bX = line.B.X;
        if(aX > bX)
            std::swap(aX, bX);

        for(int32_t x = aX; x <= bX; ++x)
            map[line.A.Y][x]++;
    }
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t main()
{
    const std::vector<std::string> inputLines = ReadTextFile("input.txt");
    if(inputLines.empty())
        return -1;

    //Load all points
    const std::vector<Line> lines = ParsePoints(inputLines);

    //Logic
    //Get max X and Y
    const Point maxPoint = GetMaxPoint(lines);

    //Allocate map
    map.resize(maxPoint.Y + 1);
    for(auto& row : map)
        row.resize(maxPoint.X + 1);

    //Fill map
    for(const auto& l : lines)
        DrawLine(l);

    // PrintMap(map);

    //Get answer
    int32_t ans = 0;
    for(const auto& row : map)
    {
        for(const auto& col : row)
        {
            if(col > 1)
                ans++;
        }
    }
    std::cout << "Answer: " << ans << std::endl;

    return 0;
}
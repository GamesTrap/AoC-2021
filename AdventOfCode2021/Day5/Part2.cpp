//Advent of Code 2021
//Day 5: Hydrothermal Venture
//Part 2
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

void PrintMap(const std::vector<std::vector<int32_t>> map)
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

        auto pointSplit = SplitString(line, " -> ");

        if(pointSplit.size() != 2)
        {
            std::cerr << "Failed to parse line: " << line << std::endl;
            continue;
        }

        auto num1Split = SplitString(pointSplit[0], ",");
        auto num2Split = SplitString(pointSplit[1], ",");

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
    int32_t x, y;
    int32_t n = std::max(std::abs(line.B.X - line.A.X), std::abs(line.B.Y - line.A.Y));

    for(int32_t i = 0; i <= n; ++i)
    {
        x = line.A.X + (line.B.X - line.A.X) * i / n;
        y = line.A.Y + (line.B.Y - line.A.Y) * i / n;

        map[y][x]++;
    }
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t main()
{
    std::vector<std::string> inputLines = ReadTextFile("input.txt");

    //Load all points
    std::vector<Line> lines = ParsePoints(inputLines);

    //Logic
    //Get max X and Y
    Point maxPoint = GetMaxPoint(lines);

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
//Advent of Code 2021
//Day 1: Sonar Sweep
//Part 2
#include "../Shared.h"

int32_t main()
{
    std::vector<std::string> lines = ReadTextFile("input.txt");
    if(lines.empty())
        return -1;

    uint32_t increaseCount = 0;
    int32_t a, b, c, d;

    int32_t count = 0;
    for(const auto& line : lines)
    {
        if(count == 0)
            a = std::stoi(line);
        else if(count == 1)
            b = std::stoi(line);
        else if(count == 2)
            c = std::stoi(line);
        else
        {
            d = std::stoi(line);

            if(b + c + d > a + b + c)
                increaseCount++;

            a = b;
            b = c;
            c = d;
        }

        ++count;
    }

    std::cout << increaseCount << " measurement sums are larger than the previous sum" << std::endl;

    return 0;
}
//Advent of Code 2021
//Day 1: Sonar Sweep
//Part 1
#include "../Shared.h"

int32_t main()
{
    const std::vector<std::string> lines = ReadTextFile("input.txt");
    if(lines.empty())
        return -1;

    //Measurement logic
    int32_t lastMeasurement = -1;
    uint32_t increaseCount = 0;

    for(const auto& line : lines)
    {
        if(line.empty())
            continue;

        const int32_t measurement = std::stoi(line);

        if(measurement > lastMeasurement && lastMeasurement >= 0)
           ++increaseCount;

        lastMeasurement = measurement;
    }

    std::cout << increaseCount << " measurements are larger than the previous measurements" << std::endl;

    return 0;
}
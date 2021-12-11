//Advent of Code 2021
//Day 2: Dive!
//Part 1
#include "../Shared.h"

int32_t main()
{
    const std::vector<std::string> lines = ReadTextFile("input.txt");
    if(lines.empty())
        return -1;

    //Logic
    int32_t horz = 0, depth = 0;
    for(const auto& line : lines)
    {
        if(line.empty())
            continue;

        const std::vector<std::string> split = SplitString(line, " ");
        if(split.size() != 2)
            continue;

        if(split[0] == "forward")
            horz += std::stoi(split[1]);
        else if(split[0] == "down")
            depth += std::stoi(split[1]);
        else if(split[0] == "up")
            depth -= std::stoi(split[1]);
    }

    std::cout << "Horizontal: " << horz << " Depth: " << depth << " Result: " << (horz * depth) << std::endl;

    return 0;
}
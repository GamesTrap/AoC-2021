//Advent of Code 2021
//Day 6: Lanternfish
//Part 1
#include "../Shared.h"

constexpr int32_t DAYS_TO_SIMULATE = 80;
constexpr int32_t MAX_LIFETIME = 9;

//-------------------------------------------------------------------------------------------------------------------//

uint64_t CountFish(const std::array<uint64_t, MAX_LIFETIME>& table)
{
    uint64_t count = 0;
    for(const auto n : table)
        count += n;
    return count;
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t main()
{
    const std::vector<std::string> lines = ReadTextFile("input.txt");
    if(lines.empty())
        return -1;

    //Parse input
    std::array<uint64_t, MAX_LIFETIME> table{};
    std::array<uint64_t, MAX_LIFETIME> backTable{};
    const auto split = SplitString(lines[0], ",");
    for(const auto& s : split)
        table[std::stoi(s)]++;

    //Logic
    for(uint32_t d = 0; d < DAYS_TO_SIMULATE; ++d)
    {
        if(d == 0)
            std::cout << "Initial State: " << CountFish(table) << " fish" << '\n';

        backTable = {}; //Clear back table

        backTable[8] += table[0];
        backTable[6] += table[0];

        for(uint32_t i = 0; i < MAX_LIFETIME; ++i)
            backTable[i - 1] += table[i];

        table = backTable; //Set new values

        std::cout << "After Day " << (d + 1) << ": " << CountFish(table) << " fish" << '\n';
    }

    return 0;
}
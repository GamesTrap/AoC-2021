//Advent of Code 2021
//Day 7: The Treachery of Whales
//Part 1
#include "../Shared.h"

#include <algorithm>

int32_t main()
{
    std::vector<std::string> lines = ReadTextFile("input.txt");

    //Parse input
    std::vector<int32_t> nums{};
    const auto split = SplitString(lines[0], ",");
    for(const auto s: split)
        nums.push_back(std::stoi(s));

    //Get min and max
    const int32_t max = *std::max_element(nums.cbegin(), nums.cend());
    const int32_t min = *std::min_element(nums.cbegin(), nums.cend());

    //Logic
    int32_t res = std::numeric_limits<int32_t>::max();
    int32_t alignPos = 0;
    for(int32_t i = min; i <= max; ++i)
    {
        int32_t fuelSum = 0;
        for(const auto n : nums)
            fuelSum += (std::max(i, n) - std::min(i, n));

        if(fuelSum < res)
        {
            res = fuelSum;
            alignPos = i;
        }
    }

    std::cout << "Total fuel cost: " << res << " Position: " << alignPos << std::endl;

    return 0;
}
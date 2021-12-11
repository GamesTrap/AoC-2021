//Advent of Code 2021
//Day 8: Seven Segment Search
//Part 1
#include "../Shared.h"

constexpr int32_t UNIQUE_SIGNAL_PATTERN_COUNT = 10;
constexpr int32_t DIGIT_OUTPUT_VALUE_COUNT = 4;

int32_t main()
{
    const std::vector<std::string> lines = ReadTextFile("input.txt");

    //Logic
    int32_t digitCount = 0;
    for(const auto& line : lines)
    {
        const auto split = SplitString(line, " ");

        int32_t splitIndex = UNIQUE_SIGNAL_PATTERN_COUNT + 1; //Skip the '|'
        for(int32_t i = 0; i < DIGIT_OUTPUT_VALUE_COUNT; ++i, ++splitIndex)
        {
            switch(split[splitIndex].size())
            {
            case 2: //Digit 1
            case 3: //Digit 7
            case 4: //Digit 4
            case 7: //Digit 8
                ++digitCount;
                break;

            default:
                break;
            }
        }
    }

    std::cout << "Digits 1, 4, 7 and 8 appear " << digitCount << " times" << std::endl;

    return 0;
}
//Advent of Code 2021
//Day 8: Seven Segment Search
//Part 2
#include "../Shared.h"

#include <unordered_map>
#include <algorithm>

//Digit 0 = 6 Segments
//Digit 1 = 2 Segments
//Digit 2 = 5 Segments
//Digit 3 = 5 Segments
//Digit 4 = 4 Segments
//Digit 5 = 5 Segments
//Digit 6 = 6 Segments
//Digit 7 = 3 Segments
//Digit 8 = 7 Segments
//Digit 9 = 6 Segments

constexpr int32_t UNIQUE_SIGNAL_PATTERN_COUNT = 10;
constexpr int32_t DIGIT_OUTPUT_VALUE_COUNT = 4;

//-------------------------------------------------------------------------------------------------------------------//

std::size_t GetIntersectionSize(const std::string& a, const std::string& b)
{
    std::string tmp;
    std::set_intersection(a.cbegin(), a.cend(), b.cbegin(), b.cend(), std::back_inserter(tmp));
    return tmp.size();
}

//-------------------------------------------------------------------------------------------------------------------//

std::vector<std::string>::const_iterator FindByIntersectionSize(const std::vector<std::string>& v, const std::string& other, int32_t size)
{
    for (auto it = v.cbegin(); it != v.cend(); ++it)
    {
        if (GetIntersectionSize(*it, other) == size)
            return it;
    }

    return {};
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t main()
{
    const std::vector<std::string> lines = ReadTextFile("input.txt");

    //Logic
    int32_t sum = 0;
    for(const auto& line : lines)
    {
        auto split = SplitString(line, " ");

        std::unordered_map<std::string, int32_t> signalPatterns;
        std::unordered_map<int32_t, std::string> signalPatternsReverse;
        std::vector<std::string> length5, length6;

        //Decipher digits
        int32_t splitIndex = 0;
        for(int32_t i = 0; i < UNIQUE_SIGNAL_PATTERN_COUNT; ++i, ++splitIndex)
        {
            std::sort(split[splitIndex].begin(), split[splitIndex].end());

            switch(split[splitIndex].size())
            {
            case 2:
                signalPatterns[split[splitIndex]] = 1;
                break;
            case 3:
                signalPatterns[split[splitIndex]] = 7;
                signalPatternsReverse[7] = split[splitIndex];
                break;
            case 4:
                signalPatterns[split[splitIndex]] = 4;
                signalPatternsReverse[4] = split[splitIndex];
                break;
            case 5:
                length5.push_back(split[splitIndex]);
                break;
            case 6:
                length6.push_back(split[splitIndex]);
                break;
            case 7:
                signalPatterns[split[splitIndex]] = 8;
                break;

            default:
                break;
            }
        }

        //Find 3
        auto it = FindByIntersectionSize(length5, signalPatternsReverse[7], 3);
        signalPatterns[*it] = 3;
        signalPatternsReverse[3] = *it;
        length5.erase(it);
        //Find 5
        it = FindByIntersectionSize(length5, signalPatternsReverse[4], 3);
        signalPatterns[*it] = 5;
        length5.erase(it);
        //Deduce 2
        signalPatterns[length5[0]] = 2;
        //Find 9
        it = FindByIntersectionSize(length6, signalPatternsReverse[3], 5);
        signalPatterns[*it] = 9;
        length6.erase(it);
        //Find 0
        it = FindByIntersectionSize(length6, signalPatternsReverse[7], 3);
        signalPatterns[*it] = 0;
        length6.erase(it);
        //Deduce 6
        signalPatterns[length6[0]] = 6;

        ++splitIndex; //Skip the '|'

        //Sum up the digits
        int32_t currNum = 0;
        for(int32_t i = 0; i < DIGIT_OUTPUT_VALUE_COUNT; ++i, ++splitIndex)
        {
            std::sort(split[splitIndex].begin(), split[splitIndex].end());
            currNum *= 10;
            currNum += signalPatterns[split[splitIndex]];
        }

        sum += currNum;
    }

    std::cout << "Sum of all output value: " << sum << std::endl;

    return 0;
}
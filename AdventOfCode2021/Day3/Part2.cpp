//Advent of Code 2021
//Day 3: Binary Diagnostic
//Part 2
#include "../Shared.h"
#include <bitset>

int32_t main()
{
    const std::vector<std::string> lines = ReadTextFile("input.txt");
    if(lines.empty())
        return -1;

    //Calculate Oxygen ratings
    std::vector<std::string> OxygenRatings = lines;
    for(std::size_t i = 0; i < lines[0].size(); ++i) //For each bit
    {
        const std::vector<std::string> temp = OxygenRatings;
        OxygenRatings.clear();
        uint32_t ones = 0, zeros = 0;
        for(std::size_t j = 0; j < temp.size(); ++j)
        {
            if(temp[j][i] == '0')
                zeros++;
            else if(temp[j][i] == '1')
                ones++;
        }

        for(std::size_t j = 0; j < temp.size(); ++j)
        {
            if(ones >= zeros && temp[j][i] == '1')
                OxygenRatings.push_back(temp[j]);
            else if(ones < zeros && temp[j][i] == '0')
                OxygenRatings.push_back(temp[j]);
        }

        if(OxygenRatings.size() <= 1)
            break;
    }

    //Calculate CO2 ratings
    std::vector<std::string> CO2Ratings = lines;
    for(std::size_t i = 0; i < lines[0].size(); ++i) //For each bit
    {
        const std::vector<std::string> temp = CO2Ratings;
        CO2Ratings.clear();
        uint32_t ones = 0, zeros = 0;
        for(std::size_t j = 0; j < temp.size(); ++j)
        {
            if(temp[j][i] == '0')
                zeros++;
            else if(temp[j][i] == '1')
                ones++;
        }

        for(std::size_t j = 0; j < temp.size(); ++j)
        {
            if(ones >= zeros && temp[j][i] == '0')
                CO2Ratings.push_back(temp[j]);
            else if(ones < zeros && temp[j][i] == '1')
                CO2Ratings.push_back(temp[j]);
        }

        if(CO2Ratings.size() <= 1)
            break;
    }

    const std::bitset<32> oxygenRating(OxygenRatings[0]);
    const std::bitset<32> co2Rating(CO2Ratings[0]);

    std::cout << "Oxygen generator rating: " << oxygenRating.to_ulong() <<
                 " CO2 scrubber rating: " << co2Rating.to_ulong() <<
                 " Life support rating: " << (oxygenRating.to_ulong() * co2Rating.to_ulong()) << std::endl;

    return 0;
}
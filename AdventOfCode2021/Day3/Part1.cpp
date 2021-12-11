//Advent of Code 2021
//Day 3: Binary Diagnostic
//Part 1
#include "../Shared.h"
#include <bitset>

int32_t main()
{
    const std::vector<std::string> lines = ReadTextFile("input.txt");
    if(lines.empty())
        return -1;

    std::string strGammaRate{}, strEpsilonRate{};
    for(std::size_t i = 0; i < lines[0].size(); ++i) //For each bit
    {
        int32_t ones = 0, zeros = 0;
        for(std::size_t j = 0; j < lines.size(); ++j) //For each number
        {
            if(lines[j][i] == '0')
                zeros++;
            else if(lines[j][i] == '1')
                ones++;
        }

        strGammaRate += (ones > zeros ? '1' : '0');
        strEpsilonRate += (ones < zeros ? '1' : '0');
    }

    const std::bitset<32> gammaRate(strGammaRate);
    //Epsilon rate is the binary inverse of the gamma rate
    const std::bitset<32> epsilonRate(strEpsilonRate);

    std::cout << "Gamma rate: " << gammaRate.to_ulong() << " Epsilon rate: " << epsilonRate.to_ulong() <<
                 " Power consumption: " << (gammaRate.to_ulong() * epsilonRate.to_ulong()) << std::endl;

    return 0;
}
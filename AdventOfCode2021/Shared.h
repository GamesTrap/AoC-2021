//This file contains shared functions for the Advent of Code 2021 solutions.

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

std::vector<std::string> ReadTextFile(const std::filesystem::path& filePath)
{
    std::ifstream file(filePath);
    if(!file.good() || !file.is_open())
    {
        std::cerr << "Could not open " << filePath << "!" << std::endl;
        return {};
    }

    std::vector<std::string> lines{};
    std::string line;
    while(std::getline(file, line))
        lines.push_back(line);
    file.close();

    return lines;
}
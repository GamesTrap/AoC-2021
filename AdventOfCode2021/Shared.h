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

//-------------------------------------------------------------------------------------------------------------------//

std::vector<std::string> SplitString(const std::string_view string,
                                     const std::string_view delimiters)
{
	std::size_t start = 0;
	std::size_t end = string.find_first_of(delimiters);

	std::vector<std::string> result;

	while (end <= std::string::npos)
	{
		std::string token = std::string(string.substr(start, end - start));

		if (!token.empty())
			result.push_back(token);

		if (end == std::string::npos)
			break;

		start = end + 1;
		end = string.find_first_of(delimiters, start);
	}

	return result;
}
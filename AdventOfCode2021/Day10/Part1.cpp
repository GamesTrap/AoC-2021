//Advent of Code 2021
//Day 10: Syntax Scoring
//Part 1
#include "../Shared.h"

#include <unordered_map>
#include <stack>

std::unordered_map<char, int32_t> ScoreMap = {
    {')', 3},
    {']', 57},
    {'}', 1197},
    {'>', 25137},
};

//-------------------------------------------------------------------------------------------------------------------//

std::unordered_map<char, char> CloseBracketsMap = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'},
    {'<', '>'},
};

//-------------------------------------------------------------------------------------------------------------------//

int32_t main()
{
    const std::vector<std::string> lines = ReadTextFile("sample.txt");
    if(lines.empty())
        return -1;

    //Logic
    int32_t score = 0;
    std::stack<char> syntaxStack{};
    for(const auto& line : lines)
    {
        syntaxStack = {};
        for(const auto c : line)
        {
            if(c != ')' && c != ']' && c != '}' && c != '>')
                syntaxStack.push(c);
            else
            {
                if(CloseBracketsMap[syntaxStack.top()] != c)
                {
                    std::cout << syntaxStack.top() << c << " ";
                    score += ScoreMap[c];
                }
                syntaxStack.pop();
            }
        }
    }

    std::cout << "\nSyntax error score: " << score << std::endl;

    return 0;
}
//Advent of Code 2021
//Day 10: Syntax Scoring
//Part 1
#include "../Shared.h"

#include <unordered_map>
#include <stack>
#include <algorithm>

std::unordered_map<char, int32_t> ScoreMap = {
    {')', 1},
    {']', 2},
    {'}', 3},
    {'>', 4},
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
    const std::vector<std::string> lines = ReadTextFile("input.txt");
    if(lines.empty())
        return -1;

    //Logic
    std::stack<char> syntaxStack{};
    std::vector<std::string> incompleteLines{};
    for(const auto& line : lines) //Get all incomplete lines
    {
        syntaxStack = {};
        bool syntaxError = false;
        for(const auto c : line)
        {
            if(c != ')' && c != ']' && c != '}' && c != '>')
                syntaxStack.push(c);
            else
            {
                if(CloseBracketsMap[syntaxStack.top()] != c)
                {
                    syntaxError = true;
                    break;
                }
                syntaxStack.pop();
            }
        }

        if(!syntaxError)
            incompleteLines.push_back(line);
    }

    //Get all auto completion strings
    std::vector<std::string> autoComplete{};
    for(const auto& line : incompleteLines)
    {
        syntaxStack = {};
        for(const auto c : line)
        {
            if(c != ')' && c != ']' && c != '}' && c != '>')
                syntaxStack.push(c);
            else
                syntaxStack.pop();
        }

        //Create auto complete string
        std::string autoCompleteStr{};
        while(!syntaxStack.empty())
        {
            autoCompleteStr += CloseBracketsMap[syntaxStack.top()];
            syntaxStack.pop();
        }
        autoComplete.push_back(autoCompleteStr);
    }

    //Calculate score
    std::vector<int64_t> scores{};
    for(const auto& line : autoComplete)
    {
        int64_t score = 0;
        for(const auto c : line)
        {
            score *= 5;
            score += ScoreMap[c];
        }
        scores.push_back(score);
    }
    std::sort(scores.begin(), scores.end());

    std::cout << "Auto complete: " << std::endl;
    for(int32_t i = 0; i < autoComplete.size(); ++i)
        std::cout << incompleteLines[i] << " -> " << autoComplete[i] << std::endl;
    std::cout << "Middle score: " << scores[scores.size() / 2] << std::endl;

    return 0;
}
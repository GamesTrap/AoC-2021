//Advent of Code 2021
//Day 4: Giant Squid
//Part 1
#include "../Shared.h"

struct Board
{
    std::vector<std::vector<int32_t>> Nums{};
};
std::vector<int32_t> drawNumbers{};
std::vector<Board> boards{};

constexpr int32_t GRID_SIZE = 5;

//-------------------------------------------------------------------------------------------------------------------//

bool IsBoardWon(const Board& board)
{
    bool won;

    //Row check
    for(int32_t y = 0; y < board.Nums.size(); ++y)
    {
        won = true;
        for(int32_t x = 0; x < board.Nums[y].size(); ++x)
        {
            if(board.Nums[y][x] != -1)
            {
                won = false;
                break;
            }
        }

        if(won)
            return true;
    }

    //Column check
    for(int32_t x = 0; x < board.Nums.size(); ++x)
    {
        won = true;
        for(int32_t y = 0; y < board.Nums[x].size(); ++y)
        {
            if(board.Nums[y][x] != -1)
            {
                won = false;
                break;
            }
        }

        if(won)
            return true;
    }

    return false;
}

//-------------------------------------------------------------------------------------------------------------------//

int32_t main()
{
    std::vector<std::string> lines = ReadTextFile("input.txt");
    if(lines.empty())
        return -1;

    //Parse first line to numbers
    std::vector<std::string> split = SplitString(lines[0], ",");
    for(const std::string& s : split) //Convert nums to ints
        drawNumbers.emplace_back(std::stoi(s));

    //Load all boards
    for(std::size_t i = 1; i < lines.size(); ++i)
    {
        if(lines[i].empty())
            continue;

        Board b;
        for(int32_t j = 0; j < GRID_SIZE; ++i, ++j)
        {
            split = SplitString(lines[i], " ");

            std::vector<int32_t> row{};
            for(const std::string& s : split)
                row.emplace_back(std::stoi(s));
            b.Nums.push_back(row);
        }

        boards.push_back(b);
    }

    //Logic
    int32_t winIndex = -1;
    int32_t currDrawNum = 0;
    for(const auto dN : drawNumbers)
    {
        currDrawNum = dN;
        //Mark boards
        for(auto& b : boards)
        {
            for(int32_t y = 0; y < b.Nums.size(); ++y)
            {
                for(int32_t x = 0; x < b.Nums[y].size(); ++x)
                {
                    if(b.Nums[y][x] == dN)
                        b.Nums[y][x] = -1;
                }
            }
        }

        //Check for win. Only column or rows count
        for(int32_t b = 0; b < boards.size(); ++b)
        {
            if(IsBoardWon(boards[b]))
            {
                winIndex = b;
                break;
            }
        }

        if(winIndex != -1)
            break;
    }

    std::cout << "Board: " << (winIndex + 1) << " won!" << '\n';

    //Unmarked number sum
    int32_t sum = 0;
    for(int32_t c = 0; c < boards[winIndex].Nums.size(); ++c)
    {
        for(int32_t r = 0; r < boards[winIndex].Nums[c].size(); ++r)
        {
            if(boards[winIndex].Nums[c][r] != -1)
                sum += boards[winIndex].Nums[c][r];
        }
    }
    std::cout << "Unmarked number sum: " << sum << '\n';
    std::cout << "Final score: " << (sum * currDrawNum) << '\n';

    return 0;
}
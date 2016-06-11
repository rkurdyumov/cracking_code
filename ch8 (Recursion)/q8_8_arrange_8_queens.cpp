#include <iostream>
#include <fstream> // for printing solutions to file
#include <iomanip> // for setw()
#include <vector>

static const int NROWS = 8;

void SaveBoard(std::ostream &out, std::vector<int> &columns)
{
    for (int r = 0; r < NROWS; ++r)
    {
        for (int c = 0; c < NROWS; ++c)
        {
            out << std::setw(2) << ((columns[r] == c) ? ("Q") : ("."));
        }
        out << std::endl;
    }
    out << std::endl;
}

// Check for queens in the same column and same diagonal
bool CheckValidPosition(std::vector<int> &columns, int row)
{
    for (int i = 0; i < row; ++i)
    {
        int diff = columns[row] - columns[i];
        if (diff == 0 || diff == (row-i) || -diff == (row-i))
            return false;
    }
    return true;
}

bool PlaceQueens(std::vector<std::vector<int>> &arrangements, int row)
{
    if (row == NROWS)
        return true;

    // Columns stores the column number for the i'th row
    static std::vector<int> columns(NROWS);
    for (int i = 0; i < NROWS; ++i)
    {
        columns[row] = i;
        if (CheckValidPosition(columns, row))
        {
            bool last_queen = PlaceQueens(arrangements, row+1);
            if (last_queen)
            {
                arrangements.push_back(columns);
            }
        }
    }
    return false;
}

int main()
{
    std::ofstream result_file("q8_8_result.txt");
    if (!result_file.is_open())
    {
        std::cout << "Cannot write result file." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::vector<int>> arrangements;
    PlaceQueens(arrangements, 0);
    
    int num_arr = arrangements.size();

    std::cout << "There are " << num_arr << " ways of arranging 8 queens." 
        << std::endl;

    for (int i = 0; i < num_arr; ++i)
    {
        SaveBoard(result_file, arrangements[i]);
    }
    result_file.close();

    return 0;
}

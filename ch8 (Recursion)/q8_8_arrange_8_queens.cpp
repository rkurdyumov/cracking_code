/*
Write an algorithm to print all ways of arranging eight queens on a chess board 
so that none of them share the same row, column or diagonal.
*/

#include <iostream>
#include <fstream> // for printing solutions to file
#include <iomanip> // std::setw
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
        out << "\n";
    }
    out << "\n";
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

// Solution: Starting from the top row, recursively attempt to place a queen
// in each possible valid position.  Backtrack when we place the last queen or
// when we run out of valid positions. Save the possible arrangements so we can
// examine them later.
// Time complexity: O(n!) where n = number of queens
bool PlaceQueensRecursive(std::vector<std::vector<int>> &arrangements,
        std::vector<int> & columns, int row)
{
    if (row == NROWS)
        return true;
    for (int i = 0; i < NROWS; ++i)
    {
        columns[row] = i;
        if (CheckValidPosition(columns, row))
        {
            bool last_queen = PlaceQueensRecursive(arrangements, columns, row+1);
            if (last_queen)
            {
                arrangements.push_back(columns);
            }
        }
    }
    return false;
}

std::vector<std::vector<int>> PlaceQueens()
{
    std::vector<std::vector<int>> arrangements;
    // Columns stores the column number for the i'th row
    std::vector<int> columns(NROWS);
    PlaceQueensRecursive(arrangements, columns, 0);
    return arrangements;
}

int main()
{
    std::ofstream result_file("q8_8_result.txt");
    if (!result_file.is_open())
    {
        std::cout << "Cannot write result file.\n";
        exit(EXIT_FAILURE);
    }

    std::vector<std::vector<int>> arrangements = PlaceQueens();
    
    int num_arr = arrangements.size();
    std::cout << "There are " << num_arr << " ways of arranging 8 queens.\n";

    // Save the results to a file so they don't clutter the terminal output
    for (int i = 0; i < num_arr; ++i)
    {
        SaveBoard(result_file, arrangements[i]);
    }
    result_file.close();
}

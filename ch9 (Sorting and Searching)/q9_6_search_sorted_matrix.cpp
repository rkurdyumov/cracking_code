/*
Given a matrix in which each row and each column is sorted, write a method to 
find an element in it.
*/

#include <iostream>
#include <iomanip> // std::setw
#include <algorithm> // std::max
#include <utility> // std::pair

const int NCOLS = 3;
const int NROWS = 4;

// Solution: start in upper right corner. If the current value is too big, 
// move left.  If it is too small, move down.
std::pair<int, int> FindElement(int M[NROWS][NCOLS], int elem)
{
    int row = 0;
    int col = NCOLS-1;
    while (row < NROWS && col >= 0)
    {
        if (M[row][col] == elem) 
            return std::make_pair(row, col); 
        else if (M[row][col] > elem)
            col--;
        else
            row++;
    }
    return std::make_pair(-1, -1);
}

void PrintMatrix(int M[NROWS][NCOLS])
{
    for (int r = 0; r < NROWS; ++r)
    {
        for (int c = 0; c < NCOLS; ++c)
        {
            std::cout << std::setw(3) << M[r][c];
        }
        std::cout << "\n";
    }
}

int main()
{
    int M[NROWS][NCOLS] = {
        {0, 3, 7}, 
        {1, 4, 8}, 
        {5, 6, 9}, 
        {6, 8, 10}};
    
    PrintMatrix(M);

    int elem = 5;
    std::pair<int, int> p = FindElement(M, elem);
    std::cout << "Element " << elem << " is at [" << p.first << "," << 
        p.second << "]\n";    
    
    int elem2 = 2;
    std::pair<int, int> p2 = FindElement(M, elem2);
    std::cout << "Element " << elem2 << " is at [" << p2.first << "," << 
        p2.second << "]\n";    
}


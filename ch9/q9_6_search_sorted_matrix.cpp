#include <iostream>
#include <iomanip> // for setw()
#include <algorithm> // for max()

void FindElement(int M[][3], int nR, int nC, int &r, int &c, int elem)
{
    r = c = -1;
    int row = 0;
    int col = nC-1;
    while (row < nR && col >= 0)
    {
        if (M[row][col] == elem) 
        {
            r = row; c = col; return;
        }
        else if (M[row][col] > elem)
            col--;
        else
            row++;
    }
}

void PrintMatrix(int M[][3], int nR, int nC)
{
    for (int r = 0; r < nR; ++r)
    {
        for (int c = 0; c < nC; ++c)
        {
            std::cout << std::setw(3) << M[r][c];
        }
        std::cout << std::endl;
    }
}

int main()
{
    int M[4][3] = {{0, 3, 7}, {1, 4, 8}, {5, 6, 9}, {6, 8, 10}};
    PrintMatrix(M, 4, 3);

    int r, c;
    int elem = 5;
    FindElement(M, 4, 3, r, c, elem);
    std::cout << "Element " << elem << " is at [" << r << "," << c << "]" << std::endl;    
    return 0;
}


/*
Given an image represented by an NxN matrix, where each pixel in the image is 4
bytes, write a method to rotate the image by 90 degrees. Can you do this in 
place?
*/

#include <iostream>

const size_t N = 4; // current code assumes NxN matrix

static void print_mat(int M[][N], size_t N)
{
    for (size_t r = 0; r < N; ++r)
    {
        for (size_t c = 0; c < N; ++c)
        {
            std::cout << M[r][c] << " "; 
        }
        std::cout << "\n";
    }
}

static void rotate_mat(int M[][N], size_t N)
{
    for (size_t row = 0; row < N/2; ++row)
    {
        size_t first = row;
        size_t last = N - row - 1;
        for (size_t i = first; i < last; ++i)
        {
            int top = M[first][i]; // store top
            M[first][i] = M[last - (i - first)][first]; // left -> top
            M[last - (i - first)][first] = M[last][last - (i - first)]; // bottom -> left
            M[last][last - (i - first)] = M[i][last]; // right -> bottom
            M[i][last] = top; // top -> right
        }
    }
}

int main()
{
    int M[][N] = {
        {11, 12, 13, 14},
        {15, 16, 17, 18},
        {19, 20, 21, 22},
        {23, 24, 25, 26}};
    
    print_mat(M, N); 
    rotate_mat(M, N);
    std::cout << "\nAfter rotation:\n";
    print_mat(M, N);
}

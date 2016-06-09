/*
Write an algorithm such that if an element in an MxN matrix is 0, its entire row 
and column is set to 0.
*/

#include <iostream>
#include <vector>

const size_t M = 3, N = 4;

static void print_mat(int mat[M][N], size_t M, size_t N)
{
    for (size_t r = 0; r < M; ++r)
    {
        for (size_t c = 0; c < N; ++c)
        {
            std::cout << mat[r][c] << " "; 
        }
        std::cout << std::endl;
    }
}

// Solution 1: Uses O(N+M) space when N or M > 32
static void zero_mat(int mat[M][N], size_t M, size_t N)
{
    std::vector<bool> row_zeros(M,false);
    std::vector<bool> col_zeros(N,false);
    for (size_t r = 0; r < M; ++r)
    {
        for (size_t c = 0; c < N; ++c)
        {
            if (mat[r][c] == 0)
            {
                row_zeros[r] = true;
                col_zeros[c] = true;
            }
        }
    }
    for (size_t r = 0; r < M; ++r)
    {
        for (size_t c = 0; c < N; ++c)
        {
            if (row_zeros[r] == true || col_zeros[c] == true)
            {
                mat[r][c] = 0;
            }
        }
    }
}

// Solution 2: Uses O(1) space when N and M <= 32
static void zero_small_mat(int mat[M][N], size_t M, size_t N)
{
    uint32_t row_zeros = 0, col_zeros = 0;
    for (size_t r = 0; r < M; ++r)
    {
        for (size_t c = 0; c < N; ++c)
        {
            if (mat[r][c] == 0)
            {
                row_zeros |= 1<<r;
                col_zeros |= 1<<c;
            }
        }
    }
    for (size_t r = 0; r < M; ++r)
    {
        for (size_t c = 0; c < N; ++c)
        {
            if ((row_zeros & (1<<r)) || (col_zeros & (1<<c)))
            {
                mat[r][c] = 0;
            }
        }
    }
}

int main()
{
    int mat[M][N] = {
        {1, 2, 3, 4},
        {1, 0, 3, 4},
        {1, 2, 3, 0}};
    
    print_mat(mat, M, N);
    if (M > 32 || N > 32)
        zero_mat(mat, M, N);
    else
        zero_small_mat(mat, M, N);
    std::cout << "Zero row and column for any zero elem:\n";
    print_mat(mat, M, N);
}

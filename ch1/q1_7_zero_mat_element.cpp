#include <iostream>
#include <vector>
#include <cstdint>

const int M = 3, N = 4;

static void print_mat(int mat[M][N], int M, int N)
{
    for (int r = 0; r < M; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            std::cout << mat[r][c] << " "; 
        }
        std::cout << std::endl;
    }
}

static void zero_mat(int mat[M][N], int M, int N)
{
    std::vector<bool> row_zeros(M,false);
    std::vector<bool> col_zeros(N,false);
    for (int r = 0; r < M; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            if (mat[r][c] == 0)
            {
                row_zeros[r] = true;
                col_zeros[c] = true;
            }
        }
    }
    for (int r = 0; r < M; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            if (row_zeros[r] == true || col_zeros[c] == true)
            {
                mat[r][c] = 0;
            }
        }
    }
}

static void zero_small_mat(int mat[M][N], int M, int N)
{
    uint32_t row_zeros = 0, col_zeros = 0;
    for (int r = 0; r < M; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            if (mat[r][c] == 0)
            {
                row_zeros |= 1<<r;
                col_zeros |= 1<<c;
            }
        }
    }
    for (int r = 0; r < M; ++r)
    {
        for (int c = 0; c < N; ++c)
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
    int mat[M][N] = {{1,2,3,4},{1,0,3,4},{1,2,3,0}};
    print_mat(mat, M, N);
    if (M > 32 || N > 32)
        zero_mat(mat, M, N);
    else
        zero_small_mat(mat, M, N);
    std::cout << std::endl;
    print_mat(mat, M, N);
}

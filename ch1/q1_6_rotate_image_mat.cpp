#include <iostream>

const int N = 4;

static void print_mat(int M[][N], int N)
{
    for (int r = 0; r < N; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            std::cout << M[r][c] << " "; 
        }
        std::cout << std::endl;
    }
}

static void rotate_mat(int M[][N], int N)
{
    for (int row = 0; row < N/2; ++row)
    {
        int first = row;
        int last = N - row - 1;
        for (int i = first; i < last; ++i)
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
    int M[][N] = {{11,12,13,14},{15,16,17,18},{19,20,21,22},{23,24,25,26}};
    print_mat(M, N);
    rotate_mat(M, N);
    std::cout << std::endl;
    print_mat(M, N);
}

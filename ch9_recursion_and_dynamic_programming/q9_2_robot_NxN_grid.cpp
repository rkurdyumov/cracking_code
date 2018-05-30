/*
Imagine a robot sitting on the upper left hand corner of an NxN grid. The robot 
can only move in two directions: right and down. How many possible paths are 
there for the robot?
FOLLOW UP
Imagine certain squares are "off limits", such that the robot can not step on 
them. Design an algorithm to get all possible paths for the robot.
*/

#include <iostream>
#include <vector>
#include <iomanip> // std::setw

static const int N = 4; // grid dimension

// Basic dynamic-programming approach that works for small (n choose k)
// Based on:
// C(n, k) = n! / (n-k)! * k!
//         = [n * (n-1) *....* 1]  / [ ( (n-k) * (n-k-1) * .... * 1) * 
//                                             ( k * (k-1) * .... * 1 ) ]
// After simplifying, we get
// C(n, k) = [n * (n-1) * .... * (n-k+1)] / [k * (k-1) * .... * 1]
//
// Also, C(n, k) = C(n, n-k)  // we can change r to n-r if r > n-r 
// See: 
// www.geeksforgeeks.org/space-and-time-efficient-binomial-coefficient
int Combination(int n, int k)
{
    if (k > n-k) k = n-k;
    
    int result = 1;
    for (int i = 0; i < k; ++i)
    {
        result *= (n-i);
        result /= (i+1);
    }
    return result;
}

// Solution: recursively check if we can go right and/or down. If we get to the
// end, we have a valid path so add to it our list.  After returning from each
// recursive call, we erase the element we just added so we can reuse the same
// curr_path variable (avoids allocating a new curr_path on each recursive call).
void GetPathsRecursive(bool free_grid[N][N], std::vector<std::vector<bool>> & paths, 
        std::vector<bool> & curr_path, int x, int y)
{
    if (x == N-1 && y == N-1)
        paths.push_back(curr_path);
    
    if (y < N-1 && free_grid[x][y+1]) // try right
    {
        curr_path.push_back(true); 
        GetPathsRecursive(free_grid, paths, curr_path, x, y+1);
        curr_path.erase(curr_path.end()-1);
    }
    if (x < N-1 && free_grid[x+1][y]) // try down
    {
        curr_path.push_back(false);
        GetPathsRecursive(free_grid, paths, curr_path, x+1, y);
        curr_path.erase(curr_path.end()-1);
    }
}

std::vector<std::vector<bool>> GetPaths(bool free_grid[N][N])
{
    std::vector<std::vector<bool>> paths;
    std::vector<bool> curr_path;
   
    // Start in upper left corner with empty path, recursively find all valid paths
    GetPathsRecursive(free_grid, paths, curr_path, 0, 0);
    return paths;
}

void PrintPaths(std::vector<std::vector<bool>> &paths)
{
    for (size_t r = 0; r < paths.size(); ++r)
    {
        for (size_t c = 0; c < paths[r].size(); ++c)
        {
            std::cout << ((paths[r][c]) ? ("R") : ("D"));
        }
        std::cout << "\n";
    }
}

void PrintGrid(bool free_grid[N][N])
{
    for (size_t r = 0; r < N; ++r)
    {
        for (size_t c = 0; c < N; ++c)
        {
            std::cout << std::setw(2) << free_grid[r][c];
        }
        std::cout << "\n";
    }
}

int main()
{
    // Part 1: verify that there are (2N-2) choose (N_1) possible paths when
    // all squares are free
    bool all_free_grid[N][N] = {{1, 1, 1, 1}, 
                                {1, 1, 1, 1}, 
                                {1, 1, 1, 1}, 
                                {1, 1, 1, 1}};

    std::vector<std::vector<bool>> all_paths = GetPaths(all_free_grid);
    
    std::cout << "Grid with all squares free:\n";
    PrintGrid(all_free_grid);
    std::cout << "We expect " << Combination(2*N-2, N-1) << " paths. We have: " <<
        all_paths.size() << " paths.\n";

    // Part 2: verify that recursive algorithm works with some squares off limits
    bool free_grid[N][N] = {{1, 1, 1, 0}, 
                            {1, 0, 1, 1}, 
                            {1, 1, 1, 1}, 
                            {1, 1, 0, 1}};
    
    std::cout << "\nCustom grid:\n";
    PrintGrid(free_grid);
 
    std::vector<std::vector<bool>> paths = GetPaths(free_grid);

    std::cout << "Starting from upper left corner, paths are:\n";
    PrintPaths(paths);
}


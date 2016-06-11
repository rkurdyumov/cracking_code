#include <iostream>
#include <vector>

static const int M = 4;

// Basic dynamic-programming that works for small (n choose k)
int Combination(int n, int k)
{
    if (k*2 > n) k = n-k; // symmetry
    if (k == 0) return 1;
    
    int result = n;
    for (int i = 2; i <= k; ++i)
    {
        result *= (n-i-1);
        result /= i;
    }
    return result;
}

void GetPathsRecursive(bool free_grid[M][M], std::vector<std::vector<bool>> &paths, 
        int curr_path, int x, int y)
{
    if (x == M-1 && y == M-1) return;
    bool try_right = false, try_down = false;
    
    std::vector<bool> path_before_split = paths[curr_path];

    if (y < M-1 && free_grid[x][y+1]) // try right
    {
        paths[curr_path].push_back(true);
        GetPathsRecursive(free_grid, paths, curr_path, x, y+1);
        try_right = true;
    }
    if (x < M-1 && free_grid[x+1][y]) // try down
    {
        if (try_right) {
            paths.push_back(std::vector<bool>(path_before_split));
            curr_path = paths.size() - 1;
        }
        paths[curr_path].push_back(false);
        GetPathsRecursive(free_grid, paths, curr_path, x+1, y);
        try_down = true;
    }
    if (!try_right && !try_down)
        paths[curr_path].erase(paths[curr_path].end() - 1);
    return;
}

std::vector<std::vector<bool>> GetPaths(bool free_grid[M][M])
{
    std::vector<std::vector<bool>> paths;
    paths.push_back(std::vector<bool>());
   
    // Start in upper left corner with empty path, recursively find all valid paths
    GetPathsRecursive(free_grid, paths, 0, 0, 0);
    
    // Remove incomplete solutions
    // We have 2*M-2 total steps, and M-1 times to choose right that uniquely 
    // determine the path, so (2*M-2) choose (M-1) steps for a valid path
    int num_steps = Combination(2*M-2, M-1);
    for (std::vector<std::vector<bool>>::iterator it = paths.begin(); it != paths.end(); )
    {
        if ((int)it->size() < num_steps)
            paths.erase(it);
        else
            ++it;
    }
    return paths;
}

void PrintPaths(std::vector<std::vector<bool>> &paths)
{
    for (size_t i = 0; i < paths.size(); ++i)
    {
        for (size_t j = 0; j < paths[i].size(); ++j)
        {
            std::cout << ((paths[i][j]) ? ("R") : ("D"));
        }
        std::cout << std::endl;
    }
}

int main()
{
    bool free_grid[M][M] = {{1, 1, 1, 0}, 
                            {1, 0, 1, 1}, 
                            {1, 1, 1, 1}, 
                            {1, 1, 0, 1}};
    
    std::vector<std::vector<bool>> paths = GetPaths(free_grid);
    PrintPaths(paths);
    
    return 0;
}


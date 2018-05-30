/*
Write a method that returns all subsets of a set.
*/

#include <iostream>
#include <vector>

// Recursive solution: Start with the empty set. Then for each element, clone
// the existing subsets (including the empty set) and add this element to them.
void GetSubsets(std::vector<std::vector<int>> &subsets, int array[], int index)
{
    // Base case: create empty set
    if (index < 0) {
        subsets.push_back(std::vector<int>());
        return;
    }

    GetSubsets(subsets, array, index-1);       
    
    size_t curr_size = subsets.size();
    // Clone existing subsets and add this element to them.  Since the base case
    // created an empty set, we will automatically create the subset with just
    // this element using the cloned empty set
    for (size_t i = 0; i < curr_size; ++i)
    {
        std::vector<int> new_subset(subsets[i]);
        new_subset.push_back(array[index]);
        subsets.push_back(new_subset);
    }
}

void PrintSubsets(std::vector<std::vector<int>> &subsets)
{
    std::cout << "There are " << subsets.size() << " subsets:" << std::endl; 
    for (size_t i = 0; i < subsets.size(); ++i)
    {
        std::cout << "[";
        for (size_t j = 0; j < subsets[i].size(); ++j)
        {
            std::cout << subsets[i][j] << " ";
        }
        std::cout << "]\n";
    }
}

int main()
{
    int array[] = {1, 2, 3, 4};
    std::vector<std::vector<int>> subsets;
    GetSubsets(subsets, array, 3);
    PrintSubsets(subsets);
}

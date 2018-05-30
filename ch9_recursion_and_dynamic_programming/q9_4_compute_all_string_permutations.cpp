/*
Write a method to compute all permutations of a string.
*/

#include <iostream>
#include <string>
#include <vector>

// Solution: Remove first character and recursively permute the remainder.
// O(n!) time complexity, O(n!) space complexity
// Base case: empty string.  Next, insert last character before the empty 
// string.  Then, insert 2nd to last character before and after the existing
// character, and so on.
void StringPermutations(std::vector<std::string> &perms, std::string str)
{
    if (str.empty())
    {
        perms.push_back("");
        return;
    }
    char letter = str[0];
    std::string rest = str.substr(1);
    StringPermutations(perms, rest);
    
    std::vector<std::string> orig_perms(perms.begin(), perms.end());
    perms.clear();
    for (std::string perm : orig_perms)
    {
        for (size_t j = 0; j <= perm.length(); ++j)
        {
            std::string new_perm = perm.substr(0,j) + letter + perm.substr(j);
            perms.push_back(new_perm);
        }
    }
}

void PrintStringPermutations(std::vector<std::string> &all)
{
    std::cout << "There are " << all.size() << " permutations:\n";
    for (size_t i = 0; i < all.size(); ++i)
        std::cout << all[i] << " ";
    std::cout << "\n";
}

int main()
{
    std::string str = "ABCD";

    std::vector<std::string> perms;
    StringPermutations(perms, str);
    PrintStringPermutations(perms);
}

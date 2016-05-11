#include <iostream>
#include <string>
#include <vector>

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
    std::cout << "There are " << all.size() << " permutations:" << std::endl;
    for (size_t i = 0; i < all.size(); ++i)
        std::cout << all[i] << " ";
    std::cout << std::endl;
}

int main()
{
    std::string str = "ABCD";

    std::vector<std::string> perms;
    StringPermutations(perms, str);
    PrintStringPermutations(perms);

    return 0;
}

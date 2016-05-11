#include <iostream>
#include <string>

void PrintCombinationsRecursive(std::string str, int pos, int left, int right)
{
    if (left == 0 && right == 0)
    {
        std::cout << str << std::endl;
        return;
    }
    if (left > 0)
    {
        str[pos] = '(';
        PrintCombinationsRecursive(str, pos+1, left-1, right);
    }
    if (right > left)
    {
        str[pos] = ')';
        PrintCombinationsRecursive(str, pos+1, left, right-1);
    }
}

void PrintAllCombinations(int n)
{
    std::string str;
    str.resize(n*2);
    PrintCombinationsRecursive(str, 0, n, n);
}

int main()
{
    PrintAllCombinations(1); std::cout << std::endl;
    PrintAllCombinations(2); std::cout << std::endl;
    PrintAllCombinations(3); std::cout << std::endl;
    PrintAllCombinations(4); std::cout << std::endl;

    return 0;
}

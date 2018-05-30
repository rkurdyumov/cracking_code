/*
Implement an algorithm to print all valid (e.g., properly opened and closed) 
combinations of n-pairs of parentheses.
EXAMPLE:
input: 3 (e.g., 3 pairs of parentheses)
output: ()()(), ()(()), (())(), ((()))
*/

#include <iostream>
#include <string>

// Solution: Keep track of the number of left and right parentheses we have
// remaining and recursively assign one to a position in a candidate string.
// We can always add a left parenthesis (if one is available) and we can add
// a right parenthesis as long as there is a left one remaining as well.
// Time complexity: O(4^n / n^1.5)
// The total number of valid combinations of n pairs is the Catalan number.
// They grow as C_n ~ 4^n / (n^1.5 * sqrt(pi)) [see Wikipedia]
void PrintCombinationsRecursive(std::string str, int pos, int left, int right)
{
    if (left == 0 && right == 0)
    {
        std::cout << str << "\n";
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
    PrintAllCombinations(1); std::cout << "\n";
    PrintAllCombinations(2); std::cout << "\n";
    PrintAllCombinations(3); std::cout << "\n";
    PrintAllCombinations(4); std::cout << "\n";
}

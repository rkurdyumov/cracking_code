/*
Write a method to sort an array of strings so that all the anagrams are next 
to each other.
*/

#include <iostream>
#include <algorithm> // std::sort
#include <vector>
#include <string>

// Implement a custom comparator for the sorting function. Since this function
// is called many times during sorting, it would benefit from caching the 
// sorted strings (not implemented here).
bool CompareStrings(std::string s1, std::string s2)
{
    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    return s1 < s2;
}

void PrintStrings(std::vector<std::string> &strings)
{
    for (size_t i = 0; i < strings.size(); ++i)
    {
        std::cout << strings[i] << "\n";
    }
}

// Solution: Use a standard sorting algorithm, with a custom comparison
// function to sort the strings (since anagrams will have the same sorted
// string).
int main()
{
    std::vector<std::string> strings;

    strings.push_back("cat");
    strings.push_back("dog");
    strings.push_back("peal");
    strings.push_back("leap");
    strings.push_back("tac");
    strings.push_back("god");
    strings.push_back("");
    strings.push_back("act");
    strings.push_back("a");

    std::cout << "String array:\n";
    PrintStrings(strings);
    std::sort(strings.begin(), strings.end(), CompareStrings);
    std::cout << "Sorted string array w/ adjacent anagrams:\n";
    PrintStrings(strings);
}

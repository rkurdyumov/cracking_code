/*
Given two strings, write a method to decide if one is a permutation of the 
other.
*/

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

// Solution 1: Check if sorted strings are identical
// O(NlogN + MlogM) time complexity
// O(N+M) space if we need to preserve strings, could be O(1) space otherwise
static bool IsAnagram1(const std::string & str1, const std::string & str2)
{
    std::string strA = str1;
    std::string strB = str2;
    sort(strA.begin(), strA.end());
    sort(strB.begin(), strB.end());
    return (strA == strB);
}

// Solution 2: Check if two strings have identical counts for each unique char
static bool IsAnagram2(const std::string & str1, const std::string & str2)
{
    if (str1.length() != str2.length()) return false;

    int unique_chars[256] = {0}; // first string has no unique chars yet
    int num_unique_chars = 0;
    int num_completed_chars = 0;

    for (size_t i = 0; i < str1.length(); i++)
    {
        unsigned char c = str1[i]; // must use unsigned char as array index
        if (unique_chars[c] == 0) ++num_unique_chars;
        ++unique_chars[c];
    }
    
    for (size_t i = 0; i < str2.length(); i++)
    {
        unsigned char c = str2[i];
        if (unique_chars[c] == 0) return false; // 2nd string has new letter
        --unique_chars[c];
        if (unique_chars[c] == 0)
        {
            ++num_completed_chars;
            if (num_completed_chars == num_unique_chars)
                return i == str2.length() - 1; // done processing 1, so check 2
        }
    }
    return false;
}

int main()
{
    std::string str1, str2;
    while(true)
    {
        std::cout << "Enter first string: ";
        std::getline(std::cin, str1);
        std::cout << "Enter second string: ";
        std::getline(std::cin, str2);
        std::cout << "Is anagram w/ Solution 1: " << IsAnagram1(str1, str2) << "\n";
        std::cout << "Is anagram w/ Solution 2: " << IsAnagram2(str1, str2) << "\n";
    }
}

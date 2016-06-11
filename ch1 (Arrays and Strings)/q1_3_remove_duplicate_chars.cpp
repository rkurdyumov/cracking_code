/*
Design an algorithm and write code to remove the duplicate characters in a 
string without using any additional buffer. NOTE: One or two additional 
variables are fine. An extra copy of the array is not.
FOLLOW UP
Write the test cases for this method.
*/

#include <iostream>
#include <cstring>

// Solution 1: No additional space, O(N^2) time complexity
static void removeDuplicateChars(char * str)
{
    if (str == nullptr) 
        return;
    size_t len = std::strlen(str);
    if (len < 2) return;

    size_t tail = 1;
    for (size_t i = 1; i < len; i++)
    {
        size_t j;
        for (j = 0; j < tail; j++)
        {
            if (str[j] == str[i]) break;
        }
        if (j == tail)
        {
            str[tail] = str[i];
            ++tail;
        }
    }
    str[tail] = '\0';
}

// Solution 2: O(1) space bool array, O(N) time complexity
static void removeDuplicateCharsWithArray(char * str)
{
    if (str == nullptr) 
        return;
    size_t len = std::strlen(str);
    if (len < 2) return;

    bool char_array[256] = {false};
    size_t tail = 0;

    for (size_t i = 0; i < len; i++)
    {
        unsigned char c = str[i];
        if (char_array[c] == true) 
            continue;
        else
        {
            str[tail] = c;
            ++tail;
            char_array[c] = true;
        }
    }
    str[tail] = '\0';
}

int main()
{
    // Test Solution 1
    char test_strings[][8] = {"abcd", "aaaa", "", "aaabbb", "abababa"};
    std::cout << "Test duplicate character removal using Solution 1:\n";
    for (size_t i = 0; i < sizeof(test_strings)/sizeof(test_strings[0]); ++i)
    {
        std::cout << test_strings[i] << "->";
        removeDuplicateChars(test_strings[i]);
        std::cout << test_strings[i] << "\n";

    }
    // Test Solution 2
    char test_strings2[][8] = {"abcd", "aaaa", "", "aaabbb", "abababa"};
    std::cout << "Test duplicate character removal using Solution 2:\n";
    for (size_t i = 0; i < sizeof(test_strings2)/sizeof(test_strings2[0]); ++i)
    {
        std::cout << test_strings2[i] << "->";
        removeDuplicateCharsWithArray(test_strings2[i]); 
        std::cout << test_strings2[i] << "\n";
    }
}

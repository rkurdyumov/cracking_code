/*
Implement an algorithm to determine if a string has all unique characters. What 
if you can not use additional data structures?
*/

#include <iostream>
#include <string>
#include <cstdint>

// Solution 1: Use additional boolean array, O(N) space where N = alphabet size
static bool hasUniqueAsciiChars(std::string str)
{
    bool ascii_chars[256] = {false};
    for (int i = 0; i < (int)str.length(); i++)
    {
        int ascii = str[i];
        if (ascii_chars[ascii]) return false;
        ascii_chars[ascii] = true;
    }
    return true;
}

// Solution 2: No additional storage, but can only differentiate among 32 chars
// Note that because we use uint32_t for used_letters, this function will return 
// false for the same uppercase and lowercase letter (but not other characters) 
// since they're exactly separated by 32 ASCII codes and will therefore map to 
// the same ON bit due to integer overflow.
static bool hasUniqueLetters(std::string str)
{
    uint32_t used_letters = 0;
    for (int i = 0; i < (int)str.length(); i++)
    {
        uint32_t val = str[i] - 'a';
        if ((used_letters & (1 << val)) > 0) return false;
        used_letters |= (1 << val);
    }
    return true;
}

int main()
{
    while (true)
    {
        std::string str;
        std::cout << "Enter a word to check for duplicate chars: ";
        std::cin >> str;
        bool unique_char = hasUniqueAsciiChars(str);
        bool unique_letter = hasUniqueLetters(str);
        std::cout << str << " has unique ASCII characters: " << unique_char << "\n";
        std::cout << str << " has unique letters: " << unique_letter << "\n";
    }
    return 0;
}    

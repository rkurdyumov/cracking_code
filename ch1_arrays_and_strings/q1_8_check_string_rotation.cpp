/*
Assume you have a method isSubstring which checks if one word is a substring of
another. Given two strings, s1 and s2, write code to check if s2 is a rotation 
of s1 using only one call to isSubstring (e.g., "waterbottle" is a rotation of 
"erbottlewat").
*/

#include <iostream>
#include <string>

// Soluton: Contatenate s1 with itself and check if s2 is a substring
static bool IsRotation(const std::string & s1, const std::string & s2)
{
    if (s1.length() != s2.length() || s1.length() == 0)
        return false;
    std::string s = s1 + s1;
    return s.find(s2) != std::string::npos;
}

int main()
{
    std::string s1, s2;
    while (true)
    {
        std::cout << "Enter string 1: ";
        std::cin >> s1;
        std::cout << "Enter string 2: ";
        std::cin >> s2;
        std::cout << "Is a rotation: " << IsRotation(s1, s2) << "\n";
    }
}


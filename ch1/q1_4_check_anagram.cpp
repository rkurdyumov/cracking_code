#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

static bool isAnagramSimple(char *str1, char *str2)
{
    std::string strA = str1;
    std::string strB = str2;
    sort(strA.begin(), strA.end());
    sort(strB.begin(), strB.end());
    return (strA == strB);
}

static bool isAnagram(char *str1, char *str2)
{
    int len1 = std::strlen(str1);
    int len2 = std::strlen(str2);
    if (len1 != len2) return false;

    int unique_letters[256] = {0};
    int num_unique_chars = 0;
    int num_completed_chars = 0;

    for (int i = 0; i < len1; i++)
    {
        unsigned char c = str1[i];
        if (unique_letters[c] == 0) ++num_unique_chars;
        ++unique_letters[c];
    }
    
    for (int i = 0; i < len2; i++)
    {
        unsigned char c = str2[i];
        if (unique_letters[c] == 0) return false;
        --unique_letters[c];
        if (unique_letters[c] == 0)
        {
            ++num_completed_chars;
            if (num_completed_chars == num_unique_chars)
            {
                bool finished_str2 = (i == len2) - 1;
                return finished_str2;
            }
        }

    }
    return false;
}
int main()
{
    char str1[50], str2[50];
    while(true)
    {
        std::cout << "Enter first string: ";
        std::cin.getline(str1, 50);
        std::cout << "Enter second string: ";
        std::cin.getline(str2, 50);
        bool is_anagram = isAnagramSimple(str1, str2);
        if (is_anagram)
            std::cout << "Yes, anagram!" << std::endl;
        else
            std::cout << "No, not an anagram!" << std::endl;
    }
    return 0;
}

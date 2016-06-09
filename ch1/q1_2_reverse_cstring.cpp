/*
Write code to reverse a C-Style String. (C-String means that "abcd" is 
represented as five characters, including the null character.)
*/

#include <iostream>
#include <cstring>

// Solution 1: Explicitly find str length before swapping in place 
static void reverseString1(char *str)
{
    int len = std::strlen(str); // length doesn't include null char
    for (int i = 0; i < len/2; i++)
        std::swap(str[i], str[len-i-1]);
}

// Solution 2: Advance pointer to end of string and then swap by moving 2
// pointers (one from start, one from end)
static void reverseString2(char *str)
{
    char * end = str;
    while ( (*end) != '\0')
        ++end;
    --end;
    while (str < end)
    {
        char tmp = *str;
        *str++ = *end;
        *end-- = tmp;
    }
}

int main()
{
    char str[50];
    while(true)
    {
        std::cout << "Enter a string: ";
        std::cin.getline(str, 50);
        std::cin.clear(); // clear error flag in case user enters too many chars
        
        reverseString1(str);
        std::cout << "Reverse using Solution 1: " << str << "\n";
        reverseString2(str);
        std::cout << "Reverse back using Solution 2: " << str << "\n";
    }
    return 0;
}


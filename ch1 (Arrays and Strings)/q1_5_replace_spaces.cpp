/*
Write a method to replace all spaces in a string with '%20’.
*/

#include <iostream>
#include <string>
#include <algorithm> // std::count

// Solution: Parse string from end and replace spaces with %20
void ReplaceSpaces(std::string & str)
{
    size_t space_count = std::count(str.begin(), str.end(), ' ');
    size_t char_count = str.length();
    
    size_t new_len = char_count + space_count * 2;
    str.resize(new_len);

    size_t tail = new_len;
    str[tail--] = '\0';
    for (size_t i = char_count; i > 0; i--)
    {
        if (str[i-1] == ' ')
        {
            str[tail--] = '0';
            str[tail--] = '2';
            str[tail--] = '%';

        }
        else
            str[tail--] = str[i-1];
    }
}

int main()
{
    std::string str;
    while (true)
    {
        std::cout << "Enter a string with spaces: ";
        std::getline(std::cin, str);
        ReplaceSpaces(str);
        std::cout << str << "\n";
    }
}

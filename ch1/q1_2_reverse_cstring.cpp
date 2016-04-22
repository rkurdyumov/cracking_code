#include <iostream>
#include <cstring>


static void reverseStringOld(char *str)
{
    int mid;
    int len = std::strlen(str);
    if (len%2 == 0)
        mid = len/2;
    else
        mid = len/2 + 1;
    for (int i = 0; i < mid; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

static void reverseString(char *str)
{
    char *end = str;
    char tmp;
    if (str != NULL)
    {
        while((*end) != '\0')
            ++end;
        --end;
        while (str < end)
        {
            tmp = *str;
            *str = *end;
            str++;
            *end = tmp;
            end--;
        }
    }
}

int main()
{
    char str[50];
    while(true)
    {
        std::cout << "Enter a string: ";
        std::cin.getline(str, 50);
        //reverseStringOld(str);
        reverseString(str);
        std::cout << str << std::endl;
    }
    return 0;
}


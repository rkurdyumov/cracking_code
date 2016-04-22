#include <iostream>
#include <cstring>

static void removeDuplicateChars(char *str)
{
    if (str == NULL) return;
    int len = std::strlen(str);
    if (len < 2) return;

    int tail = 1;
    for (int i = 1; i < len; i++)
    {
        int j;
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

static void removeDuplicateCharsWithArray(char *str)
{
    if (str == NULL) return;
    uint32_t len = std::strlen(str);
    if (len < 2) return;

    bool char_array[256] = {false};
    int tail = 0;

    for (uint32_t i = 0; i < len; i++)
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
    char str[50];
    while(true)
    {
        std::cout << "Enter string: ";
        std::cin.getline(str, 50);
        //removeDuplicateChars(str);
        removeDuplicateCharsWithArray(str);
        std::cout << str << std::endl;
    }
    return 0;
}

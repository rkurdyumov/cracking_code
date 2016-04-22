#include <iostream>
#include <string>

static const int MAX_LEN = 50;

void replace_spaces(char *str)
{
    char *ch = str;
    int ch_count = 0, space_count = 0;
    while (*ch != '\0')
    {
        ++ch_count;
        if (*ch == ' ')
            ++space_count;
        ++ch;
    }
    int new_len = ch_count + space_count * 2;
    if (new_len + 1 > MAX_LEN) return;
    int tail = new_len;
    str[tail--] = '\0';
    for (int i = ch_count - 1; i >= 0; i--)
    {
        if (str[i] == ' ')
        {
            str[tail--] = '0';
            str[tail--] = '2';
            str[tail--] = '%';

        }
        else
            str[tail--] = str[i];
    }
}

int main()
{
    char str[MAX_LEN];
    while (true)
    {
        std::cout << "Enter a string with spaces: ";
        std::cin.getline(str,MAX_LEN);
        replace_spaces(str);
        std::cout << str << std::endl;
    }
    return 0;
}

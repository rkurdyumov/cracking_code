#include <iostream>
#include <string>
#include <cstdint>

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

// Note that because we use uint32_t for used_letters, this function
// will work for both uppercase and lowercase letters (but not other
// characters) since they're exactly separated by 32 ASCII codes and
// will therefore map to the same ON bit due to integer overflow.
static bool hasUniqueLowerCaseLetters(std::string str)
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
        //bool unique = hasUniqueAsciiChars(str);
        bool unique = hasUniqueLowerCaseLetters(str);
        if (unique == true)
            std::cout << str << " is unique (no duplicates)" << std::endl;
        else
            std::cout << str << " is not unique (has duplicates)" << std::endl;
    }
    return 0;
}    

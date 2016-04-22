#include <iostream>
#include <string>

static bool isSubstring(std::string s1, std::string s2)
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
        bool flag = isSubstring(s1,s2);
        if (flag)
            std::cout << "Yes, rotation." << std::endl;
        else
            std::cout << "No, not a rotation." << std::endl;
    }
    return 0;
}


#include <iostream>
#include <algorithm> // sort()
#include <vector>
#include <string>

bool CompareStrings(std::string s1, std::string s2)
{
    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    return s1 < s2;
}

void PrintStrings(std::vector<std::string> &strings)
{
    for (size_t i = 0; i < strings.size(); ++i)
    {
        std::cout << strings[i] << std::endl;
    }
}

int main()
{
    std::vector<std::string> strings;

    strings.push_back("no");
    strings.push_back("yes");
    strings.push_back("peal");
    strings.push_back("leap");
    strings.push_back("on");
    strings.push_back("say");
    strings.push_back("");
    strings.push_back("what");
    strings.push_back("a");

    std::cout << "String array:" << std::endl;
    PrintStrings(strings);
    std::sort(strings.begin(), strings.end(), CompareStrings);
    std::cout << "Sorted string array:" << std::endl;
    PrintStrings(strings);
    return 0;
}

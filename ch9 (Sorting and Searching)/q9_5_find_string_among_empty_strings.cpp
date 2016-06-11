#include <iostream>
#include <vector>
#include <string>

int BinarySearchString(std::vector<std::string> &strings, int low, int high, std::string str)
{
    if (low > high) return -1;

    while (low <= high && strings[high] == "")
        --high;
    if (low > high)
        return -1; // All empty strings
    
    // Keep track of the old_mid so we don't recheck the empty strings later
    int mid = low + (high - low)/2;
    int old_mid = mid;
    while (strings[mid] == "")
        ++mid; // advance midpoint until we get a non-empty string
    
    int comp = strings[mid].compare(str);
    if (comp == 0) return mid;
    else if (comp < 0)
        return BinarySearchString(strings, mid+1, high, str);
    else
        return BinarySearchString(strings, low, old_mid-1, str);
}

int FindString(std::vector<std::string> &strings, std::string str)
{
    if (strings.empty() || str.empty()) return -1;
    return BinarySearchString(strings, 0, strings.size() - 1, str);
}

void PrintStrings(std::vector<std::string> &strings)
{
    std::cout << "[";
    for (auto c: strings)
        std::cout << "\"" << c << "\",";
    std::cout << "]" << std::endl;
}

int main()
{
    std::vector<std::string> strings = 
        {"at","","","","ball","","","car","","","dad","",""};
    
    PrintStrings(strings);
    
    int index = FindString(strings, "ball");
    std::cout << "String \"ball\" is at index " << index << std::endl;

    index = FindString(strings, "ballcar");
    std::cout << "String \"ballcar\" is at index " << index << std::endl;

    return 0;
}

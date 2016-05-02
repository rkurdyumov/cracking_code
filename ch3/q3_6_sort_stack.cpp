#include <iostream>
#include <stack>

void Sort(std::stack<int> &s)
{
    std::stack<int> other;
    while (!s.empty())
    {
        int temp = s.top(); s.pop();
        while (!other.empty() && other.top() > temp)
        {
            s.push(other.top());
            other.pop();
        }
        other.push(temp);
    }
    s = other;
}

void Insert(std::stack<int> &s, int curr)
{
    if (s.empty())
    {
        s.push(curr);
        return;
    }
    int top = s.top();
    if (curr < top)
    {
        s.pop();
        Insert(s, curr);
        s.push(top);
    }
    else
        s.push(curr);
}

void SortRecursive(std::stack<int> &s)
{
    if (!s.empty())
    {
        int value = s.top();
        s.pop();
        SortRecursive(s);
        Insert(s, value);
    }
}

int main()
{
    std::stack<int> s1, s2;

    int arr[] = {4, 1, 2, 3, 0};
    
    for (size_t i = 0; i < sizeof(arr) / sizeof(*arr); ++i)
    {
        s1.push(arr[i]);
        s2.push(arr[i]);
        std::cout << arr[i] << "<-";
    }
    std::cout << "top" << std::endl;

    Sort(s1);
    SortRecursive(s2);

    // Result of sort using additional stack
    std::cout << "Sort: top";
    while (!s1.empty())
    {
        int value = s1.top();
        std::cout << "->" << value;
        s1.pop();
    }
    std::cout << std::endl;

    // Result of sort using implicit recursive call stack:
    std::cout << "Recursive sort: top";
    while (!s2.empty())
    {
        int value = s2.top();
        std::cout << "->" << value;
        s2.pop();
    }
    std::cout << std::endl;


    return 0; 
}

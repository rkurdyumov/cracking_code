/*
Write a program to sort a stack in ascending order. You should not make any 
assumptions about how the stack is implemented. The following are the only 
functions that should be used to write this program: 
push | pop | peek | isEmpty.
*/

#include <iostream>
#include <stack>

// Iterative solution: use a sorted second stack. If we pop a value from the
// original stack that's too small for the second stack, move values from the
// second stack to the original stack until we find room for that value. Then 
// push that value on the second stack, transfer the moved values back, and 
// proceed.
// Time complexity: O(n^2), space complexity: O(n)
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

// Recursive solution: start from base case, where all elements have been
// popped off.  Insert the last element to be popped back on.  Then try to 
// insert the 2nd to last.  If it's too small, pop off the top stack element
// and insert successfully.  The logic easily generalizes: If the current 
// popped off element is too small, recursively pop from the stack until we can
// push it on.
// Time complexity: O(n^2), space complexity: O(1) [O(n) call stack]
void Insert(std::stack<int> &s, int curr)
{
    if (s.empty() || curr > s.top())
        s.push(curr);
    else
    {
        int top = s.top();
        s.pop();
        Insert(s, curr);
        s.push(top);
    }
}

void SortRecursive(std::stack<int> &s)
{
    if (s.empty())
        return;
    int value = s.top();
    s.pop();
    SortRecursive(s);
    Insert(s, value);
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
    std::cout << "top\n";

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
    std::cout << "\n";

    // Result of sort using implicit recursive call stack:
    std::cout << "Recursive sort: top";
    while (!s2.empty())
    {
        int value = s2.top();
        std::cout << "->" << value;
        s2.pop();
    }
    std::cout << "\n";


    return 0; 
}

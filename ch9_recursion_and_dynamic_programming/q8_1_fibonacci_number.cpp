/*
Write a method to generate the nth Fibonacci number.
*/

#include <iostream>

// Recursive solution
//
int FibRecursive(int n)
{
    if (n < 2) 
        return n;
    return FibRecursive(n-1) + FibRecursive(n-2);
}

// Iterative solution: use dynamic programming approach to store two previous
// Fibonacci numbers (instead of an entire array holding all 'n' numbers)
int FibIterative(int n)
{
    if (n < 2) 
        return n;
    int prev = 1;
    int prev_prev = 0;
    for (int i = 2; i < n; ++i)
    {
        int curr = prev + prev_prev;
        prev_prev = prev;
        prev = curr;
    }
    return prev + prev_prev;
}

int main()
{
    std::cout << "Fib(6): " << FibRecursive(6) << "\n";
    std::cout << "Fib(7): " << FibIterative(7) << "\n";
}

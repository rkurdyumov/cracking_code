#include <iostream>

int FibRecursive(int n)
{
    if (n < 2) return n;
    return FibRecursive(n-1) + FibRecursive(n-2);
}

int FibIterative(int n)
{
    if (n < 2) return n;
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
    std::cout << "Fib(6): " << FibRecursive(6) << std::endl;
    std::cout << "Fib(7): " << FibIterative(7) << std::endl;
    return 0;
}

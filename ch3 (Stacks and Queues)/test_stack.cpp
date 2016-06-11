#include <iostream>
#include "stack.h"

int main()
{
    Stack stack;
    for (int i = 0; i < 5; ++i)
        stack.Push(i);

    std::cout << "stack: " << stack << std::endl;

    Stack copy(stack);
    std::cout << "copy: " << copy << std::endl;

    int data = stack.Top();
    stack.Pop();
    std::cout << "stack.Pop(): [" << data << "] " <<  stack << std::endl;

    stack.Push(4);
    std::cout << "stack.Push(4): " << stack << std::endl;

    return 0;
}

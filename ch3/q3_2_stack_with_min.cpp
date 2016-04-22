#include <iostream>
#include <cassert>
#include <stack>
#include <limits>

class StackWithMin
{
    private:
        std::stack<int> data_stack;
        std::stack<int> min_stack;

    public:
        StackWithMin() { 
            min_stack.push(std::numeric_limits<int>::max());
        }

        ~StackWithMin() { }
        
        void Push(int value)
        {
            data_stack.push(value);
            if (value <= Min())
                min_stack.push(value);
        }

        int Top() const
        {
            assert(!data_stack.empty());
            return data_stack.top();
        }

        void Pop()
        {
            if (Top() == Min())
                min_stack.pop();
            data_stack.pop();
        }

        int Min() const
        {
            return min_stack.top();
        }

        bool IsEmpty() const
        {
            return data_stack.empty();
        }
};

int main()
{
    StackWithMin stack;
    std::cout << "stack: ";
    stack.Push(5); std::cout << stack.Top() << "<--";
    stack.Push(4); std::cout << stack.Top() << "<--";
    stack.Push(1); std::cout << stack.Top() << "<--";
    stack.Push(1); std::cout << stack.Top() << "<--";
    stack.Push(3); std::cout << stack.Top() << "<--";
    stack.Push(0); std::cout << stack.Top() << "<--";
    stack.Push(6); std::cout << stack.Top() << "<--top" << std::endl;

    while (!stack.IsEmpty())
    {
        int value = stack.Top();
        stack.Pop();
        std::cout << "pop: " << value << ", min = " << stack.Min() << std::endl;
    }
}


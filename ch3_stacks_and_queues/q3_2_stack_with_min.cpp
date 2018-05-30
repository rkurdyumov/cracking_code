/*
How would you design a stack which, in addition to push and pop, also has a 
function min which returns the minimum element? Push, pop and min should all 
operate in O(1) time.
*/

#include <iostream>
#include <cassert>
#include <stack>
#include <limits>

// Solution: Maintain a second (smaller) stack that only stores new mins
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
            if (value <= Min()) // store duplicate new mins
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
    stack.Push(6); std::cout << stack.Top() << "<--top\n";

    while (!stack.IsEmpty())
    {
        int value = stack.Top();
        stack.Pop();
        std::cout << "pop: " << value << ", min = " << stack.Min() << "\n";
    }
}


#include <iostream>
#include <cassert>
#include <stack>
#include <deque>
#include <vector>

// Implementation #1: set of stacks that appear as 1 monolithic stack to the user.
// The user can pop from the individual stacks.  The design allows for the stacks
// (other than the last) to be below full capacity, but they get deleted when they 
// are empty.  This avoids the rollover system (which is O(n) worst case time 
// complexity) for popping from stack #1 (where n = number of stacks).
class SetOfStacks
{
    public:
        SetOfStacks(int t = 10): threshold(t)
        {
            stack_set.push_back(std::stack<int>());
        }

        ~SetOfStacks() { }

        bool IsEmpty() const { return stack_set.empty(); }

        bool IsEmpty(int index) const { 
            assert(!IsEmpty());
            return stack_set[index].empty(); 
        }

        bool IsFull() const { 
            assert(!IsEmpty());
            return stack_set[GetLastStackIndex()].size() == threshold; 
        }

        bool IsFull(int index) const { return stack_set[index].size() == threshold; }

        int NumStacks() { return stack_set.size(); };

        void Push(int value)
        {
            if (IsEmpty() || IsFull())
            {
                stack_set.push_back(std::stack<int>());
            }
            stack_set[GetLastStackIndex()].push(value);
        }

        int Top() const
        {
            assert(!IsEmpty() && !IsEmpty(GetLastStackIndex()));
            return stack_set[GetLastStackIndex()].top();
        }

        void Pop()
        {
            int last_stack_index = GetLastStackIndex();
            assert(!IsEmpty() && !IsEmpty(last_stack_index));
            stack_set[last_stack_index].pop();
            if (IsEmpty(last_stack_index))
                stack_set.erase(stack_set.begin() + last_stack_index);
        }

        int PopAt(int index)
        {
            assert(!IsEmpty() && !IsEmpty(index));
            int value = stack_set[index].top();
            stack_set[index].pop();
            if (IsEmpty(index))
                stack_set.erase(stack_set.begin() + index);
            return value;
        }

    private:
        std::vector<std::stack<int>> stack_set;
        const unsigned int threshold;
        int GetLastStackIndex() const { return stack_set.size() - 1; };
};

// Implementation #2: set of stacks that appear as 1 monolithic stack to the user.
// The user can pop from the individual stacks.  The design uses a rollover method,
// so that stacks (other than the last) are always at full capacity.  This method
// has O(n) worst case time complexity for popping from the 1st stack (where n = 
// number of stacks) but is more appropriate when the user expects the non-last
// stacks to be always full. We also need to use a deque instead of a stack since
// we need access to the bottom element.
class SetOfStacksWithRollover
{
    public:
        SetOfStacksWithRollover(int t = 10): threshold(t)
        {
            stack_set.push_back(std::deque<int>());
        }

        ~SetOfStacksWithRollover() { }

        bool IsEmpty() const { return stack_set.empty(); }

        bool IsEmpty(int index) const { 
            assert(!IsEmpty());
            return stack_set[index].empty(); 
        }

        bool IsFull() const { 
            assert(!IsEmpty());
            return stack_set[GetLastStackIndex()].size() == threshold; 
        }

        bool IsFull(int index) const { return stack_set[index].size() == threshold; }

        int NumStacks() { return stack_set.size(); };

        // Top of stack = front of deque
        void Push(int value)
        {
            if (IsEmpty() || IsFull())
            {
                stack_set.push_back(std::deque<int>());
            }
            stack_set[GetLastStackIndex()].push_front(value);
        }

        int Top() const
        {
            assert(!IsEmpty() && !IsEmpty(GetLastStackIndex()));
            return stack_set[GetLastStackIndex()].front();
        }

        void Pop()
        {
            int last_stack_index = GetLastStackIndex();
            assert(!IsEmpty() && !IsEmpty(last_stack_index));
            stack_set[last_stack_index].pop_front();
            if (IsEmpty(last_stack_index))
                stack_set.erase(stack_set.begin() + last_stack_index);
        }

        // Remove top element, then use rollover function to propagate
        int PopAt(int index)
        {
            assert(!IsEmpty() && !IsEmpty(index));
            if (index == GetLastStackIndex())
            {
                int value = Top(); Pop(); return value;
            }
            int value = stack_set[index].front();
            stack_set[index].pop_front();
            Rollover(index);
            return value;
        }

        // Current stack is missing one element, so take the bottom element
        // from the next stack and put it on the top of this one
        void Rollover(int index)
        {
            if (index == GetLastStackIndex()) return;
            int bottom_value = stack_set[index + 1].back();
            stack_set[index + 1].pop_back();
            stack_set[index].push_front(bottom_value);
            if (IsEmpty(index + 1))
                stack_set.erase(stack_set.begin() + index + 1);
            else
                Rollover(index + 1);
        }

    private:
        std::vector<std::deque<int>> stack_set;
        const unsigned int threshold;
        int GetLastStackIndex() const { return stack_set.size() - 1; };

};

int main()
{
    // Test implementation with no rollover
    SetOfStacks stack_set(3);

    for (int i = 0; i < 7; ++i) {
        stack_set.Push(i);
        std::cout << i << "<--";
    }
    std::cout << "**** Test stack set without rollover ****" << std::endl;
    std::cout << "top" << std::endl;

    for (int i = 0; i < 7; ++i) {
        int value = stack_set.Top();
        stack_set.Pop();
        std::cout << "Popping elem " << value << std::endl;
    }

    std::cout << "Number of stacks: " << stack_set.NumStacks() << std::endl;
    std::cout << "Is stack set empty? " << stack_set.IsEmpty() << std::endl;

    for (int i = 0; i < 7; ++i) {
        stack_set.Push(i);
        std::cout << i << "<--";
    }
    std::cout << "top" << std::endl;
    std::cout << "Number of stacks: " << stack_set.NumStacks() << std::endl;
   
    int value;
    // [ 0 1 2 | 3 4 5 | 6 ] <-- top
    for (int i = 0; i < 5; ++i)
    {
        value = stack_set.PopAt(0);
        std::cout << "Popping elem " << value << " from stack 0" << std::endl;
    }
    // [ 3 | 6]
    value = stack_set.PopAt(1);
    std::cout << "Popping elem " << value << " from stack 1" << std::endl;
    
    // [ 3 ]
    stack_set.Push(2); stack_set.Push(1); stack_set.Push(0);
    std::cout << "Pushing [2 1 0]. Num stacks: " << stack_set.NumStacks()  << std::endl;
    
    // [ 3 2 1 | 0 ]


    // Test implementation with rollover
    SetOfStacksWithRollover stack_set2(2);

    for (int i = 0; i < 5; ++i) {
        stack_set2.Push(i);
        std::cout << i << "<--";
    }
    std::cout << "top" << std::endl;

    // [0 1 | 2 3 | 4] <-- top
    for (int i = 0; i < 5; ++i)
    {
        int value = stack_set2.PopAt(0);
        std::cout << "Popping elem " << value << " from stack 0" << std::endl;
    }

    std::cout << "Number of stacks: " << stack_set2.NumStacks() << std::endl;
    std::cout << "Is stack set empty? " << stack_set2.IsEmpty() << std::endl;

    return 0;
}

/*
Describe how you could use a single array to implement three stacks.
*/

#include <iostream>
#include <cassert>

// Solution 1: Assume 3 stacks are equal sizes, don't use extra space
class Stack3Equal
{
    private:
        int *data; // array of all allocated stack nodes, implicitly split 3-ways
        size_t stack_size; // max size of each stack
        size_t count[3]; // number of elements in each stack

    public:
        Stack3Equal(size_t size = 10) : stack_size(size)
        {   
            data = new int[stack_size * 3];
            count[0] = count[1] = count[2] = 0;
        }  
        
        ~Stack3Equal()
        {
            delete[] data;
        }

        bool IsEmpty(int stack) { return count[stack] == 0; }
        
        bool IsFull(int stack) { return count[stack] == stack_size; }

        void Push(int stack, int value)
        {
            assert(!IsFull(stack));
            size_t index = stack_size * stack + count[stack];
            data[index] = value;
            ++count[stack];
        }

        int Top(int stack)
        {
            assert(!IsEmpty(stack));
            size_t index = stack_size * stack + count[stack] - 1;
            return data[index];
        }

        void Pop(int stack)
        {
            assert(!IsEmpty(stack));
            --count[stack];
        }
};

// Solution 2: Allow stacks to be different max sizes, this comes at a O(n)
// extra space complexity cost (where n = maximum total size of all stacks) 
// since we must keep track of a free array of nodes.
class Stack3
{
    private:
        struct StackNode {
            int value;
            int prev_index;
        };
        
        StackNode *data; // array of all possible allocated stack nodes
        size_t total_size; // max total size of all stacks
        int stack_index[3]; // current top element index of each stack
        int *free_list; // array of freely available nodes
        int free_index; // free_list index of currently available free node
    
    public:
        Stack3(size_t size = 10) : total_size(size)
        {   
            stack_index[0] = stack_index[1] = stack_index[2] = -1;
            data = new StackNode[total_size];
            free_list = new int[total_size];
            for (size_t i = 0; i < total_size; ++i)
                free_list[i] = total_size - 1 - i;
            // free_list = [total_size - 1, total_size -2, ..., 1, 0];
            // When adding back to free list, we want to add to end of array 
            // (treat free_list like an array implementation of a stack) so
            // that we don't have to move any existing elements around and so
            // that (free_index + 1) tells us how much free space we have
            free_index = total_size - 1;
        }

        ~Stack3()
        {
            delete[] data;
            delete[] free_list;
        }

        bool IsEmpty(int stack) const { return stack_index[stack] == -1; }

        bool IsFull() const { return free_index == -1; }

        void Push(int stack, int value) 
        {
            assert(!IsFull());
            int index = free_list[free_index--];
            data[index].value = value;
            data[index].prev_index = stack_index[stack];
            stack_index[stack] = index;
        }

        int Top(int stack) const
        {
            assert(!IsEmpty(stack));
            return data[stack_index[stack]].value;
        }

        void Pop(int stack)
        {
            assert(!IsEmpty(stack));
            free_list[++free_index] = stack_index[stack]; // release as free
            stack_index[stack] = data[stack_index[stack]].prev_index;
        }
};

int main()
{
    // Test variable size stack implementation
    Stack3 stacks(5);
    
    stacks.Push(0,1);
    stacks.Push(0,2);
    stacks.Push(1,10);
    stacks.Push(2,20);
    stacks.Push(2,21);

    std::cout << "**** Test variable size stack ****\n";
    std::cout << "Total array is full? " << stacks.IsFull() << "\n";

    int value[5];

    value[0] = stacks.Top(0); stacks.Pop(0);
    value[1] = stacks.Top(0); stacks.Pop(0);
    value[2] = stacks.Top(1); stacks.Pop(1);
    value[3] = stacks.Top(2); stacks.Pop(2);
    value[4] = stacks.Top(2); stacks.Pop(2);

    std::cout << "1st stack: top-->" << value[0] << "-->" << value[1] << "\n";
    std::cout << "2nd stack: top-->" << value[2] << "\n";
    std::cout << "3rd stack: top-->" << value[3] << "-->" << value[4] << "\n";

    std::cout << "1st stack is empty? " << stacks.IsEmpty(0) << "\n";
    std::cout << "2nd stack is empty? " << stacks.IsEmpty(1) << "\n";
    std::cout << "3rd stack is empty? " << stacks.IsEmpty(2) << "\n";

    std::cout << "Total array is full? " << stacks.IsFull() << "\n";

    // Test equal sized stack implementation
    Stack3Equal stacks2(2);
    stacks2.Push(0,1);
    stacks2.Push(0,2);
    stacks2.Push(1,10);
    stacks2.Push(1,11);
    stacks2.Push(2,20);
    stacks2.Push(2,21);

    std::cout << "\n**** Test equal sized stack ****\n";
    std::cout << "1st stack is full? " << stacks2.IsFull(0) << "\n"; 
    std::cout << "2nd stack is full? " << stacks2.IsFull(1) << "\n"; 
    std::cout << "3rd stack is full? " << stacks2.IsFull(2) << "\n"; 

    int value2[6];

    value2[0] = stacks2.Top(0); stacks2.Pop(0);
    value2[1] = stacks2.Top(0); stacks2.Pop(0);
    value2[2] = stacks2.Top(1); stacks2.Pop(1);
    value2[3] = stacks2.Top(1); stacks2.Pop(1);
    value2[4] = stacks2.Top(2); stacks2.Pop(2);
    value2[5] = stacks2.Top(2); stacks2.Pop(2);

    std::cout << "1st stack: top-->" << value2[0] << "-->" << value2[1] << "\n";
    std::cout << "2nd stack: top-->" << value2[2] << "-->" << value2[3] << "\n";
    std::cout << "3rd stack: top-->" << value2[4] << "-->" << value2[5] << "\n";

    std::cout << "1st stack is empty? " << stacks2.IsEmpty(0) << "\n";
    std::cout << "2nd stack is empty? " << stacks2.IsEmpty(1) << "\n";
    std::cout << "3rd stack is empty? " << stacks2.IsEmpty(2) << "\n";
}



#include <iostream>
#include <cassert>


class Stack3Equal
{
    private:
        int *data;
        const int stack_size;
        int count[3];

    public:
        Stack3Equal(int size = 10) : stack_size(size)
        {   
            assert(stack_size > 0);
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
            int index = stack_size * stack + count[stack];
            data[index] = value;
            ++count[stack];
        }

        int Top(int stack)
        {
            assert(!IsEmpty(stack));
            int index = stack_size * stack + count[stack] - 1;
            return data[index];
        }

        void Pop(int stack)
        {
            assert(!IsEmpty(stack));
            --count[stack];
        }
};

// Solution 2: Allow stacks to be different max sizes, this comes at a O(n)
// space complexity cost (where n = maximum total size of all stacks) since 
// we must keep track of a free list
class Stack3
{
    private:
        struct StackNode {
            int value;
            int prev_index;
        };
        
        StackNode *data;
        int total_size;
        int stack_index[3];
        int *free_list;
        int free_index;
    
    public:
        Stack3(int size = 10) : total_size(size)
        {   
            assert(total_size > 0);
            stack_index[0] = stack_index[1] = stack_index[2] = -1;
            data = new StackNode[total_size];
            free_list = new int[total_size];
            for (int i = 0; i < total_size; ++i)
                free_list[i] = total_size - 1 - i;
            // free_list = [total_size - 1, total_size -2, ..., 1, 0];
            // When adding back to free list, we want to add to end of array 
            // (treat free_list like an array implementation of a stack) so
            // that (free_index + 1) tells us how much free space we have
            free_index = total_size - 1;
        }

        ~Stack3()
        {
            delete[] data;
            delete[] free_list;
        }

        bool IsEmpty(int stack) const { return free_index == total_size - 1; }

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

    std::cout << "**** Test variable size stack ****" << std::endl;
    std::cout << "Total array is full? " << stacks.IsFull() << std::endl;

    int value[5];

    value[0] = stacks.Top(0); stacks.Pop(0);
    value[1] = stacks.Top(0); stacks.Pop(0);
    value[2] = stacks.Top(1); stacks.Pop(1);
    value[3] = stacks.Top(2); stacks.Pop(2);
    value[4] = stacks.Top(2); stacks.Pop(2);

    std::cout << "1st stack: top-->" << value[0] << "-->" << value[1] << std::endl;
    std::cout << "2nd stack: top-->" << value[2] << std::endl;
    std::cout << "3rd stack: top-->" << value[3] << "-->" << value[4] << std::endl;

    std::cout << "1st stack is empty? " << stacks.IsEmpty(0) << std::endl;
    std::cout << "2nd stack is empty? " << stacks.IsEmpty(1) << std::endl;
    std::cout << "3rd stack is empty? " << stacks.IsEmpty(2) << std::endl;

    std::cout << "Total array is full? " << stacks.IsFull() << std::endl;

    // Test equal sized stack implementation
    Stack3Equal stacks2(2);
    stacks2.Push(0,1);
    stacks2.Push(0,2);
    stacks2.Push(1,10);
    stacks2.Push(1,11);
    stacks2.Push(2,20);
    stacks2.Push(2,21);

    std::cout << std::endl << "**** Test equal sized stack ****" << std::endl;
    std::cout << "1st stack is full? " << stacks2.IsFull(0) << std::endl;
    std::cout << "2nd stack is full? " << stacks2.IsFull(1) << std::endl;
    std::cout << "3rd stack is full? " << stacks2.IsFull(2) << std::endl;

    int value2[6];

    value2[0] = stacks2.Top(0); stacks2.Pop(0);
    value2[1] = stacks2.Top(0); stacks2.Pop(0);
    value2[2] = stacks2.Top(1); stacks2.Pop(1);
    value2[3] = stacks2.Top(1); stacks2.Pop(1);
    value2[4] = stacks2.Top(2); stacks2.Pop(2);
    value2[5] = stacks2.Top(2); stacks2.Pop(2);

    std::cout << "1st stack: top-->" << value2[0] << "-->" << value2[1] << std::endl;
    std::cout << "2nd stack: top-->" << value2[2] << "-->" << value2[3] << std::endl;
    std::cout << "3rd stack: top-->" << value2[4] << "-->" << value2[5] << std::endl;

    std::cout << "1st stack is empty? " << stacks2.IsEmpty(0) << std::endl;
    std::cout << "2nd stack is empty? " << stacks2.IsEmpty(1) << std::endl;
    std::cout << "3rd stack is empty? " << stacks2.IsEmpty(2) << std::endl;
    return 0;
}



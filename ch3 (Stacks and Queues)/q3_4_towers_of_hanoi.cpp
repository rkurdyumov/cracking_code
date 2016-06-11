/*
In the classic problem of the Towers of Hanoi, you have 3 rods and N disks of 
different sizes which can slide onto any tower. The puzzle starts with disks 
sorted in ascending order of size from top to bottom (e.g., each disk sits on 
top of an even larger one). You have the following constraints: 
(A) Only one disk can be moved at a time.
(B) A disk is slid off the top of one rod onto the next rod.
(C) A disk can only be placed on top of a larger disk.
Write a program to move the disks from the first rod to the last using Stacks.
*/

#include <iostream>
#include <cassert>
#include <stack>

class Tower 
{
    private:
        std::stack<int> rods[3];
        const int num_disks;
    
    public:
        Tower(int n = 4) : num_disks(n)
        {
            for (int i = 0; i < num_disks; ++i)
                rods[0].push(num_disks - i); // disks arranged large->small
        }

        ~Tower() { }

        int Top(int n)
        {
            assert(!rods[n].empty());
            return rods[n].top();
        }

        void Pop(int n)
        {
            assert(!rods[n].empty());
            rods[n].pop();
        }

        void Move()
        {
            MoveRecursive(0, 1, 2, num_disks);
        }

        void MoveRecursive(int start, int temp, int end, int n)
        {
            if (n == 0) return;
            MoveRecursive(start, end, temp, n-1);
            int val = rods[start].top();
            rods[start].pop();
            rods[end].push(val);
            MoveRecursive(temp, start, end, n-1);
        }

};

int main()
{
    int num_rods = 6;
    Tower t(num_rods);

    t.Move();

    std::cout << "Last rod after move: ";
    const int last_index = 2; // last tower
    std::cout << "top-->";
    for (int i = 0; i < num_rods; ++i)
    {
        int value = t.Top(last_index); t.Pop(last_index);
        std::cout << value << "-->";
    }
    std::cout << "end\n";
}

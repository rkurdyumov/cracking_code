/*
In the classic problem of the Towers of Hanoi, you have 3 towers and N disks of
different sizes which can slide onto any tower. The puzzle starts with disks 
sorted in ascending order of size from top to bottom (e.g., each disk sits on 
top of an even larger one). You have the following constraints: 
(A) Only one disk can be moved at a time.
(B) A disk is slid off the top of one tower onto the next tower.
(C) A disk can only be placed on top of a larger disk.
Write a program to move the disks from the first tower to the last using Stacks.
*/

#include <iostream>
#include <cassert>
#include <stack>

class Tower 
{
    private:
        std::stack<int> towers[3];
        const int num_disks;
    
    public:
        Tower(int n = 4) : num_disks(n)
        {
            for (int i = 0; i < num_disks; ++i)
                towers[0].push(num_disks - i); // disks arranged large->small
        }

        ~Tower() { }

        int Top(int n)
        {
            assert(!towers[n].empty());
            return towers[n].top();
        }

        void Pop(int n)
        {
            assert(!towers[n].empty());
            towers[n].pop();
        }

        void Move()
        {
            MoveRecursive(0, 1, 2, num_disks);
        }

        void MoveRecursive(int start, int temp, int end, int n)
        {
            if (n == 0) return;
            MoveRecursive(start, end, temp, n-1);
            int val = towers[start].top();
            towers[start].pop();
            towers[end].push(val);
            MoveRecursive(temp, start, end, n-1);
        }

};

int main()
{
    int num_discs = 6;
    Tower t(num_discs);

    t.Move();

    std::cout << "Last tower after move: ";
    const int last_index = 2; // last tower
    std::cout << "top-->";
    for (int i = 0; i < num_discs; ++i)
    {
        int value = t.Top(last_index); t.Pop(last_index);
        std::cout << value << "-->";
    }
    std::cout << "bottom\n";
}

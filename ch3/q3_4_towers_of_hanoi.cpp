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
                rods[0].push(num_disks - i); // disks in ascending order
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
    std::cout << "end" << std::endl;

    return 0;
}

/*
Implement a MyQueue class which implements a queue using two stacks.
*/

#include <iostream>
#include <cassert>
#include <stack>

// Solution: use two stacks: s1 stores the newest elements on top, s2 stores
// the oldest elements on top.  If s2 is empty and we need to access the front
// (oldest) element in the queue, push all the elements from s1 over to s2.
class QueueUsingStacks
{
    public:
        QueueUsingStacks() { }
        
        ~QueueUsingStacks() { } 
        
        bool IsEmpty() const { return s1.empty() && s2.empty(); }

        int Front()
        {
            if (!s2.empty()) 
                return s2.top();
            Transfer();
            assert(!s2.empty());
            return s2.top();
        }

        void Pop()
        {
            if (!s2.empty())
            { 
                s2.pop();
                return;
            }
            Transfer();
            assert(!s2.empty());
            s2.pop();
        }

        void Push(int value)
        {
            s1.push(value);
        }
     
    private:
        std::stack<int> s1;
        std::stack<int> s2;
        // Move elements from stack 1 to stack 2
        void Transfer()
        {
            while (!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
        }
};

int main()
{
    QueueUsingStacks queue;
    
    queue.Push(0);
    queue.Push(1);
    queue.Push(2);
    queue.Pop();
    queue.Pop();
    queue.Pop();
    queue.Push(3);

    int value = queue.Front();
    queue.Pop();

    bool empty = queue.IsEmpty();
    std::cout << "Removing elem " << value << ". Queue empty? " << empty << "\n";
}

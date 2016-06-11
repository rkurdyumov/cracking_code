/*
Implement an algorithm to find the nth to last element of a singly linked list.
*/

#include <iostream>
#include <set>
#include "linked_list.h"

class LinkedListExtended : public LinkedList {
    public:
        int NthToLastElement(int n) const;
        int NthToLastElementRecursive(int n);
    private:
        Node * RecursiveHelper(Node *p, int n, int &depth);
};

// Iterative solution: advance leader pointer by n-1, then advance both until
// leader hits the last node
int LinkedListExtended::NthToLastElement(int n) const
{
    if (IsEmpty() || n < 1) return -1;

    Node *leader = head, *trailer = head;
    for (int i = 0; i < n - 1; ++i)
    {
        leader = leader->next;
        if (leader == nullptr)
            return -1;
    }
    while (leader != tail)
    {
        trailer = trailer->next;
        leader = leader->next;
    }
    return trailer->data;
}

// Recursive solution: recurse down to tail, then track the depth coming out
int LinkedListExtended::NthToLastElementRecursive(int n)
{
    if (IsEmpty() || n < 1) return -1;
    int depth = 0;
    Node * result = RecursiveHelper(head, n, depth);
    return result == nullptr ? -1 : result->data;
}

LinkedListExtended::Node * LinkedListExtended::RecursiveHelper(Node *p, int n, 
        int & depth)
{
    Node *result = p; // assignment only used for base case (when p = tail)

    if (p != tail)
        result = RecursiveHelper(p->next, n, depth);
    if (++depth == n)
        return p;
    else if (p == head && depth < n) // if we've recursed all the way back, n is too big
        return nullptr;
    else
        return result;
}

int main()
{
    LinkedListExtended list;
    list.PushFront(4);
    list.PushFront(3);
    list.PushFront(2); 
    list.PushFront(1);
    list.PushFront(0);
    std::cout << "list: " << list << std::endl; // should have [0 1 2 3 4];
   
    std::cout << "Iterative solution:" << std::endl;
    for (int k = 1; k <= 6; ++k)
    {
        std::cout << "The " << k << " to last element is " << 
            list.NthToLastElement(k) << "\n";
    }
    std::cout << "Recursive solution:" << std::endl;
    for (int k = 1; k <= 6; ++k)
    {
        std::cout << "The " << k << " to last element is " << 
            list.NthToLastElementRecursive(k) << "\n";
    }
}

/*
Implement an algorithm to find the kth to last element of a singly linked list.
*/

#include <iostream>
#include <set>
#include "linked_list.h"

class LinkedListExtended : public LinkedList {
    public:
        int KthToLastElement(int k) const;
        int KthToLastElementRecursive(int k);
    private:
        Node * RecursiveHelper(Node * p, int k, int & depth);
};

// Iterative solution: advance leader pointer by k-1, then advance both until
// leader hits the last node
int LinkedListExtended::KthToLastElement(int k) const
{
    if (IsEmpty() || k < 1) return -1;

    Node * leader = head, * trailer = head;
    for (int i = 0; i < k - 1; ++i)
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
int LinkedListExtended::KthToLastElementRecursive(int k)
{
    if (IsEmpty() || k < 1) return -1;
    int depth = 0;
    Node * result = RecursiveHelper(head, k, depth);
    return result == nullptr ? -1 : result->data;
}

LinkedListExtended::Node * LinkedListExtended::RecursiveHelper(Node * n, int k, 
        int & depth)
{
    Node *result = n; // assignment only used for base case (when n = tail)

    if (n != tail)
        result = RecursiveHelper(n->next, k, depth);
    if (++depth == k)
        return n;
    else if (n == head && depth < k) // if we've recursed all the way back, k is too big
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
    std::cout << "list: " << list << "\n"; // should have [0 1 2 3 4];
   
    std::cout << "Iterative solution:\n";
    for (int k = 1; k <= 6; ++k)
    {
        std::cout << "The " << k << " to last element is " << 
            list.KthToLastElement(k) << "\n";
    }
    std::cout << "Recursive solution:\n";
    for (int k = 1; k <= 6; ++k)
    {
        std::cout << "The " << k << " to last element is " << 
            list.KthToLastElementRecursive(k) << "\n";
    }
}

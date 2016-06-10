/*
Reverse a singly linked list using recursion.  See linked_list.cpp for the 
iterative implementation.
*/

#include <iostream>
#include "linked_list.h"

class LinkedListExtended : public LinkedList
{
    public:
        void ReverseListRecursive();
    private:
        Node * RecursiveHelper(Node * n);
};

void LinkedListExtended::ReverseListRecursive()
{
    if (IsEmpty())
        return;
    tail = head;
    head = RecursiveHelper(head);
}

LinkedListExtended::Node * LinkedListExtended::RecursiveHelper(Node * n)
{
    if (n->next == nullptr) 
        return n;
    Node * rest = RecursiveHelper(n->next);
    n->next->next = n;
    n->next = nullptr;
    return rest;
}

int main()
{
    LinkedListExtended list;
    list.Append(0);
    list.Append(1);
    list.Append(2);
    list.Append(3);
    std::cout << "list: " << list << "\n";

    list.ReverseListRecursive();
    std::cout << "list.ReverseListRecursive(): " << list << "\n";
}

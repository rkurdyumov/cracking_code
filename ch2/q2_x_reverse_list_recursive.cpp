#include <iostream>
#include "linked_list.h"

class LinkedListExtended : public LinkedList
{
    public:
        void ReverseListRecursive();
    private:
        Node * RecursiveHelper(Node *k);
};

void LinkedListExtended::ReverseListRecursive()
{
    Node *start = head;
    head = RecursiveHelper(start);
}

LinkedListExtended::Node * LinkedListExtended::RecursiveHelper(Node *first)
{
    if (first == nullptr || first->next == nullptr) return first;
    Node *rest = RecursiveHelper(first->next);
    first->next->next = first;
    first->next = nullptr;
    return rest;
}

int main()
{
    LinkedListExtended list;
    list.Append(0);
    list.Append(1);
    list.Append(2);
    list.Append(3);
    std::cout << "list: " << list << std::endl;

    list.ReverseListRecursive();
    std::cout << "list.ReverseListRecursive(): " << list << std::endl;

    return 0;
}

#include <iostream>
#include <set>
#include "linked_list.h"

class LinkedListExtended : public LinkedList {
    public:
        Node * NthToLastElement(int n) const;
        Node * NthToLastElementRecursive(int n);
    private:
        Node * RecursiveHelper(Node *p, int n, int &depth);
};

// Iterative solution
LinkedListExtended::Node * LinkedListExtended::NthToLastElement(int n) const
{
    if (IsEmpty() || n < 1) return nullptr;

    Node *n2 = head, *n1 = head;
    for (int i = 0; i < n - 1; ++i)
    {
        if (n2 == nullptr) return nullptr; // went past tail
        n2 = n2->next;
    }
    while (n2 != tail)
    {
        n1 = n1->next;
        n2 = n2->next;
    }
    return n1;
}

// Recursive solution
LinkedListExtended::Node * LinkedListExtended::NthToLastElementRecursive(int n)
{
    if (IsEmpty() || n < 1) return nullptr;
    int depth = 0;
    return RecursiveHelper(head, n, depth);
}

LinkedListExtended::Node * LinkedListExtended::RecursiveHelper(Node *p, int n, int &depth)
{
    Node *result = p; // assignment only used for base case (when p = tail)
    if (p != tail)
        result = RecursiveHelper(p->next, n, depth);
    if (++depth == n)
        return p;
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
    for (int k = 1; k <= 5; ++k)
    {
        LinkedListExtended::Node *n = list.NthToLastElement(k);
        std::cout << "The " << k << " to last element is " << n->data << std::endl;
    }
    std::cout << "Recursive solution:" << std::endl;
    for (int k = 1; k <= 5; ++k)
    {
        LinkedListExtended::Node *n = list.NthToLastElementRecursive(k);
        std::cout << "The " << k << " to last element is " << n->data << std::endl;
    }

    return 0;
}

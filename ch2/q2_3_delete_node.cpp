/*
Implement an algorithm to delete a node in the middle of a single linked list, 
given only access to that node.
EXAMPLE
Input: the node 'c' from the linked list a->b->c->d->e
Result: nothing is returned, but the new linked list looks like a->b->d->e
*/

#include <iostream>
#include "linked_list.h"

class LinkedListExtended : public LinkedList
{
    public:
        void DeleteNode(Node *n);
        Node * GetNode(int data);
};

LinkedListExtended::Node * LinkedListExtended::GetNode(int data)
{
    for (Node *n = Begin(); n != End(); n = n->next)
        if (n->data == data) 
            return n;
    return nullptr;
}

// Solution: we consider all cases (delete head, tail, last node, middle node)
void LinkedListExtended::DeleteNode(Node *n)
{
    if (n == nullptr) 
        return;
    if (n == tail && n == head) // remove last node
    {
        head = tail = nullptr;
        delete n;
    }
    else if (n == tail) // replace tail
    {
        Node *prev = head;
        while (prev->next != tail) 
            prev = prev->next;
        prev->next = nullptr;
        tail = prev;
        delete n;
    }
    else if (n == head) // replace head
    {
        head = head->next;
        delete n;
    }
    // For deleting a middle node, we swap the next node data into the curr node
    // and delete the next node, so any external pointers to the next node will
    // be invalidated.
    else // replace middle node
    {
        Node *next = n->next; 
        n->data = next->data;
        n->next = next->next;
        if (next == tail) 
            tail = n;
        delete next;
    }
}

int main()
{
    LinkedListExtended list;
    list.PushFront(3);
    list.PushFront(2);
    list.PushFront(1);
    list.PushFront(0);
    std::cout << "list: " << list << "\n";

    list.DeleteNode(list.GetNode(2)); // remove middle
    std::cout << "list.deleteNode(2): " << list << "\n";
    list.DeleteNode(list.GetNode(3)); // remove tail
    std::cout << "list.deleteNode(3): " << list << "\n";
    list.DeleteNode(list.GetNode(0)); // remove head
    std::cout << "list.deleteNode(0): " << list << "\n";
    list.DeleteNode(list.GetNode(1)); // remove last node
    std::cout << "list.deleteNode(1): " << list << "\n";
}

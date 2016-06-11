/*
Given a circular linked list, implement an algorithm which returns node at the 
begin ning of the loop.
DEFINITION
Circular linked list: A (corrupt) linked list in which a node's next pointer 
points to an earlier node, so as to make a loop in the linked list.
EXAMPLE
Input: A -> B -> C -> D -> E -> C [the same C as earlier]
Output: C
*/

#include <iostream>
#include "linked_list.h"

class LinkedListExtended : public LinkedList 
{
    public:
        LinkedListExtended() : LinkedList() {} 
        LinkedListExtended(const LinkedListExtended &list);
        ~LinkedListExtended();
        void MakeLoop(int data);
        int ReturnLoopStart() const;
    private:
        virtual void Print(std::ostream &out) const;
};

// Override the copy constructor because the base class one will loop forever
LinkedListExtended::LinkedListExtended(const LinkedListExtended & list) : 
    LinkedListExtended()
{
    Node * curr = list.head;
    while (curr != list.tail)
    {
        Append(curr->data);
        curr = curr->next;
    }
    Append(curr->data);
    tail->next = curr->next;
}

LinkedListExtended::~LinkedListExtended()
{
    // get rid of loop before calling base destructor
    tail->next = nullptr;
}

void LinkedListExtended::MakeLoop(int data)
{
    for (Node * curr = Begin(); curr != End(); curr = curr->next)
    {
        if (curr->data == data)
        {
            tail->next = curr;
            break;
        }
    }
}

int LinkedListExtended::ReturnLoopStart() const
{
    if (IsEmpty() || head->next == nullptr) 
        return -1;

    // Move the fast pointer at 2x speed, they will meet k nodes from loop start
    Node * fast = head; 
    Node * slow = head;
    while (fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    if (fast->next == nullptr) return -1;

    // By definition, loop start is also k nodes from head, so advance both slow
    // and fast and they will meet at loop start
    slow = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow->data;
}

void LinkedListExtended::Print(std::ostream &out) const
{
    int loopstart = ReturnLoopStart();
    Node * curr = head;

    while (curr != tail)
    {
        out << curr->data << "-->";
        curr = curr->next;
    }
    out << tail->data << "-->";

    if (loopstart == -1) 
        out << "nullptr";
    else 
        out << tail->next->data;
}

int main()
{
    LinkedListExtended list;
    list.Append(1);
    list.Append(2);
    list.Append(3);
    list.Append(4);
    list.Append(5);
    std::cout << "list: " << list << "\n";
    
    list.MakeLoop(3); 
    int loopstart_data = list.ReturnLoopStart();
    
    std::cout << "list w/ loop: " << list << "\n";
    std::cout << "Loop start element: " << loopstart_data << "\n";

    // Verify polymorphism works properly (unrelated to problem)
    LinkedList *b = new LinkedListExtended(list);
    std::cout << "Print list using LinkedList *ptr: " << *b << "\n";
    delete b;
}

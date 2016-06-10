/*
Write code to remove duplicates from an unsorted linked list.
FOLLOW UP
How would you solve this problem if a temporary buffer is not allowed?
*/

#include <iostream>
#include <set>
#include "linked_list.h"

class LinkedListExtended : public LinkedList {
    public:
        void RemoveDuplicates();  // use set as buffer
        void RemoveDuplicates2(); // iterate through with 2 pointers
};

// Solution 1: using set to keep track of duplicate elements
// O(n) time and O(n) space complexity
void LinkedListExtended::RemoveDuplicates()
{
    std::set<int> set;
    Node *curr = head;
    Node *prev = nullptr;
    while(curr != nullptr)
    {
        if(set.find(curr->data) != set.end())
        {
            prev->next = curr->next;
            delete curr;
            curr = prev->next;
        }
        else
        {
            set.insert(curr->data);
            prev = curr;
            curr = curr->next;
        }
    }
    tail = prev; // update tail in case we deleted it
}

// Solution 2: Use 2 pointers (current and trailer that checks up to current)
// O(n^2) time and O(1) space complexity using 2 pointers
void LinkedListExtended::RemoveDuplicates2()
{
    Node *prev = head; // one node behind curr
    for (Node *curr = head->next; curr != nullptr; curr = curr->next)
    {
        for (Node *trailer = head; trailer != curr; trailer = trailer->next)
        {
            if (curr->data == trailer->data)
            {
                prev->next = curr->next;
                delete curr;
                curr = prev; // first for loop will move curr along for us
                break; // should only have one duplicate per new node examined
            }
        }
        prev = curr;
    }
    tail = prev; // update tail in case we deleted it
}

int main()
{
    LinkedListExtended list = LinkedListExtended();
    
    list.PushFront(3); // add to front
    list.PushFront(2);
    list.PushFront(1);
    list.PushFront(0);
    list.Append(3); // add to back
    list.Append(2);
    list.Append(1);
    std::cout << "list: " << list << std::endl; // should have [0 1 2 3 3 2 1]
    
    list.RemoveDuplicates(); // Use set
    std::cout << "list.RemoveDuplicates(): " << list << "\n"; // [0 1 2 3]
    
    list.Append(3);
    list.Append(2);
    list.Append(1);
    std::cout << "list: " << list << "\n"; // should have [0 1 2 3 3 2 1]
    
    list.RemoveDuplicates2(); // Use 2 pointers
    std::cout << "list.RemoveDuplicates2(): " << list << "\n"; // [0 1 2 3]

    return 0;
}

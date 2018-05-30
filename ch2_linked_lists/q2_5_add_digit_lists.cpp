/*
You have two numbers represented by a linked list, where each node contains a 
single digit. The digits are stored in reverse order, such that the 1's digit 
is at the head of the list. Write a function that adds the two numbers and 
returns the sum as a linked list.
EXAMPLE
Input: (7 -> 1 -> 6) + (5 -> 9 -> 2).  That is, 617 + 295.
Output: 2 -> 1 -> 9.  That is, 912.
FOLLOW UP
Supposed the digits are stored in forward order.  Repeat the above problem.
Input: (6 -> 1 -> 7) + (2 -> 9 -> 5).  That is, 617 + 295.
Output: 9 -> 1 -> 2.  That is, 912.
*/

#include <iostream>
#include "linked_list.h"

class LinkedListExtended : public LinkedList
{
    public:
        friend LinkedListExtended SumLists(const LinkedListExtended & list1,
                const LinkedListExtended & list2);
        friend LinkedListExtended SumListsRecursive(const LinkedListExtended & list1, 
                const LinkedListExtended & list2);
    private: // technically friend functions aren't public/private but show intent
        friend void RecursiveHelper(LinkedListExtended & list, const Node * n1, 
                const Node * n2, int carry);
};

// Iterative solution
LinkedListExtended SumLists(const LinkedListExtended & list1, 
        const LinkedListExtended & list2)
{
    LinkedListExtended result;
    const LinkedListExtended::Node * n1 = list1.Begin();
    const LinkedListExtended::Node * n2 = list2.Begin();
    int carry = 0;
    while(n1 != nullptr || n2 != nullptr)
    {
        int value = carry;
        value += ((n1 == nullptr) ? 0 : n1->data);
        value += ((n2 == nullptr) ? 0 : n2->data);
        result.Append(value%10);
        carry = (value >= 10 ? 1 : 0);
        n1 = ((n1 == nullptr) ? nullptr : n1->next);
        n2 = ((n2 == nullptr) ? nullptr : n2->next);
    }
    if (carry == 1) result.Append(1);
    return result; 
}

// Recursive solution
LinkedListExtended SumListsRecursive(const LinkedListExtended & list1,
        const LinkedListExtended &list2)
{
    int carry = 0;
    LinkedListExtended list;
    RecursiveHelper(list, list1.head, list2.head, carry);
    return list;
}

void RecursiveHelper(LinkedListExtended & list, const LinkedListExtended::Node * n1, 
        const LinkedListExtended::Node * n2, int carry)
{
    if (n1 == nullptr && n2 == nullptr)
    {
        if (carry == 1) 
            list.Append(1);
        return;
    }
    int value = carry;
    LinkedListExtended::Node * n1_next = nullptr;
    LinkedListExtended::Node * n2_next = nullptr;
    if (n1 != nullptr) 
    {
        value += n1->data;
        n1_next = n1->next;
    }   
    if (n2 != nullptr) 
    {
        value += n2->data;
        n2_next = n2->next;
    }   
    
    list.Append(value%10);

    RecursiveHelper(list, n1_next, n2_next, value >= 10 ? 1 : 0);
}


int main()
{
    LinkedListExtended list1, list2;
    
    int arr1[] = {7, 1, 6};
    int arr2[] = {5, 9, 2};
    for (size_t i = 0; i < sizeof(arr1)/sizeof(arr1[0]); ++i)
        list1.Append(arr1[i]);
    for (size_t i = 0; i < sizeof(arr2)/sizeof(arr2[0]); ++i)
        list2.Append(arr2[i]);
    std::cout << "list1, list2: " << list1 << ", " << list2 << "\n";

    // Sum using iterative approach
    LinkedListExtended sum = SumLists(list1, list2);
    std::cout << "SumLists(list1, list2): " << sum << std::endl;

    // Sum using recursive approach
    LinkedListExtended sum2 = SumListsRecursive(list1, list2);
    std::cout << "SumListsRecursive(list1, list2): " << sum2 << "\n";
}

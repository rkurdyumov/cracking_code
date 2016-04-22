#include <iostream>
#include "linked_list.h"

class LinkedListExtended : public LinkedList
{
    public:
        friend LinkedListExtended SumLists(const LinkedListExtended &list1,
                const LinkedListExtended &list2);
        void SumListsRecursive(const LinkedListExtended &list1, 
                const LinkedListExtended &list2);
    private:
        void RecursiveHelper(const Node *n1, const Node *n2, int carry);
};

// Iterative solution
LinkedListExtended SumLists(const LinkedListExtended &list1, const LinkedListExtended &list2)
{
    LinkedListExtended result = LinkedListExtended();
    const LinkedListExtended::Node *n1 = list1.Begin(), *n2 = list2.Begin();
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
void LinkedListExtended::SumListsRecursive(const LinkedListExtended &list1,
        const LinkedListExtended &list2)
{
    int carry = 0;
    this->RecursiveHelper(list1.head, list2.head, carry);
}

void LinkedListExtended::RecursiveHelper(const Node *n1, const Node *n2, int carry)
{
    if (n1 == nullptr && n2 == nullptr)
    {
        if (carry == 1) this->Append(1);
        return;
    }
    int value = carry;
    Node *n1_next, *n2_next;
    if (n1 != nullptr) 
    {
        value += n1->data;
        n1_next = n1->next;
    }   
    else
        n1_next = nullptr;
    if (n2 != nullptr) 
    {
        value += n2->data;
        n2_next = n2->next;
    }   
    else
        n2_next = nullptr;
    
    this->Append(value%10);

    this->RecursiveHelper(n1_next, n2_next, value >= 10 ? 1 : 0);
}


int main()
{
    LinkedListExtended list1, list2;
    
    int arr1[] = {4, 5, 6};
    int arr2[] = {3, 4, 5, 9};
    for (int i = 0; i < (int) (sizeof(arr1)/sizeof(*arr1)); ++i)
        list1.Append(arr1[i]);
    for (int i = 0; i < (int) (sizeof(arr2)/sizeof(*arr2)); ++i)
        list2.Append(arr2[i]);
    std::cout << "list1, list2: " << list1 << ", " << list2 << std::endl;

    // Sum using iterative approach
    LinkedListExtended sum = SumLists(list1, list2);
    std::cout << "SumLists(list1, list2): " << sum << std::endl;

    // Sum using recursive approach
    LinkedListExtended sum2 = LinkedListExtended();
    sum2.SumListsRecursive(list1, list2);
    std::cout << "SumListsRecursive(list1, list2): " << sum2 <<  std::endl;

    return 0;
}

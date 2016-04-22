#include<iostream>
#include "linked_list.h"

int main()
{

    LinkedList list1 = LinkedList();
    LinkedList list2 = LinkedList();
    
    int arr1[] = {0, 1, 2, 3};
    int arr2[] = {4, 5, 6, 7};
    for (int i = 0; i < (int) (sizeof(arr1)/sizeof(*arr1)); ++i) {
        list1.Append(arr1[i]);
        list2.Append(arr2[i]);
    }
    std::cout << "list1, list2: " << list1 << ", " << list2 << std::endl;

    list2.InsertAfter(list2.Begin(), 4);
    std::cout << "Insert 4 after front of list2: " << list2 << std::endl; 

    int data = list2.Front();
    list2.PopFront();
    std::cout << "Pop list2.Front(): [" << data << "] " << list2 << std::endl;

    LinkedList list1_reverse = list1;
    list1_reverse.Reverse();
    std::cout << "list1.Reverse(): " << list1_reverse << std::endl;

    LinkedList list3 = list1;
    list3 += list1;
    std::cout << "list1 += list1: " << list3 << std::endl;

    LinkedList sum = list1 + list2;
    std::cout << "list1 + list2: " << sum << std::endl;

    return 0;
}

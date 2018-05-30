/*
SELECTION SORT
O(n^2) time
O(1) auxiliary space

The algorithm divides the input list into two parts: 
(1) the sublist of items already sorted, which is built up from left to right 
at the front (left) of the list
(2) the sublist of items remaining to be sorted that occupy the rest of the 
list. 
Initially, the sorted sublist is empty and the unsorted sublist is the entire 
input list. The algorithm proceeds by finding the smallest (or largest, 
depending on sorting order) element in the unsorted sublist, exchanging 
(swapping) it with the leftmost unsorted element (putting it in sorted order), 
and moving the sublist boundaries one element to the right.
*/

#include <iostream>

// Iterative implementation
void SelectionSort(int array[], int n)
{
    for (int i = 0; i < n-1; ++i)
    {
        int smallest_index = i;
        for (int j = i+1; j < n; ++j)
        {
            if (array[j] < array[smallest_index])
                smallest_index = j;
        }
        std::swap(array[i], array[smallest_index]);
    }
}

void PrintArray(int array[], int n)
{
    for (int i = 0; i < n; ++i)
        std::cout << array[i] << " ";
    std::cout << "\n";
}

int main()
{
    int array[] = {5, 2, 4, 0};
    
    PrintArray(array, 4);
    SelectionSort(array, 4);
    std::cout << "Sorted array: ";
    PrintArray(array, 4);
}

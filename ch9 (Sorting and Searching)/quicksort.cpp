/*
QUICKSORT
O(n^2) time (worst), O(nlogn) time (average)
O(logn) space

The steps are:

(1) Pick an element, called a pivot, from the array.
(2) Partitioning: reorder the array so that all elements with values less than 
the pivot come before the pivot, while all elements with values greater than 
the pivot come after it (equal values can go either way). After this 
partitioning, the pivot is in its final position. This is called the partition 
operation.
(3) Recursively apply the above steps to the sub-array of elements with smaller 
values and separately to the sub-array of elements with greater values.
*/

#include <iostream>
#include <utility> // std::swap
#include <stack>

// Both the recursive and iterative implementations use this Partition function
int Partition(int array[], int low, int high)
{
    int pivot = high; // arbitrarily choose high element
    int first_bigger = low; // index of first element bigger than pivot
    for (int i = low; i < high; ++i)
    {
        if (array[i] < array[pivot])
        {
            std::swap(array[i], array[first_bigger]);
            first_bigger++;
        }
    }
    std::swap(array[first_bigger], array[pivot]);
    return first_bigger;
}

// Recursive implementation
void QuickSortRecursive(int array[], int low, int high)
{
    if (high > low)
    {
        int pivot = Partition(array, low, high);
        QuickSortRecursive(array, low, pivot-1);
        QuickSortRecursive(array, pivot+1, high);
    }
}

void QuickSort(int array[], int n)
{
    QuickSortRecursive(array, 0, n-1);
}

// Iterative implementation
void QuickSortIterative(int array[], int n)
{
    std::stack<int> args;
    args.push(0); // low index
    args.push(n-1); // high index
    while (!args.empty())
    {
        int high = args.top(); args.pop();
        int low = args.top(); args.pop();
        if (high < low)
        {
            int pivot = Partition(array, low, high);
            args.push(pivot+1); // upper half of partitioned array
            args.push(high);    
            args.push(low);     // lower half of partitioned array
            args.push(pivot-1);
        }
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
    int array2[] = {5, 2, 4, 0};
    
    PrintArray(array, 4);
    QuickSort(array, 4);
    QuickSortIterative(array2, 4);
    
    std::cout << "Sorted array: ";
    PrintArray(array, 4);
    PrintArray(array2, 4);
}

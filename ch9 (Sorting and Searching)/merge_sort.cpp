/*
MERGE SORT
O(nlogn) time
O(n) auxiliary space

Conceptually, a merge sort works as follows:

(1) Divide the unsorted list into n sublists, each containing 1 element (a list 
of 1 element is considered sorted).
(2) Repeatedly merge sublists to produce new sorted sublists until there is only 
1 sublist remaining. This will be the sorted list.
*/

#include <iostream>
#include <algorithm> // std::min
#include <queue>

// Given an array and indices into two adjacent sorted ranges [low middle] and 
// (middle high], merge the two in sorted order.  Use a queue to maintain the
// sorted order of the original ranges.
void Merge(int array[], int low, int middle, int high)
{
    std::queue<int> q1, q2;

    for (int i = low; i <= middle; ++i)
        q1.push(array[i]);
    for (int i = middle+1; i <= high; ++i)
        q2.push(array[i]);

    int i = low;
    while (!q1.empty() && !q2.empty())
    {
        if (q1.front() < q2.front())
        {
            array[i++] = q1.front(); q1.pop();
        }
        else
        {
            array[i++] = q2.front(); q2.pop();
        }
    }
    while (!q1.empty())
    {
        array[i++] = q1.front(); q1.pop();
    }
    while (!q2.empty())
    {
        array[i++] = q2.front(); q2.pop();
    }
}

// Recursive algorithm: recursively break down the array until we get to single
// elements, then merge and sort the parts as we recurse out.
void MergeSortRecursive(int array[], int low, int high)
{
    if (low < high)
    {
        int middle = low + (high - low)/2;
        MergeSortRecursive(array, low, middle);
        MergeSortRecursive(array, middle + 1, high);
        Merge(array, low, middle, high);
    }
}

void MergeSort(int array[], int n)
{
    MergeSortRecursive(array, 0, n-1);
}

// Iterative algorithm: sort each pair, then sort every 4 elements by merging
// the pairs, etc.
void MergeSortIterative(int array[], int n)
{
    for (int curr_size = 1; curr_size <= n-1; curr_size *= 2)
    {
        for (int low = 0; low < n-1; low += 2*curr_size)
        {
            int middle = low + curr_size - 1;
            // The high index can never be larger than the last element
            int high = std::min(low + 2*curr_size - 1, n-1);
            Merge(array, low, middle, high);
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
    MergeSort(array, 4);
    MergeSortIterative(array2, 4);

    std::cout << "Sorted array using recursive merge sort: ";
    PrintArray(array, 4);
    std::cout << "Sorted array using iterative merge sort: ";
    PrintArray(array2, 4);
}

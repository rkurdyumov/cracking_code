/*
Given a sorted array of n integers that has been rotated an unknown number of
times, give an O(log n) algorithm that finds an element in the array. You may 
assume that the array was originally sorted in increasing order.
EXAMPLE:
Input: find 5 in array (15 16 19 20 25 1 3 4 5 7 10 14)
Output: 8 (the index of 5 in the array)
*/

#include <iostream>

// Recursive implementation of modified binary search. The key idea is to find
// whether the left or right sub-array is sorted (at least one of them must be
// since the original array was sorted).  Once we know the sorted sub-array, we
// clearly know whether to recursively search inside that sub-array, or to look
// in the other sub-array.
int FindElementRecursive(int array[], int low, int high, int elem)
{
    if (low > high) 
        return -1;

    int mid = low + (high - low)/2;
    
    if (array[mid] == elem) return mid;

    if (array[low] <= array[mid]) // if left array is sorted
    {
        if (array[low] <= elem && array[mid] > elem) // if elem is in left array
            return FindElementRecursive(array, low, mid-1, elem);
        else // if elem in right half
            return FindElementRecursive(array, mid+1, high, elem);
    }
    else // otherwise right array is sorted
    {
        if (array[mid] < elem && array[high] >= elem) // If elem is in right array
            return FindElementRecursive(array, mid+1, high, elem);
        else // if elem is in left half
            return FindElementRecursive(array, low, mid-1, elem);
    }
}

int FindElement(int array[], int elem, size_t n)
{
    return FindElementRecursive(array, 0, n-1, elem);
}

int main()
{
    int array[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
    int elem = 5;
    int index = FindElement(array, elem, sizeof(array)/sizeof(array[0]));
    std::cout << "Element " << elem << " is at index " << index << "\n";
}

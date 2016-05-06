#include <iostream>

int FindElementRecursive(int array[], int low, int high, int elem)
{
    if (low > high) return -1;

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

int FindElement(int array[], int elem, int n)
{
    return FindElementRecursive(array, 0, n-1, elem);
}

int main()
{
    int array[12] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};

    int elem = 5;
    int index = FindElement(array, elem, 12);
    std::cout << "Element " << elem << " is at index " << index << std::endl;
    return 0;
}

#include <iostream>
#include <algorithm> // for min()
#include <queue>

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

void MergeSortRecursive(int array[], int low, int high)
{
    if (low < high)
    {
        int middle = (low + high) / 2;
        MergeSortRecursive(array, low, middle);
        MergeSortRecursive(array, middle + 1, high);
        Merge(array, low, middle, high);
    }
}

void MergeSort(int array[], int n)
{
    MergeSortRecursive(array, 0, n-1);
}

void MergeSortIterative(int array[], int n)
{
    for (int curr_size = 1; curr_size <= n-1; curr_size *= 2)
    {
        for (int low = 0; low < n-1; low += 2*curr_size)
        {
            int middle = low + curr_size - 1;
            int high = std::min(low + 2*curr_size - 1, n-1);
            Merge(array, low, middle, high);
        }
    }
}

void PrintArray(int array[], int n)
{
    for (int i = 0; i < n; ++i)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}

int main()
{
    int array[] = {5, 4, 2, 0};
    int array2[] = {5, 4, 2, 0};
    
    
    PrintArray(array, 4);
    MergeSort(array, 4);
    MergeSortIterative(array2, 4);
    std::cout << "Sorted array: ";
    PrintArray(array, 4);
    PrintArray(array2, 4);

    return 0;
}

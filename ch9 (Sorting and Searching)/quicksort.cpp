#include <iostream>
#include <utility> // for swap()
#include <stack>

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

void QuickSortIterative(int array[], int n)
{
    std::stack<int> args;
    args.push(0);
    args.push(n-1);
    while (!args.empty())
    {
        int high = args.top(); args.pop();
        int low = args.top(); args.pop();
        if (low < high)
        {
            int pivot = Partition(array, low, high);
            args.push(pivot+1);
            args.push(high);
            args.push(low);
            args.push(pivot-1);
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
    int array[] = {5, 2, 4, 0};
    int array2[] = {5, 2, 4, 0};
    
    PrintArray(array, 4);
    QuickSort(array, 4);
    QuickSortIterative(array2, 4);
    std::cout << "Sorted array: ";
    PrintArray(array, 4);
    PrintArray(array2, 4);

    return 0;
}

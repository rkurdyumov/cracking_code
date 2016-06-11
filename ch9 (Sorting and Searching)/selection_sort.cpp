#include <iostream>

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
    std::cout << std::endl;
}

int main()
{
    int array[] = {5, 4, 2, 0};
    
    PrintArray(array, 4);
    SelectionSort(array, 4);
    std::cout << "Sorted array: ";
    PrintArray(array, 4);

    return 0;
}

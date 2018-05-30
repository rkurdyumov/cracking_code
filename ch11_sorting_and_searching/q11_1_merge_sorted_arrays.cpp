/*
You are given two sorted arrays, A and B, and A has a large enough buffer at 
the end to hold B. Write a method to merge B into A in sorted order.
*/

#include <iostream>

// Assume A[] has enough room for merging A and B. Merge from the back, 
// comparing each element from A and B.
void MergeSortedArrays(int A[], int nA, int B[], int nB)
{
    int iA = nA - 1; // last A element index
    int iB = nB - 1; // last B element index
    int iM = nA + nB - 1; // last merged index

    while (iA >= 0 && iB >= 0)
    {
        if (A[iA] > B[iB])
            A[iM--] = A[iA--];
        else
            A[iM--] = B[iB--];
    }
    while (iB >= 0)
        A[iM--] = B[iB--];
    // Don't need to move remaining elements in A, they are already in place
}

void PrintArray(int array[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}

int main()
{
    const int A_SIZE = 4;
    const int B_SIZE = 3;
    
    int A[A_SIZE + B_SIZE] = {1, 2, 3, 7};
    int B[B_SIZE]  = {0, 4, 6};

    std::cout << "A = "; PrintArray(A, A_SIZE);
    std::cout << "B = "; PrintArray(B, B_SIZE);
    MergeSortedArrays(A, A_SIZE, B, B_SIZE);
    std::cout << "Merge = "; PrintArray(A, A_SIZE + B_SIZE);
}

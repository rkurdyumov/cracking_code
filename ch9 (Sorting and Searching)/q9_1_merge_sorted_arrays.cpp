#include <iostream>

// Assume A[] has enough room for merging A and B
void MergeSortedArrays(int A[], int nA, int B[], int nB)
{
    int iA = nA - 1;
    int iB = nB - 1;
    int iM = nA + nB - 1;

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
}

int main()
{
    int A[7] = {1, 2, 3, 7};
    int B[]  = {0, 4, 6};

    std::cout << "A = "; PrintArray(A, 4); std::cout << std::endl;
    std::cout << "B = "; PrintArray(B, 3); std::cout << std::endl;
    MergeSortedArrays(A, 4, B, 3);
    std::cout << "Merge = "; PrintArray(A, 7); std::cout << std::endl;

}

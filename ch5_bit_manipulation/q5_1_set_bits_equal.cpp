/*
You are given two 32-bit numbers, N and M, and two bit positions, i and j. 
Write a method to insert M into N such that M starts at bit j and end at bit 
i. You can assume that the bits j through i have enough space to fit all of M.
That is, if M = 10011, you can assume that there are at least 5 bits between j
and i.  You would not, for example, have j = 3 and i = 2 because M could not
fully fit between bit 3 and bit 2.

EXAMPLE:
Input:  N = 10000000000, M = 10011, i = 2, j = 6
Output: N = 10001001100
*/

#include <iostream>
#include <bitset>

// Solution: Make a bit-mask that clears bits [i, j] in N, then use OR to put
// M in those spots.
static int UpdateBits(uint32_t N, uint32_t M, size_t i, size_t j)
{
    // Example for i = 2, j = 6
    uint32_t left = (~0) << (j+1); // 1111 1000 0000
    uint32_t right = (1 << i) - 1; // 0000 0000 0011
    uint32_t mask = left | right;  // 1111 1000 0011
    return (N & mask) | (M << i);
}

int main()
{
    uint32_t N = 0b10000000000;
    uint32_t M = 0b10011;
    size_t i = 2, j = 6;
    
    std::cout << "N = " << std::bitset<16>(N) << "\nM = " << 
        std::bitset<16>(M) << "\n";
    std::cout << "Set bits [" << i << "," << j << "] in N equal to M:\n" << 
        "N = " << std::bitset<16>(UpdateBits(N, M, i, j)) << "\n";
}

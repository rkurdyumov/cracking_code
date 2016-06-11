#include <iostream>

const int N_COINS = 4;

int CheckTotal(int coins[], int curr_coin, int target)
{
    // Base case: we are using 1 cent coin (which can always be used to represent n cents)
    if (curr_coin == N_COINS-1) return 1;
    // We are using >1 cent coin
    int total = 0;
    // First try large denomination, then move to smaller denominations as long
    // as we stay below the total sum.  When we can only use 1 cent coin, we have
    // the base case and there's only one way to complete the sum.
    for (int i = 0; i*coins[curr_coin] <= target; ++i)
    {
        total += CheckTotal(coins, curr_coin + 1, target - i*coins[curr_coin]);
    }
    return total;
}


int main()
{
    int coins[N_COINS] = {25, 10, 5, 1};
    int target = 100;
    int num_ways = CheckTotal(coins, 0, target);
    std::cout << "There are " << num_ways << " ways to represent " << target 
        << " cents" << std::endl;
    return 0;
}

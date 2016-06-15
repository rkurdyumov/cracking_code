/*
A circus is designing a tower routine consisting of people standing atop one 
another's shoulders. For practical and aesthetic reasons, each person must be 
both shorter and lighter than the person below him or her. Given the heights 
and weights of each person in the circus, write a method to compute the largest 
possible number of people in such a tower.
EXAMPLE:
Input (ht, wt): (65, 100) (70, 150) (56, 90) (75, 190) (60, 95) (68, 98)
Output: The longest tower is length 6 and includes from top to bottom: (56, 90)
(60,95) (68,98) (70,150) (75,190)

NOTE: The input was slightly modified from the one in the book to cover more
edge conditions in the code.
*/

#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <iomanip> // std::setw

struct Person
{
    int height;
    int weight;
    Person(int h, int w) : height(h), weight(w) { }
};

bool CompareHeightsThenWeights(const Person &p1, const Person &p2) 
{ 
    if (p1.height != p2.height) 
        return p1.height < p2.height; 
    return p1.weight < p2.weight;
}

// Find the first element larger than or equal to input value
int BinarySearchSubseq(std::vector<int> & last_subseq_values, int low, int high, 
        int value)
{
    while (high > low)
    {
        int mid = low + (high - low)/2;
        if (last_subseq_values[mid] >= value)
            high = mid;
        else
            low = mid+1;
    }
    return high;
}

// Helper function to assemble the indices of the longest possible tower of 
// people ordered tallest->smallest
std::vector<int> MakeLongestSubseq(std::vector<int> & last_subseq_indices, 
        std::vector<int> & prev_indices)
{
    size_t length = last_subseq_indices.size() - 1;
    std::vector<int> longest_subseq(length);
    size_t curr_index = last_subseq_indices[length];
    longest_subseq[0] = curr_index;
    for (size_t i = 1; i < length; ++i)
    {
        curr_index = prev_indices[curr_index];
        longest_subseq[i] = curr_index;
    }
    return longest_subseq; // ordered tallest->shortest
}

// Use a standard "find longest subsequence" algorithm on weights after sorting
// by heights to find the max number of people in a tower.  This code is more
// complicated because we also try to store the order of people in the tower, 
// not just the maximum tower size.
//
// Basically, there are 4 vectors used, shown below with their state at the end 
// of the algorithm:
// people:             (56,90) (60,95) (65,100) (68,98) (70,150) (75,190)
// index (implicit):   0       1       2        3       4        5
// prev_index:         -1      0       1        1       3        4
//
// last_subseq_index:   L1:0    L2:1    L3:3     L4:4     L5:5
// last_subseq_value:  (56,90) (60,95) (68,98)  (70,150) (75,190)
std::vector<int> MaxTower(std::vector<Person> &people)
{
    if (people.empty()) 
        return std::vector<int>();

    // Sort by heights (and equal heights by weights)
    std::sort(people.begin(), people.end(), CompareHeightsThenWeights);

    // Create a vector where the i'th entry corresponds to the lowest ending
    // value of subsequence with length i found so far (so entry 0 is a dummy)
    std::vector<int> last_subseq_value(2);
    last_subseq_value[1] = people[0].weight; // initialize with first 
    // Keep track of the last index in each subsequence so we can backtrack and 
    // print longest subsequence later
    std::vector<int> last_subseq_index(2);
    last_subseq_index[1] = 0;
    // Previous index in longest subsequence using this person
    std::vector<int> prev_index(people.size(), -1);
    prev_index[0] = -1;

    for (size_t i = 1; i < people.size(); ++i)
    {
        int li = last_subseq_value.size() - 1; // last subsequence index

        if (people[i].weight < last_subseq_value[1]) // new value for length 1
        {
            last_subseq_value[1] = people[i].weight;
            last_subseq_index[1] = i;
            prev_index[i] = -1;        
        }
        else if (people[i].weight >= last_subseq_value[li]) // new longest
        {
            last_subseq_value.push_back(people[i].weight);
            prev_index[i] = last_subseq_index[li];
            last_subseq_index.push_back(i);
        }
        else
        {
            // Search for the longest current subsequence whose ending value can
            // be lowered by this new value
            int low = 2; // length 1 subsequence case covered above
            int high = last_subseq_value.size() - 1;
            int index = BinarySearchSubseq(last_subseq_value, low, high, people[i].weight);
            last_subseq_value[index] = people[i].weight;
            prev_index[i] = prev_index[last_subseq_index[index]];;
            last_subseq_index[index] = i;
        }
    }
    return MakeLongestSubseq(last_subseq_index, prev_index);
}

int main()
{
    std::vector<Person> people;
    people.push_back(Person(65,100));
    people.push_back(Person(70,150));
    people.push_back(Person(56,90));
    people.push_back(Person(75,190));
    people.push_back(Person(60,95));
    people.push_back(Person(68,98));

    std::vector<int> tower = MaxTower(people);
    int size = tower.size();

    std::cout << "Max tower size is " << size << std::endl;
    for (int i = 0; i < size; ++i)
        std::cout << "(" << people[tower[i]].height << "," << 
            people[tower[i]].weight << ")->";
    std::cout << "top\n";
}

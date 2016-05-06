#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // for setw()

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
int BinarySearchSubseq(std::vector<int> &last_subseq_values, int low, int high, int value)
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

// Use a standard "find longest subsequence" algorithm on weights after sorting
// by heights to find the max number of people in a tower
std::vector<int> MaxTower(std::vector<Person> &people)
{
    if (people.empty()) return std::vector<int>();

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

    int length = last_subseq_value.size() - 1;
    std::vector<int> longest_subseq(length);
    int curr_index = last_subseq_index[last_subseq_index.size() - 1];
    longest_subseq[0] = curr_index;
    for (int i = 1; i < length; ++i)
    {
        curr_index = prev_index[curr_index];
        longest_subseq[i] = curr_index;
    }
    return longest_subseq; // ordered tallest->shortest
}

int main()
{
    std::vector<Person> people;
    people.push_back(Person(60,100));
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
    std::cout << "top" << std::endl;

    return 0;
}

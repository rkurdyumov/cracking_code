#include <iostream>
#include <vector>
#include "binary_search_tree.h"

class MyBST : public BinarySearchTree<int>
{
    public:
        MyBST(int array[], size_t size);
        void PrintAllPaths(int sum);
    private:
        Node * BuildBST(int array[], int low, int high);
        void CheckPathRecursive(Node * n, int sum_left,
                std::vector<std::vector<int>> & paths, std::vector<int> path);
};

MyBST::MyBST(int array[], size_t size)
{
    this->root = BuildBST(array, 0, size-1);
}

MyBST::Node * MyBST::BuildBST(int array[], int low, int high)
{
    if (low > high)
        return nullptr;
    int mid = low + (high - low)/2;
    Node * n = new Node(array[mid]);
    n->left = BuildBST(array, low, mid-1);
    n->right = BuildBST(array, mid+1, high);
    return n;
}

void MyBST::PrintAllPaths(int sum)
{
    std::vector<std::vector<int>> paths;
    CheckPathRecursive(this->root, sum, paths, std::vector<int>());
    std::cout << "All paths that sum to " << sum << ":\n";
    for (auto path : paths)
    {
        for (auto i : path)
        {
            std::cout << i << "->";
        }
        std::cout << "end\n";
    }
}

void MyBST::CheckPathRecursive(Node * n, int sum,
        std::vector<std::vector<int>> & paths, std::vector<int> path)
{
    if (n == nullptr)
        return;
    path.push_back(n->data);
    int sum_left = sum;
    for (size_t i = path.size(); i != 0; --i)
    {
        sum_left -= path[i-1];
        if (sum_left == 0)
        {
            std::vector<int>::const_iterator first = path.begin() + (i-1);
            std::vector<int>::const_iterator last = path.end();
            paths.push_back(std::vector<int>(first, last));
        }
    }
    CheckPathRecursive(n->left, sum, paths, path);
    CheckPathRecursive(n->right, sum, paths, path);
}

int main()
{
    int array[] = {-3, -2, -1, 0, 1, 2, 3};

    MyBST bst(array, sizeof(array)/sizeof(array[0]));
    std::cout << "tree:\n" << bst << "\n";
    
    for (int i = -5; i <= 5; ++i)
        bst.PrintAllPaths(i);
}



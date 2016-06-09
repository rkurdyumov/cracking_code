#include <iostream>
#include "binary_search_tree.h"

template <typename T>
class MyBST: public BinarySearchTree<T>
{
    public:
        bool IsBalanced();

    private:
        int IsBalanced(typename BinarySearchTree<T>::Node * n);
};

template <typename T>
bool MyBST<T>::IsBalanced()
{
    return IsBalanced(BinarySearchTree<T>::root) != -1;
}

template <typename T>
int MyBST<T>::IsBalanced(typename BinarySearchTree<T>::Node * n)
{
    if (n == nullptr)
        return 0;
    
    int left_depth = IsBalanced(n->left);
    if (left_depth == -1)
        return -1;
    int right_depth = IsBalanced(n->right);
    if (right_depth == -1)
        return -1;
    
    int depth_diff = left_depth - right_depth;
    if (depth_diff > 1 || depth_diff < -1)
        return -1;

    return std::max(left_depth, right_depth) + 1;
}

int main()
{
    MyBST<int> bst;

    int insert_array[] = {5, 1, 9, 3, 7, 0, 2};
    for (size_t i = 0; i < sizeof(insert_array)/sizeof(insert_array[0]); ++i)
        bst.Insert(insert_array[i]);
    std::cout << bst << "\n";
    std::cout << "Is balanced: " << bst.IsBalanced() << "\n";

    bst.Remove(7);
    std::cout << bst << "\n";
    std::cout << "Is balanced: " << bst.IsBalanced() << "\n";

}

/*
You have two very large binary trees: T1, with millions of nodes, and T2, with 
hundreds of nodes. Create an algorithm to decide if T2 is a subtree of T1.
*/

#include <iostream>
#include <string>
#include "binary_search_tree.h"

template <typename T>
class MyBST : public BinarySearchTree<T>
{
    public:
        MyBST() : BinarySearchTree<T>::BinarySearchTree() {}
        MyBST(T array[], size_t size);
        bool ContainsSubtree(const MyBST & other) const; // O(N*M) time, O(1) space
        bool ContainsSubtree2(const MyBST & other) const; // O(N) time, O(N) space

    private:
        typename BinarySearchTree<T>::Node * BuildBST(T array[], int low, int high);
        bool IsSubtree(typename BinarySearchTree<T>::Node * tree, 
                typename BinarySearchTree<T>::Node * subtree) const;
        bool MatchTree(typename BinarySearchTree<T>::Node * tree, 
                typename BinarySearchTree<T>::Node * subtree) const;
        void PreOrderTraversalWithNullChar(typename BinarySearchTree<T>::Node * n,
                std::string & str) const;
};

template <typename T>
MyBST<T>::MyBST(T array[], size_t size)
{
    this->root = BuildBST(array, 0, size-1);
    this->size = size;
}

template <typename T>
typename BinarySearchTree<T>::Node * MyBST<T>::BuildBST(T array[], int low, int high)
{
    if (low > high)
        return nullptr;
    int mid = low + (high - low)/2;
    typename BinarySearchTree<T>::Node * n = new typename BinarySearchTree<T>::Node(array[mid]);
    n->left = BuildBST(array, low, mid-1);
    n->right = BuildBST(array, mid+1, high);
    return n;
}


// Method 1: Recursive search
// Worst case time complexity: O(N*M) where N=tree size, M=subtree size
// This method returns true even if the subtree is internal to the tree (subtree
// does not need to contain all leaf nodes starting from common root)
template <typename T>
bool MyBST<T>::ContainsSubtree(const MyBST & other) const
{
    if (other.IsEmpty()) return true;
    return IsSubtree(this->root, other.root);
}

template <typename T>
bool MyBST<T>::IsSubtree(typename BinarySearchTree<T>::Node * tree, 
                typename BinarySearchTree<T>::Node * subtree) const
{
    if (tree == nullptr) // we know subtree is non-empty here
        return false;
    if (MatchTree(tree, subtree))
        return true;
    return IsSubtree(tree->left, subtree) || IsSubtree(tree->right, subtree);
}

template <typename T>
bool MyBST<T>::MatchTree(typename BinarySearchTree<T>::Node * tree, 
                typename BinarySearchTree<T>::Node * subtree) const
{
    // Commented code returns true only for subtree that has ALL common root descendants
    /*
    if (tree == nullptr && subtree == nullptr)
        return true; // exhausted both tree and subtree
    if (tree == nullptr || subtree == nullptr)
        return false; // only one of tree or subtree is empty
    */
    if (subtree == nullptr)
        return true; // exhausted subtree
    if (tree == nullptr)
        return false; // tree exhausted but subtree isn't yet
    if (tree->data != subtree->data)
        return false;
    return MatchTree(tree->left, subtree->left) && MatchTree(tree->right, subtree->right);
}

// Method 1: Substring search on pre-order traversal with null markers
// Worst case time complexity: O(N) where N=tree size
// Space complexity: O(N) where N=tree size
// This method returns false if the subtree is internal to the tree (subtree
// needs to contain all leaf nodes starting from common root)
template <typename T>
bool MyBST<T>::ContainsSubtree2(const MyBST & other) const
{
    if (other.IsEmpty()) return true;
    if (this->IsEmpty()) return false;

    std::string tree_pre_order, subtree_pre_order;
  
    tree_pre_order.reserve(this->Size());
    subtree_pre_order.reserve(other.Size());

    this->PreOrderTraversalWithNullChar(this->root, tree_pre_order);
    other.PreOrderTraversalWithNullChar(other.root, subtree_pre_order);

    size_t found = tree_pre_order.find(subtree_pre_order); // O(n) time complexity
    return found != std::string::npos;
}

template <typename T>
void MyBST<T>::PreOrderTraversalWithNullChar(typename BinarySearchTree<T>::Node * n,
        std::string & str) const
{
    if (n == nullptr)
    {
        str += "-";
        return;
    }
    str += std::to_string(n->data);
    PreOrderTraversalWithNullChar(n->left, str);
    PreOrderTraversalWithNullChar(n->right, str);
}

int main()
{
    int array[] = {1, 2, 3, 4, 5, 6, 7};
    int sub_array1[] = {1, 2, 3};
    int sub_array2[] = {2, 3, 4, 5, 6, 7};
    int sub_array3[] = {0, 4, 8};
    
    MyBST<int> tree(array, sizeof(array)/sizeof(array[0]));
    MyBST<int> subtree1(sub_array1, sizeof(sub_array1)/sizeof(sub_array1[0]));
    MyBST<int> subtree2(sub_array2, sizeof(sub_array2)/sizeof(sub_array2[0]));
    MyBST<int> subtree3(sub_array3, sizeof(sub_array3)/sizeof(sub_array3[0]));
    MyBST<int> empty_tree;
    

    std::cout << "tree:\n" << tree << "\n";
    std::cout << "subtree1:\n" << subtree1 << "\n";
    std::cout << "subtree2:\n" << subtree2 << "\n";
    std::cout << "subtree3:\n" << subtree3 << "\n";

    std::cout << "Recursive search method:\n";
    std::cout << "tree contains subtree1: " << tree.ContainsSubtree(subtree1) << "\n";
    std::cout << "tree contains subtree2: " << tree.ContainsSubtree(subtree2) << "\n";
    std::cout << "tree contains subtree3: " << tree.ContainsSubtree(subtree3) << "\n";
    std::cout << "tree contains empty subtree: " << tree.ContainsSubtree(empty_tree) << "\n";

    std::cout << "\nSubstring search method with pre-order traversal:\n";
    std::cout << "tree contains subtree1: " << tree.ContainsSubtree2(subtree1) << "\n";
    std::cout << "tree contains subtree2: " << tree.ContainsSubtree2(subtree2) << "\n";
    std::cout << "tree contains subtree3: " << tree.ContainsSubtree2(subtree3) << "\n";
    std::cout << "tree contains empty subtree: " << tree.ContainsSubtree2(empty_tree) << "\n";
}

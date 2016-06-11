/*
Given a binary search tree, design an algorithm which creates a linked list of 
all the nodes at each depth (i.e., if you have a tree with depth D, you'll have 
D linked lists).
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <list>
#include "binary_search_tree.h"

template <typename T>
class MyBST : public BinarySearchTree<T>
{
    public:    
        std::vector<std::list<T>> GetNodesAtEachDepth();

    private:
        void BuildList(typename BinarySearchTree<T>::Node *n, 
                std::vector<std::list<T>> & lists, int depth);
};

template <typename T>
std::vector<std::list<T>> MyBST<T>::GetNodesAtEachDepth()
{
    std::vector<std::list<T>> lists;
    BuildList(this->root, lists, 0);
    return lists;
}

template <typename T>
void MyBST<T>::BuildList(typename BinarySearchTree<T>::Node *n, 
        std::vector<std::list<T>> & lists, int depth)
{
    if (n == nullptr) 
        return;
    assert (depth <= lists.size());
    if (depth == lists.size())
        lists.push_back(std::list<T>(1, n->data));
    else
        lists[depth].push_back(n->data);
    BuildList(n->left, lists, depth + 1);
    BuildList(n->right, lists, depth + 1);
}

int main()
{
    
    MyBST<int> bst_int;
    int insert_array[] = {3, 1, 5, 0, 2, 4, 6};
    for (size_t i = 0; i < sizeof(insert_array)/sizeof(insert_array[0]); ++i)
        bst_int.Insert(insert_array[i]);

    std::cout << "int BST of size "  << bst_int.Size() <<  ":\n";
    std::cout << bst_int << "\n";

    std::vector<std::list<int>> lists = bst_int.GetNodesAtEachDepth();
    for (auto list : lists)
    {
        for (auto elem : list)
            std::cout << elem << "->";
    std::cout << "\n";
    }
}

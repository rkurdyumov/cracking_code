#include "binary_search_tree.h"

#ifndef BINARY_SEARCH_TREE_CPP
#define BINARY_SEARCH_TREE_CPP

// Make deep copy of node n and all nodes below it recursively
template <typename T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::Node::Copy() const
{
    if (this == nullptr)
        return nullptr;
    return new Node(data, left->Copy(), right->Copy());
}

template <typename T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::Node::Find(const T & value)
{
    Node * curr = this;
    while (curr != nullptr)
    {
        if (value < curr->data)
            curr = curr->left;
        else if (value > curr->data)
            curr = curr->right;
        else break;
    }
    return curr;
}

template <typename T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::Node::FindParent(const T & value)
{
    Node * curr = this;
    if (curr == nullptr) return nullptr; // in case of empty tree
    if ((left != nullptr && left->data == value) || 
            (right != nullptr && right->data == value))
        return curr; // found parent
    if (left != nullptr && value < curr->data)
        return left->FindParent(value);
    if (right != nullptr && value > curr->data)
        return right->FindParent(value);
    return nullptr;
}

template <typename T>
typename BinarySearchTree<T>::Node ** BinarySearchTree<T>::Node::Where(const T & value)
{
    if (value < data)
    {
        if (left == nullptr)
            return &left;
        else
            return left->Where(value);
    }
    if (value > data)
    {
        if (right == nullptr)
            return &right;
        else
            return right->Where(value);
    }
    return nullptr;
}

// Remove Node with given value.  Must be called by parent Node or higher.
template <typename T>
bool BinarySearchTree<T>::Node::Remove(const T & value)
{
    Node * parent = this->FindParent(value);
    if (parent == nullptr) return false; // value doesn't exist

    Node * curr = parent->left;
    Node ** parent_dir_ptr = &parent->left;
    // Figure out if we're the left or right child
    if (curr == nullptr || curr->data != value)
    {
        curr = parent->right;
        parent_dir_ptr = &parent->right;
    }
    // Remove node with two children: replace it with min element in right subtree
    if (curr->left != nullptr && curr->right != nullptr)
    {
        T min_data = curr->right->MinValue();
        curr->Remove(min_data); // remove old Node from right subtree
        curr->data = min_data;
    }
    // Remove node with <= 1 child, update parent's left/right pointer
    else 
    {
        *parent_dir_ptr = (curr->left == nullptr) ? curr->right : curr->left;
        curr->left = curr->right = nullptr; // delete is recursive so take out of tree
        delete curr;
    }
    return true;
}

template <typename T>
const T & BinarySearchTree<T>::Node::MinValue() const
{
    if (left == nullptr) 
        return data;
    return left->MinValue();
}

template <typename T>
const T & BinarySearchTree<T>::Node::MaxValue() const
{
    if (right == nullptr) 
        return data;
    return right->MaxValue();
}

// Use in-order traversal and check if elements are sorted
template <typename T>
bool BinarySearchTree<T>::Node::IsBST(Node * prev_node) const
{
    if (this == nullptr)
        return true;
    if (!left->IsBST(prev_node))
        return false;
    if (prev_node != nullptr && data <= prev_node->data) // don't allow duplicate values
        return false;
    if (!right->IsBST(prev_node))
        return false;
    return true;
}

// Use in-order traversal and check if elements are sorted
template <typename T>
bool BinarySearchTree<T>::Node::IsEqual(Node * other) const
{
    if (this == other) 
        return true;
    if (this == nullptr || other == nullptr) // more leaves on one BST
        return false;
    if (data != other->data)
       return false;
    return (left->IsEqual(other->left) && right->IsEqual(other->right));
}

// Recursive print function that keeps track of indentation for each tree level
template <typename T>
void BinarySearchTree<T>::Node::Print(std::ostream & out, int indent = 0) const
{
    if (indent > 0)
        out << std::setw(indent) << ' ';
    if (this == nullptr) 
    {
        out << '-' << "\n";
        return;
    }
    out << data << "\n";
    right->Print(out, indent + 2);
    left->Print(out, indent + 2);
}

template <typename T>
void BinarySearchTree<T>::Node::PrintPreOrder(std::ostream & out) const
{
    if (this == nullptr) 
        return;
    out << data << " ";
    left->PrintPreOrder(out);
    right->PrintPreOrder(out);
}

template <typename T>
void BinarySearchTree<T>::Node::PrintInOrder(std::ostream & out) const
{
    if (this == nullptr) 
        return;
    left->PrintInOrder(out);
    out << data << " ";
    right->PrintInOrder(out);
}
    
template <typename T>
void BinarySearchTree<T>::Node::PrintPostOrder(std::ostream & out) const
{
    if (this == nullptr) 
        return;
    left->PrintPostOrder(out);
    right->PrintPostOrder(out);
    out << data << " ";
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree & other)
{
    size = other.size;
    root = other.root->Copy(); // deep copy using recursion
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    delete root;    
}

template <typename T>
void BinarySearchTree<T>::swap(BinarySearchTree & other) 
{
    std::swap(root, other.root);
    std::swap(size, other.size);
}

template <typename T>
BinarySearchTree<T> & BinarySearchTree<T>::operator=(BinarySearchTree other)
{
    swap(other);
    return *this;
}

template <typename T>
bool BinarySearchTree<T>::operator==(BinarySearchTree & other)
{
    return root->IsEqual(other.root);
}

template <typename T>
std::ostream & operator<<(std::ostream & out, const BinarySearchTree<T> & bst)
{
    bst.root->Print(out, 0);
    return out;
}

template <typename T>
void BinarySearchTree<T>::Insert(const T & value)
{
    Node ** where = &root;
    if (!IsEmpty())
    {
        where = root->Where(value);
        if (where == nullptr) 
            return; // already in tree
    }
    *where = new Node(value);
    ++size;
}

template <typename T>
bool BinarySearchTree<T>::Remove(const T & value)
{
    if (IsEmpty()) 
        return false;
    // Case 1: removing root.  Replace root with either inorder predecessor or successor
    if (root->data == value)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr; // Probably not really needed
            --size;
            return true;
        }
        // Get value of inorder predecessor or successor
        T new_value = (root->right == nullptr) ? root->left->MaxValue() : root->right->MinValue();
        // First delete the Node with the value we've copied (since removing it
        // relies on the root having it's original unique value)
        root->Remove(new_value); // should always succeed so ignore return value
        --size;
        // Then copy the value from the deleted node to the root
        root->data = new_value;
        return true;
    }
    // Case 2: removing non-root node
    bool deleted = root->Remove(value);
    if (deleted) 
        --size;
    return deleted;
}

template <typename T>
bool BinarySearchTree<T>::Contains(const T & value) const
{
    return !IsEmpty() && root->Find(value);
}

template <typename T>
const T & BinarySearchTree<T>::MinValue() const
{
    return root->MinValue();
}

template <typename T>
const T & BinarySearchTree<T>::MaxValue() const
{
    return root->MaxValue();
}

template <typename T>
void BinarySearchTree<T>::Clear()
{
    delete root;
    root = nullptr; // not strictly necessary
    size = 0;
}

template <typename T>
bool BinarySearchTree<T>::IsEmpty() const
{
    return size == 0;
}

template <typename T>
size_t BinarySearchTree<T>::Size() const
{
    return size;
}

template <typename T>
bool BinarySearchTree<T>::IsBST() const
{
    return root->IsBST(nullptr);
}

template <typename T>
void BinarySearchTree<T>::PrintPreOrder(std::ostream & out) const
{
    root->PrintPreOrder(out);
}

template <typename T>
void BinarySearchTree<T>::PrintInOrder(std::ostream & out) const
{
    root->PrintInOrder(out);
}

template <typename T>
void BinarySearchTree<T>::PrintPostOrder(std::ostream & out) const
{
    root->PrintPostOrder(out);
}

#endif

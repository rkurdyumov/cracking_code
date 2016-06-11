#include <iomanip> // std::setw
#include "utility" // std::swap


template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree & other)
{
    size = other.size;
    root = other.Copy(other.root); // deep copy using recursion
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
    return IsEqual(root, other.root);
}

template <typename T>
std::ostream & operator<<(std::ostream & out, const BinarySearchTree<T> & bst)
{
    bst.Print(bst.root, out, 0);
    return out;
}

// Recursive print function that keeps track of indentation for each tree level
template <typename T>
void BinarySearchTree<T>::Print(const Node * n, std::ostream & out, int indent) const
{
    if (indent > 0)
        out << std::setw(indent) << ' ';
    if (n == nullptr) 
    {
        out << '-' << "\n";
        return;
    }
    out << n->data << "\n";
    Print(n->right, out, indent + 2);
    Print(n->left, out, indent + 2);
}


template <typename T>
void BinarySearchTree<T>::Insert(const T & value)
{
    Node ** where = &root;
    if (!IsEmpty())
    {
        where = Where(root, value);
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
        T new_value = (root->right == nullptr) ? MaxValue(root->left) : MinValue(root->right);
        // First delete the Node with the value we've copied (since removing it
        // relies on the root having it's original unique value)
        Remove(root, new_value); // should always succeed so ignore return value
        --size;
        // Then copy the value from the deleted node to the root
        root->data = new_value;
        return true;
    }
    // Case 2: removing non-root node
    bool deleted = Remove(root, value);
    if (deleted) 
        --size;
    return deleted;
}

template <typename T>
bool BinarySearchTree<T>::Contains(const T & value) const
{
    return !IsEmpty() && Find(root, value);
}

template <typename T>
const T & BinarySearchTree<T>::MinValue() const
{
    return MinValue(root);
}

template <typename T>
const T & BinarySearchTree<T>::MaxValue() const
{
    return MaxValue(root);
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
    return IsBST(root, nullptr);
}

template <typename T>
const T & BinarySearchTree<T>::MinValue(const Node * curr) const
{
    // Assume current pointer is not nullptr
    if (curr->left == nullptr)
        return curr->data;
    return MinValue(curr->left);
}

template <typename T>
const T & BinarySearchTree<T>::MaxValue(const Node * curr) const
{
    // Assume current pointer is not nullptr
    if (curr->right == nullptr) 
        return curr->data;
    return MaxValue(curr->right);
}

// Make deep copy of node n and all nodes below it recursively
template <typename T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::Copy(
        const BinarySearchTree<T>::Node * n) const
{
    if (n == nullptr)
        return nullptr;
    return new Node(n->data, Copy(n->left), Copy(n->right));
}

template <typename T>
const typename BinarySearchTree<T>::Node * BinarySearchTree<T>::Find(
        const Node * curr, const T & value) const
{
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
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::FindParent(
        Node * curr, const T & value)
{
    if (curr == nullptr) return nullptr; // in case of empty tree
    if ((curr->left != nullptr && curr->left->data == value) || 
            (curr->right != nullptr && curr->right->data == value))
        return curr; // found parent
    if (curr->left != nullptr && value < curr->data)
        return FindParent(curr->left, value);
    if (curr->right != nullptr && value > curr->data)
        return FindParent(curr->right, value);
    return nullptr;
}

template <typename T>
typename BinarySearchTree<T>::Node ** BinarySearchTree<T>::Where(
        Node * curr, const T & value)
{
    if (curr == nullptr) return nullptr;

    if (value < curr->data)
    {
        if (curr->left == nullptr)
            return &curr->left;
        else
            return Where(curr->left, value);
    }
    if (value > curr->data)
    {
        if (curr->right == nullptr)
            return &curr->right;
        else
            return Where(curr->right, value);
    }
    return nullptr; // don't allow duplicate entries
}

// Remove Node with given value.  Ancestor must be parent Node or higher.
template <typename T>
bool BinarySearchTree<T>::Remove(Node * ancestor, const T & value)
{
    Node * parent = FindParent(ancestor, value);
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
        T min_data = MinValue(curr->right);
        Remove(curr, min_data); // remove old Node from right subtree
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

// Use in-order traversal and check if elements are sorted
template <typename T>
bool BinarySearchTree<T>::IsBST(const Node * curr, const Node * prev) const
{
    if (curr == nullptr)
        return true;
    if (!IsBST(curr->left, prev))
        return false;
    // Don't allow duplicate values (use <=)
    if (prev != nullptr && curr->data <= prev->data)
        return false;
    return IsBST(curr->right, curr);
}

template <typename T>
bool BinarySearchTree<T>::IsEqual(const Node * curr, const Node * other) const
{
    if (curr == other) 
        return true;
    if (curr == nullptr || other == nullptr) // more leaves on one BST
        return false;
    if (curr->data != other->data)
       return false;
    return (IsEqual(curr->left, other->left) && IsEqual(curr->right, other->right));
}

template <typename T>
void BinarySearchTree<T>::PrintPreOrder(std::ostream & out) const
{
    PrintPreOrder(root, out);
}

template <typename T>
void BinarySearchTree<T>::PrintInOrder(std::ostream & out) const
{
    PrintInOrder(root, out);
}

template <typename T>
void BinarySearchTree<T>::PrintPostOrder(std::ostream & out) const
{
    PrintPostOrder(root, out);
}

template <typename T>
void BinarySearchTree<T>::PrintPreOrder(const Node * n, std::ostream & out) const
{
    if (n == nullptr) 
        return;
    out << n->data << " ";
    PrintPreOrder(n->left, out);
    PrintPreOrder(n->right, out);
}

template <typename T>
void BinarySearchTree<T>::PrintInOrder(const Node * n, std::ostream & out) const
{
    if (n == nullptr) 
        return;
    PrintInOrder(n->left, out);
    out << n->data << " ";
    PrintInOrder(n->right, out);
}
    
template <typename T>
void BinarySearchTree<T>::PrintPostOrder(const Node * n, std::ostream & out) const
{
    if (n == nullptr) 
        return;
    PrintPostOrder(n->left, out);
    PrintPostOrder(n->right, out);
    out << n->data << " ";
}


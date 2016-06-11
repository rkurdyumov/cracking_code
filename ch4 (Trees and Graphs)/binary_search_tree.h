#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <ostream>

template <typename T>
class BinarySearchTree
{
    public:
        
        BinarySearchTree() {} // default constructor
        BinarySearchTree(const BinarySearchTree & other); // copy constructor
        ~BinarySearchTree();
        BinarySearchTree & operator=(BinarySearchTree other);
        bool operator==(BinarySearchTree & other);
        template <typename U>
        friend std::ostream & operator<<(std::ostream & out, const BinarySearchTree<U> & bst);
        
        void Insert(const T & value);
        bool Remove(const T & value);
        void Clear();
        
        bool Contains(const T & value) const;
        const T & MinValue() const;
        const T & MaxValue() const;
        bool IsEmpty() const;
        size_t Size() const;
        bool IsBST() const;

        void PrintPreOrder(std::ostream & out) const;
        void PrintInOrder(std::ostream & out) const;
        void PrintPostOrder(std::ostream & out) const;

    protected:
        class Node
        {
            public:
                T data;
                Node *left = nullptr;
                Node *right = nullptr;
                
                Node(const T& value, Node *l = nullptr, Node *r = nullptr) : 
                    data(value), left(l), right(r) {}
                ~Node() { delete left; delete right; }
        };
        
        Node *root = nullptr;
        size_t size = 0;
    
    private:
        void swap(BinarySearchTree & other);
        
        const T & MinValue(const Node * curr) const; // find Node with minimum value
        const T & MaxValue(const Node * curr) const; // find Node with minimum value
        
        Node * Copy(const Node * n) const; // deep copy
        const Node * Find(const Node * curr, const T & value) const; // find Node with value
        Node * FindParent(Node * curr, const T & value);        
        Node ** Where(Node * curr, const T & value); // find place for Node with value
        
        bool Remove(Node * ancestor, const T & value); // remove Node with value
        bool IsBST(const Node * curr, const Node * prev) const;
        bool IsEqual(const Node * curr, const Node * other) const;

        void Print(const Node * n, std::ostream & out, int indent = 0) const; // pretty print
        void PrintPreOrder(const Node * n, std::ostream & out) const;
        void PrintInOrder(const Node * n, std::ostream & out) const;
        void PrintPostOrder(const Node * n, std::ostream & out) const;
};

#include "binary_search_tree.tpp"

#endif

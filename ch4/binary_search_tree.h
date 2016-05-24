#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <ostream>
#include <iomanip> // for std::setw() 
#include <utility? // for std::swap()

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

    private:
        class Node
        {
            public:
                T data;
                Node *left = nullptr;
                Node *right = nullptr;
                
                Node(const T& value, Node *l = nullptr, Node *r = nullptr) : 
                    data(value), left(l), right(r) {}
                ~Node() { delete left; delete right; }
                
                Node * Copy() const; // deep copy
                Node * Find(const T & value); // find Node with value
                Node ** Where(const T & value); // find place for Node with value
                
                bool Remove(const T & value); // remove Node with value
                const T & MinValue() const; // find Node with minimum value
                const T & MaxValue() const; // find Node with minimum value
                bool IsBST(Node * prev_node) const;
                bool IsEqual(Node * other) const;
                
                void Print(std::ostream & out, int indent) const; // recursively print Node
                void PrintPreOrder(std::ostream & out) const;
                void PrintInOrder(std::ostream & out) const;
                void PrintPostOrder(std::ostream & out) const;
            
            private:
                Node * FindParent(const T & value); // find parent of Node with value
        };
        
        Node *root = nullptr;
        size_t size = 0;
        void swap(BinarySearchTree & other);
};

#include "binary_search_tree.cpp"

#endif

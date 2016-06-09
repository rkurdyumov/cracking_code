/*
Design an algorithm and write code to find the first common ancestor of two 
nodes in a binary tree. Avoid storing additional nodes in a data structure. 
NOTE: This is not necessarily a binary search tree.
*/

#include <iostream>
#include <iomanip> // std::setw

class BinaryTree
{
    public:
        struct Node
        {
            Node * left = nullptr;
            Node * right = nullptr;
            Node * parent = nullptr;
            int data;
            Node(Node * p, int value) : parent(p), data(value) {}
            ~Node() { delete left; delete right; }
            int Depth();
        };
        Node * root;
        
        BinaryTree(int array[], int size);
        ~BinaryTree() { delete root; }

        void Print(std::ostream & out) const;

        Node * FirstCommonAncestorUsingParent(Node * n1, Node * n2);
        int FirstCommonAncestor(int value1, int value2);

    private:
        Node * InsertArray(Node * curr, Node * parent, int array[], int low, int high);
        void PrintNodes(std::ostream & out, const Node * n, int indent = 0) const;
        Node * FirstCommonAncestorRecursive(Node * curr, int value1, int value2);
};

BinaryTree::BinaryTree(int array[], int size)
{
    root = InsertArray(root, nullptr, array, 0, size-1);
}

BinaryTree::Node * BinaryTree::InsertArray(Node * curr, Node * parent, 
        int array[], int low, int high)
{
    if (low > high)
        return nullptr;
    int mid = low + (high - low)/2;
    curr = new Node(parent, array[mid]);
    curr->left = InsertArray(curr->left, curr, array, low, mid-1);
    curr->right = InsertArray(curr->right, curr, array, mid+1, high);
    return curr;
}

void BinaryTree::Print(std::ostream & out) const
{
    PrintNodes(out, root);
}
        
void BinaryTree::PrintNodes(std::ostream & out, const Node * n, int indent) const
{
    if (indent > 0)
        out << std::setw(indent) << ' ';
    if (n == nullptr)
    {
        out << "-\n";
        return;
    }
    out << n->data << "\n";
    PrintNodes(out, n->right, indent+2);
    PrintNodes(out, n->left, indent+2);
}

// Time Complexity: O(h), Space Complexity: O(1)
BinaryTree::Node * BinaryTree::FirstCommonAncestorUsingParent(Node * n1, Node * n2)
{
    if (n1 == nullptr || n2 == nullptr) return nullptr;

    int depth1 = n1->Depth();
    int depth2 = n2->Depth();

    int diff = depth1 - depth2;

    if (diff < 0)
    {
        std::swap(n1, n2);
        diff = -diff;
    }

    while (diff--)
        n1 = n1->parent;

    while (n1 && n2)
    {
        if (n1 == n2)
            return n1;
        n1 = n1->parent;
        n2 = n2->parent;
    }
    
    return nullptr;
}

// Time Complexity: O(h), Space Complexity: O(1)
// Assumes both values exist in tree
int BinaryTree::FirstCommonAncestor(int value1, int value2)
{
    Node * anc = FirstCommonAncestorRecursive(root, value1, value2);
    return (anc) ? anc->data : -1;
}

BinaryTree::Node * BinaryTree::FirstCommonAncestorRecursive(Node * curr, 
        int value1, int value2)
{
    if (curr == nullptr) return nullptr;

    if (curr->data == value1 || curr->data == value2)
        return curr;

    Node * left = FirstCommonAncestorRecursive(curr->left, value1, value2);
    Node * right = FirstCommonAncestorRecursive(curr->right, value1, value2);

    if (left && right)
        return curr;
    
    return (left == nullptr) ? right : left;
}

int BinaryTree::Node::Depth()
{
    int depth = -1;
    Node * curr = this;
    while (curr)
    {
        ++depth;
        curr = curr->parent;
    }
    return depth;
}

int main()
{
    int array[] = {1, 2, 3, 4, 5, 6, 7};

    BinaryTree bt(array, sizeof(array)/sizeof(array[0]));
    bt.Print(std::cout);

    BinaryTree::Node * n1 = bt.root->left->left;
    BinaryTree::Node * n2 = bt.root->right->right;
    BinaryTree::Node * n3 = bt.root->right->left;

    BinaryTree::Node * anc = bt.FirstCommonAncestorUsingParent(n1, n2);
    BinaryTree::Node * anc2 = bt.FirstCommonAncestorUsingParent(n3, n2);

    std::cout << "FCA of " << n1->data << " and " << n2->data << " is " << anc->data << "\n";
    std::cout << "FCA of " << n3->data << " and " << n2->data << " is " << anc2->data << "\n";

    int d1 = 2;
    int d2 = 7;

    int d_anc = bt.FirstCommonAncestor(d1, d2);
    std::cout << "FCA of " << d1 << " and " << d2 << " is " << d_anc << "\n";
}

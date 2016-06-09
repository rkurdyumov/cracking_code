/*
Write an algorithm to find the 'next' node (i.e., in-order successor) of a 
given node in a binary search tree where each node has a link to its parent.
*/

#include <iostream>
#include <iomanip>

class BST {
    public:
        struct Node
        {
            Node * left = nullptr;
            Node * right = nullptr;
            Node * parent = nullptr;
            int data;
            Node(Node * p, int value) : parent(p), data(value) {}
            ~Node() { delete left; delete right; }
        };
        Node * root;

        BST(int array[], int size);
        ~BST();

        void Print(std::ostream & out) const;
        void PrintInOrder(std::ostream & out);

    private:
        Node * InOrderSuccessor(Node * n);
        void PrintNodes(std::ostream & out, const Node * n, int indent = 0) const;
        Node * InsertSortedArray(Node * curr, Node * parent, int array[], int low, int high);
        Node * MinNode(Node * n);
};

BST::BST(int array[], int size)
{
    root = InsertSortedArray(root, nullptr, array, 0, size-1);
}

BST::~BST()
{
    delete root;
}

BST::Node * BST::InsertSortedArray(Node * curr, Node * parent, int array[], int low, int high)
{
    if (low > high)
        return nullptr;
    int mid = low + (high - low)/2;
    curr = new Node(parent, array[mid]);
    curr->left = InsertSortedArray(curr->left, curr, array, low, mid-1);
    curr->right = InsertSortedArray(curr->right, curr, array, mid+1, high);
    return curr;
}

void BST::Print(std::ostream & out) const
{
    PrintNodes(out, root);
}

void BST::PrintNodes(std::ostream & out, const Node * n, int indent) const
{
    if (indent > 0)
        out << std::setw(indent) << ' ';
    if (n == nullptr)
    {
        out << "-\n";
        return;
    }
    out << n->data << "\n";
    PrintNodes(out, n->right, indent + 2);
    PrintNodes(out, n->left, indent + 2);
}


BST::Node * BST::InOrderSuccessor(Node * n)
{
    if (n == nullptr) return nullptr;
    if (n->right != nullptr)
        return MinNode(n->right);
    Node * p = n->parent;
    while (p != nullptr && n == p->right)
    {
        n = p;
        p = p->parent;
    }
    return p;
}

void BST::PrintInOrder(std::ostream & out)
{
    Node *curr = MinNode(root);
    while (curr != nullptr)
    {
        std::cout << curr->data << " ";
        curr = InOrderSuccessor(curr);
    }
    out << "\n";
}

BST::Node * BST::MinNode(Node * n)
{
    while (n->left != nullptr)
        n = n->left;
    return n;
}

int main()
{
    int array[] = {1, 2, 3, 4, 5, 6, 7};

    BST bst(array, sizeof(array)/sizeof(array[0]));
    bst.Print(std::cout);
    bst.PrintInOrder(std::cout);
}

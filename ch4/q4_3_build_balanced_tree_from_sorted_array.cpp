#include <iostream>
#include <iomanip> // std::setw

struct Node
{
    Node * left = nullptr;
    Node * right = nullptr;
    int data;
    Node(int value) : data(value) {}
};

// Builds a BST assuming the input array is sorted (increasing order)
Node * BuildBST(int array[], int low, int high)
{
    if (high < low) 
        return nullptr;
    int mid = low + (high - low)/2;
    Node * n = new Node(array[mid]);
    n->left = BuildBST(array, low, mid-1);
    n->right = BuildBST(array, mid+1, high);
    return n;
}

void PrintTree(std::ostream & out, const Node * root, int indent = 0)
{
    if (indent > 0)
        out << std::setw(indent) << ' ';
    if (root == nullptr)
    {
        out << "-\n";
        return;
    }
    out << root->data << "\n";
    PrintTree(out, root->right, indent + 2);
    PrintTree(out, root->left, indent + 2);
}

void DeleteTree(Node * root)
{
    if (root == nullptr) return;
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}

int main()
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6};

    Node * bst = BuildBST(arr, 0, 6);
    PrintTree(std::cout, bst);
    DeleteTree(bst);
}

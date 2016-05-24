#include <iostream>
#include <string>
#include <limits>
#include "binary_search_tree.h"

int main()
{
    
    BinarySearchTree<int> bst_int;
    int insert_array[] = {5, 1, 9, 3, 7, 0, 2};
    for (size_t i = 0; i < sizeof(insert_array)/sizeof(insert_array[0]); ++i)
        bst_int.Insert(insert_array[i]);

    std::cout << "int BST of size "  << bst_int.Size() <<  ":\n";
    std::cout << bst_int << "\n";
    std::cout << "Contains(3): " << bst_int.Contains(3) << " " << 
        "Contains(4): " << bst_int.Contains(4) << " Is BST: " << bst_int.IsBST() << "\n";
    std::cout << "Print pre order: "; bst_int.PrintPreOrder(std::cout); std::cout << "\n";
    std::cout << "Print in order: "; bst_int.PrintInOrder(std::cout); std::cout << "\n";
    std::cout << "Print post order: "; bst_int.PrintPostOrder(std::cout); std::cout << "\n";

    BinarySearchTree<int> bst_int2 = bst_int;
    bool same_tree_flag = (bst_int == bst_int2);

    int remove_array[] = {5, 1, 7, 2, 9, 3, 0};

    for (size_t i = 0; i < sizeof(remove_array)/sizeof(remove_array[0]); ++i)
    {
        bst_int.Remove(remove_array[i]);
        std::cout << "Remove(" << remove_array[i] << "), new size = " <<
            bst_int.Size() << ": \n";
        std::cout << bst_int << "\n";
    }
    
    std::cout << "int BST copy of size "  << bst_int2.Size() <<  ":\n";
    std::cout << bst_int2 << "\n";
    std::cout << "Check if valid copy: " << same_tree_flag << "\n";
    bst_int2.Clear();
    std::cout << "Clear copy, now size = "  << bst_int2.Size() <<  ":\n";
    std::cout << bst_int2 << "\n";

    bst_int2.Insert(5);
    bst_int2.Insert(1);
    std::cout << "Added 5 and 1, now size = " << bst_int2.Size() << ":\n";
    std::cout << bst_int2 << "\n";

    BinarySearchTree<std::string> bst_str;
    bst_str.Insert("C");
    bst_str.Insert("B");
    bst_str.Insert("D");
    bst_str.Insert("A");
    bst_str.Insert("E");

    std::cout << "str BST of size "  << bst_str.Size() <<  ":\n";
    std::cout << bst_str << "\n";
    std::cout << "Contains(\"A\"): " << bst_str.Contains("C") << " " << 
        "Contains(\"F\"): " << bst_str.Contains("F") << " Is BST: " << bst_str.IsBST() << "\n";
}

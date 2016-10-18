#include "../include/BinarySearchTree.h"

// i'm here

template <typename T>
void print(std::ostream& out, BinarySearchTree<T>& tree, std::string name)
{
    out << name << ": \n";
    if (tree.empty())
        out << "is empty.\n";
    else
        out << tree << "\n";
    return;
}

template <typename T>
void print(std::ofstream& out, BinarySearchTree<T>& tree, std::string name)
{
    out << name << ": ";
    if (tree.empty())
        out << "is empty.\n";
    else
        out << tree << "\n";
    return;
}

int main()
{
    auto a = {4, 2, 3, 5, 1}; //a - std::initializer_list<int>
    BinarySearchTree<int> b(a);

    print(std::cout, b, "b");
    std::cout << b.size() << std::endl;
    b.find(5);
    b.find(8);

    b.insert(4);
    b.insert(10);
    std::cout << b.size() << std::endl;
    b.remove(125);
    std::cout << b.size() << std::endl;
}

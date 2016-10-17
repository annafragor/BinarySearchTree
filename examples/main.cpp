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
    auto list = {1, 2, 3, 4, 5};
    auto newList = {9, 8, 10, 6, 7, 5};
    BinarySearchTree<int> b(a);

    /*if(b.find(5))
        std::cout << "such value as 5 was found." << std::endl;
    if(b.find(8))
        std::cout << "such value as 8 was found." << std::endl; //such value as 8 wasn't found.
    */

    print(std::cout, b, "b");
    std::cout << b.size() << std::endl;
    b.find(5);
    b.find(8);

/*    if (b.insert(4))
        std::cout << "4 was inserted" << std::endl; //не выводит, тк элемент 4 уже есть
    if (b.insert(10))
        std::cout << "10 was inserted" << std::endl;
    print(std::cout, b, "b");*/
    b.insert(4);
    b.insert(10);
    std::cout << b.size() << std::endl;
    b.remove(125);
    std::cout << b.size() << std::endl;
/*    BinarySearchTree<int> bin;
    std::cout << "input bin: ";
    std::cin >> bin; //проверка потокового ввода

    print(std::cout, bin, "bin");

    std::ofstream fout("file.txt", std::ios::out); //открываем и очищаем файл
    if (!fout.is_open())
    { std::cout << "can't open the file" << std::endl; return 0; }
    print(fout, bin, "bin");

    BinarySearchTree<int> bout;
    std::ifstream fin("file2.txt", std::ios::in);
    fin.seekg(0, std::ios::beg);
    fin >> bout; //прoверка файлового ввода
    std::cout << "read from file2: "; // bout; //просмотр того, что считалось из файла
    print(std::cout, bout, "bout");

    BinarySearchTree<int> b1(list);
    print(std::cout, b1, "b1 before moving");
    BinarySearchTree<int> b2(std::move(b1)); //конструктор перемещения
    print(std::cout, b2, "b2 after move c-tor");
    print(std::cout, b1, "b1 after moving");

    BinarySearchTree<int> bst(newList);
    print(std::cout, bst, "bst");
    b2 = std::move(bst); //move operator=
    print(std::cout, bst, "bst after moving to b2 by move=");
    print(std::cout, b2, "b2");

    BinarySearchTree<int> c(newList);
    print(std::cout, c, "c");
    BinarySearchTree<int> newC(a);
    print(std::cout, newC, "newC");
    BinarySearchTree<int> newnewC(newC);
    print(std::cout, newnewC, "newnewC (after move c-tor)");

    newC = c;
    print(std::cout, newC, "newC (after copy= of c)");

    if (newC == newnewC)
        std::cout << "newC == newnewC" << std::endl;
    else
        std::cout << "newC != newnewC" << std::endl; // OK
    if (newC == c)
        std::cout << "newC == c" << std::endl; // OK
    else
        std::cout << "newC != c" << std::endl;

    auto forRemove = {20, 10, 26, 24, 27, 22, 21, 23, 25};
    BinarySearchTree<int> forR(forRemove);
    print(std::cout, forR, "forR");
    forR.remove(20);
    print(std::cout, forR, "forR after remove(20)");
    if (!forR.remove(12))
        std::cout << "12 doesn't exist in forR" << std::endl;
*/
}

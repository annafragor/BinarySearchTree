#include <iostream>
#include <cstring> //для size_t
#include <fstream>
#include "../include/BinarySearchTree.h"

int main() {
    auto a = {4, 2, 3, 5, 1}; //a - std::initializer_list<int>]
    BinarySearchTree<int> b(a);

    if(b.find(5))
        std::cout << "such value as 5 was found." << std::endl;
    if(b.find(8))
        std::cout << "such value as 8 was found." << std::endl; //such value as 8 wasn't found.

    std::cout << b << std::endl;

    if (b.insert(4))
        std::cout << "4 was inserted" << std::endl; //не выводит, тк элемент 4 уже есть
    if (b.insert(10))
        std::cout << "10 was inserted" << std::endl;

    std::cout << b << std::endl;

    BinarySearchTree<int> bin;
    std::cin >> bin; //проверка потокового ввода

    std::fstream f("D://!BMSTU//Programming//3semester//BinarySearchTree//examples//file.txt", std::ios::out); //открываем и очищаем файл
    if (!f.is_open())
    { std::cout << "can't open the file" << std::endl; return 0; }
    if (bin.empty())
        f << "tree is empty.";
    else
        f << bin; //прoверка файлового вывода

    BinarySearchTree<int> bout;
    f.close();
    f.open("D://!BMSTU//Programming//3semester//BinarySearchTree//examples//file2.txt", std::ios::in);
    f.seekg(0, std::ios::beg);
    f >> bout; //прoверка файлового ввода
    std::cout << "read from file:" << std::endl; // bout; //просмотр того, что считалось из файла
    if (bout.empty())
        std::cout << "tree is empty.";
    else
        std::cout << bout;


    auto list1 = {1, 2, 3, 4, 5};
    BinarySearchTree<int> b1(list1);
    BinarySearchTree<int> b2(std::move(b1)); //конструктор перемещения
    std::cout << std::endl << "b2:" << std::endl;
    std::cout << b2;
    std::cout << std::endl << "b1:" << std::endl;
    if (b1.empty())
        std::cout << "b1 is empty." << std::endl;
    else
        std::cout << b1 << std::endl;

    return 0;
}

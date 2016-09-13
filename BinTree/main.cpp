#include <iostream>
#include <cstring> //для size_t
#include <fstream>

template <typename T>
class BinarySearchTree {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;
        friend class BinarySearchTree;

        Node(T value_) : value(value_), left(nullptr), right(nullptr) {}

        friend std::ostream& operator << (std::ostream& out, const Node* node)
        {
            out << node->value;
            if (node->left)
                out << "\nleft from " << node->value << ": " << node->left;
            if (node->right)
                out << "\nright from " << node->value << ": " << node->right;
            return out;
        }

        ~Node() {
            if (this->left)
                delete this->left;
            if (this->right)
                delete this->right;
        }
    };

    BinarySearchTree() : root(nullptr), size_(0) {}
    BinarySearchTree(const std::initializer_list<T>& list) : size_(list.size()), root(nullptr) {
        for (auto it = list.begin(); it != list.end(); ++it)
            insert(*it);
    }

    auto size() const noexcept -> size_t { return size_; }

    bool empty() const{
        if (size())
            return false;
        else
            return true;
    }

    auto insert(const T& value) noexcept -> bool {
        bool foundPlace = false;
        if (find(value))
            return foundPlace;
        if (root == nullptr) {
            root = new Node(value);
            return true;
        }
        Node* thisNode = root;
        while (!foundPlace)
        {
            if (value < thisNode->value) {
                if (!thisNode->left) {
                    thisNode->left = new Node(value);
                    foundPlace = true;
                } else
                    thisNode = thisNode->left;
            } else if (!thisNode->right) {
                thisNode->right = new Node(value);
                foundPlace = true;
            } else
                thisNode = thisNode->right;
        }
        size_++;
        return foundPlace;
    }

    auto find(const T& value) const noexcept -> const T* {
        if (!root)
            return nullptr;
        Node* thisNode = root;
        while(1)
        {
            if (value == thisNode->value) {
                return &thisNode->value;
            }
            else if (value < thisNode->value)
                if (thisNode->left)
                    thisNode = thisNode->left;
                else {
                    return nullptr;
                }
            else {
                if (thisNode->right)
                    thisNode = thisNode->right;
                else
                    return nullptr;
            }
        }
    }

    friend std::ostream& operator << (std::ostream& out, const BinarySearchTree<T>& tree){ /*вывод*/
        if (tree.root)
            out << "root: " << tree.root;
        return out;
    }

    friend std::istream& operator >> (std::istream& in, BinarySearchTree<T>& tree) { /*ввод*/
        int n = 1;
        in >> n; //cчитываем количество элементов
        for (int i = 0; i < n; i++)
        {
            T value;
            in >> value;
            tree.insert(value);
        }
        return in;
    }

    ~BinarySearchTree() { delete root; }

private:
    size_t size_;
    Node* root;
};

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

    std::fstream f("D://!BMSTU//Programming//3semester//BinTree//file.txt", std::ios::out); //открываем и очищаем файл
    if (!f.is_open())
    { std::cout << "can't open the file" << std::endl; return 0; }
    if (bin.empty())
        f << "tree is empty.";
    else
        f << bin; //прoверка файлового вывода

    BinarySearchTree<int> bout;
    f.close();
    f.open("D://!BMSTU//Programming//3semester//BinTree//file2.txt", std::ios::in);
    f.seekg(0, std::ios::beg);
    f >> bout; //прoверка файлового ввода
    std::cout << "read from file: "; // bout; //просмотр того, что считалось из файла
    if (bout.empty())
        std::cout << "tree is empty.";
    else
        std::cout << bout;
    return 0;
}

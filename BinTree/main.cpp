#include <iostream>
//для size_t
#include <cstring>
#include <fstream>

template <typename T>
class BinarySearchTree /*упорядоченное дерево*/ {
public:
    struct Node {
        Node* left;
        Node* right;
        T value;

        friend class BinarySearchTree;

        Node(T value_) : value(value_), left(nullptr), right(nullptr) {}

        friend std::ostream& operator << (std::ostream& out, const Node* node)
        {
            out << node->value; out << " ";
            if (node->left) {
                out << node->left;
            }
            if (node->right) {
                out << node->right;
            }
            return out;
        }
    };

    BinarySearchTree() : root(nullptr), size_(0) {}
    BinarySearchTree(const std::initializer_list<T>& list) : size_(list.size()), root(nullptr) {
        Node* thisNode = nullptr;
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            if (it == list.begin())
                root = new Node(*it);
            else
                insert(*it);
        }
    }

    auto size() const noexcept -> size_t { return size_; }

    auto insert(const T& value) noexcept -> bool {
        bool foundPlace = false;
        Node* thisNode = root;
        if (thisNode == nullptr) {
            root = new Node(value);
            return true;
        }
        while (!foundPlace)
        {
            if (value <= thisNode->value) {
                if (!thisNode->left) {
                    thisNode->left = new Node(value);
                    foundPlace = true;
                }else
                    thisNode = thisNode->left;
            } else
            if (!thisNode->right) {
                thisNode->right = new Node(value);
                foundPlace = true;
            }else
                thisNode = thisNode->right;
        }
        size_++;
        return foundPlace;
    }

    auto find(const T& value) const noexcept -> const Node* {
        Node* thisNode = root;
        while(1)
        {
            if (value == thisNode->value) {
                std::cout << "such value as " << value << " was found." << std::endl;
                return thisNode;
            }
            else if (value < thisNode->value)
                if (thisNode->left)
                    thisNode = thisNode->left;
                else {
                    std::cout << "such value as " << value << " wasn't found." << std::endl;
                    return nullptr;
                }
            else {
                if (thisNode->right)
                    thisNode = thisNode->right;
                else {
                    std::cout << "such value as " << value << " wasn't found." << std::endl;
                    return nullptr;
                }
            }
        }
    }

    friend std::ostream& operator << (std::ostream& out, const BinarySearchTree<T>& tree){ /*вывод*/
        if (tree.root)
            out << tree.root;
        else
            std::cout << "tree is empty\n";
        return out;
    }

    friend std::istream& operator >> (std::istream& in, BinarySearchTree<T>& tree) { /*ввод*/
        int n;
        in >> n; /*cчитываем количество элементов дерева*/
        std::cout << n << std::endl;
        for (int i = 0; i < n; i++)
        {
            T value;
            in >> value;
            tree.insert(value);
        }
        return in;
    }

    ~BinarySearchTree() {}
private:
    size_t size_;
    Node* root;
};

void clearFile(const char* filename)
{
    std::fstream clear_file(filename, std::ios::out);
    clear_file.close();
    return;
}

int main() { /*проверка работы функций и методов*/
    auto a = {4, 2, 3, 5, 1}; //a - std::initializer_list<int>
    BinarySearchTree<int> b(a);

    b.find(5);                          //such value as 5 was found.
    b.find(8);                          //such value as 8 wasn't found.
    std::cout << b << std::endl;        //4 2 1 3 5
    b.insert(10);
    std::cout << b << std::endl;        //4 2 1 3 5 10

    BinarySearchTree<int> bin;
    std::cin >> bin;                    //проверка потокового ввода

    clearFile("D://!BMSTU//Programming//3semester//BinTree//file.txt");
    std::fstream f;
    f.open("D://!BMSTU//Programming//3semester//BinTree//file.txt");
    if (!f.is_open())
    { std::cout << "can't open the file"; return 0; }
    f << bin;                           //прoверка файлового вывода

    BinarySearchTree<int> bout;
    std::cout << "in from file ";
    f.seekg(0, std::ios::beg);
    f >> bout;                          //прoверка файлового ввода
    f.close();
    return 0;
}

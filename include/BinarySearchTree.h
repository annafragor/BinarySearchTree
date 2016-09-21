//
// Created by ANNA on 17.09.2016.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <iostream>
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

        friend auto operator << (std::ofstream& out, const Node* node) -> std::ofstream&{
            out << node->value << " ";
            if (node->left)
                out << node->left;
            if (node->right)
                out << node->right;
            return out;
        }

        friend auto operator << (std::ostream& out, const Node* node) -> std::ostream& {
            if (node->right)
                out << node->right;
            out << node->value << " ";
            if (node->left)
                out << node->left;
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
    BinarySearchTree(const std::initializer_list<T>& list);
    BinarySearchTree(BinarySearchTree&& rhs);
    BinarySearchTree(const BinarySearchTree& tree);

    auto size() const noexcept -> size_t;
    bool empty() const;
    auto insert(const T& value) noexcept -> bool;
    auto find(const T& value) const noexcept -> const T*;

    friend auto operator << (std::ofstream& out, const BinarySearchTree<T>& tree) -> std::ofstream& { //прямой
        out << tree.root;
        return out;
    }
    friend auto operator << (std::ostream& out, const BinarySearchTree<T>& tree) -> std::ostream& { //симметричный
        out << tree.root;
        return out;
    }
    friend auto operator >> (std::istream& in, BinarySearchTree<T>& tree) -> std::istream& {
        size_t n;
        if (!(in >> n)){
            std::cerr << "wrong type of number of elements" << std::endl;
            return in;
        }
        //std::cout << "--" << n << "--\n";
        for (int i = 0; i < n; ++i)
        {
            T value;
            if(in >> value)
                tree.insert(value);
            else {
                std::cerr << "wrong input data" << std::endl;
                return in;
            }
        }
        return in;
    }

    //friend auto operator >> (std::ifstream& in, BinarySearchTree<T>& tree) -> std::ifstream&{}

    BinarySearchTree& operator = (BinarySearchTree&& rhs){
        if (this == &rhs)
            return *this;

        size_ = rhs.size_;
        rhs.size_ = 0;

        delete root;
        root = rhs.root;
        rhs.root = nullptr;
        return *this;
    }
    auto operator = (const BinarySearchTree& tree) -> BinarySearchTree&{

    }




    ~BinarySearchTree();

private:
    size_t size_;
    Node* root;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const std::initializer_list<T> &list) : size_(list.size()), root(nullptr) {
    for (auto it = list.begin(); it != list.end(); ++it)
        insert(*it);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree &&rhs) : size_(rhs.size_) {
    root = rhs.root;
    rhs.size_ = 0;
    rhs.root = nullptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &rhs) : size_(rhs.size_) {

}




template <typename T>
auto BinarySearchTree<T>::size() const noexcept -> size_t { return size_; }

template <typename T>
bool BinarySearchTree<T>::empty() const {
    if (size())
        return false;
    else
        return true;
}

template <typename T>
auto BinarySearchTree<T>::insert(const T &value) noexcept -> bool {
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

template <typename T>
auto BinarySearchTree<T>::find(const T &value) const noexcept -> const T * {
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

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() { delete root; }

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H

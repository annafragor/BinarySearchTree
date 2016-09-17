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
    BinarySearchTree(const std::initializer_list<T>& list);

    auto size() const noexcept -> size_t;
    bool empty() const;
    auto insert(const T& value) noexcept -> bool;
    auto find(const T& value) const noexcept -> const T*;

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

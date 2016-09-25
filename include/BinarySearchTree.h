//
// Created by ANNA on 17.09.2016.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <iostream>
#include <fstream>
#include <typeinfo>

template <typename T>
class BinarySearchTree
{
public:
    struct Node
    {
        Node* left;
        Node* right;
        T value;

        Node(T value_) : value(value_), left(nullptr), right(nullptr) {}

        auto _value() const noexcept -> T { return value; }

        auto copy(Node* rhs) -> Node*
        {
            if (value != rhs->value) // если данные узлы не равны
                value = rhs->value;  // делаем их равными

            if (!left && rhs->left) // если левой ветви нет, а должна быть, выделяем под левый узел память
                left = new Node(rhs->left->value); // и инициализируем нужным значением
            if (!right && rhs->right) // аналогично если правой ветки нет
                right = new Node(rhs->right->value);

            if (left && !rhs->left) { // если левая ветка есть, а ее быть не должно
                delete left;          // удаляем ее
                left = nullptr;
            }
            if (right && !rhs->right) { // аналогично если правая ветка есть, а ее быть не должно
                delete right;
                right = nullptr;
            }

            if (left)
                left = left->copy(rhs->left);
            if (right)
                right = right->copy(rhs->right);

            return this;
        }

        auto equal(Node* rhs) const noexcept -> bool
        {
            // если какая-либо ветка существует, а соответствующая в другом дереве - нет,
            // возвращаем false
            if ((left && !rhs->left) || (right && !rhs->right))
                return false;
            if ((!left && rhs->left) || (!right && rhs->right))
                return false;

            bool equalLeft = true; bool equalRight = true;
            if (value != rhs->value) // если данные узлы не равны, возвращаем false
                return false;
            else // если равны (и мы уже знаем, что left и right существуют попарно с rhs->left и rhs->right)
            {
                if (!left && !right /* && !rhs->left && !rhs->right*/)
                    return true;
                if (left)
                    equalLeft = left->equal(rhs->left);
                if (right)
                    equalRight = right->equal(rhs->right);
                return equalLeft && equalRight;
            }
        }

        friend auto operator << (std::ostream& out, const Node* node) -> std::ostream&
        {
            if (typeid(out).name() == typeid(std::cout).name()) {
                if (node->right)
                    out << node->right;
                out << node->value << " ";
                if (node->left)
                    out << node->left;
            } else {
                out << node->value << " ";
                if (node->left)
                    out << node->left;
                if (node->right)
                    out << node->right;
            }
            return out;
        }

        ~Node()
        {
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
    bool empty() const noexcept;
    auto insert(const T& value) noexcept -> bool;
    auto find(const T& value) const noexcept -> const T*;

    friend auto operator << (std::ostream& out, const BinarySearchTree<T>& tree) -> std::ostream&
    { //симметричный
        out << tree.root;
        return out;
    }
    friend auto operator >> (std::istream& in, BinarySearchTree<T>& tree) -> std::istream&
    {
        size_t n;
        if (!(in >> n)){
            std::cerr << "wrong type of number of elements" << std::endl;
            return in;
        }
        tree.size_ = n;
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

    auto operator = (BinarySearchTree&& rhs) -> BinarySearchTree&;
    auto operator = (const BinarySearchTree& rhs) -> BinarySearchTree&;
    auto operator == (const BinarySearchTree& rhs) -> bool;

    ~BinarySearchTree();

private:
    size_t size_;
    Node* root;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const std::initializer_list<T> &list) : size_(list.size()), root(nullptr)
{
    for (auto it = list.begin(); it != list.end(); ++it)
        insert(*it);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree &&rhs) : size_(rhs.size_), root(nullptr)
{
    root = rhs.root;
    rhs.size_ = 0;
    rhs.root = nullptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &rhs) : size_(rhs.size_), root(nullptr)
{
    root = new Node(0);
    root = root->copy(rhs.root);
}

template <typename T>
auto BinarySearchTree<T>::size() const noexcept -> size_t { return size_; }

template <typename T>
bool BinarySearchTree<T>::empty() const
{
    if (size())
        return false;
    else
        return true;
}

template <typename T>
auto BinarySearchTree<T>::insert(const T &value) noexcept -> bool
{
    bool foundPlace = false;
    if (root == nullptr) {
        root = new Node(value);
        return true;
    }
    Node* thisNode = root;
    while (!foundPlace)
    {
        if (value == thisNode->value)
            return false;
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
auto BinarySearchTree<T>::find(const T &value) const noexcept -> const T*
{
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
auto BinarySearchTree<T>::operator=(BinarySearchTree &&rhs) -> BinarySearchTree&
{
    if (this == &rhs)
        return *this;

    size_ = rhs.size_;
    rhs.size_ = 0;

    delete root;
    root = rhs.root;
    rhs.root = nullptr;
    return *this;
}

template <typename T>
auto BinarySearchTree<T>::operator=(const BinarySearchTree &rhs) -> BinarySearchTree&
{
    if (this == &rhs)
        return *this;

    size_ = rhs.size_;
    root = root->copy(rhs.root);
    return *this;
}

template <typename T>
auto BinarySearchTree<T>::operator==(const BinarySearchTree &rhs) -> bool
{
    if (root->equal(rhs.root))
        return true;
    else
        return false;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() { delete root; }

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H

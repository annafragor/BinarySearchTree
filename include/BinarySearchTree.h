//
// Created by ANNA on 17.09.2016.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <iostream>
#include <fstream>
#include <memory>
#include <exception>

template <typename T>
class BinarySearchTree
{
public:
    class bad_argument : public std::logic_error
    {
    public:
        bad_argument(const std::string& data = "") : logic_error(data) {}
    };

    struct Node
    {
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        T value;

        Node(T value_) : value(value_), left(nullptr), right(nullptr) {}

        auto _value() const noexcept -> T { return value; }

        auto symmetric(std::ostream& out, std::string lvl) const noexcept -> std::ostream&
        {
            if (right)
                right->symmetric(out, lvl + '-');
            out << lvl << value << "\n";
            if (left)
                left->symmetric(out, lvl + '-');
            return out;
        }

        auto direct(std::ofstream& out, std::string lvl) const noexcept -> std::ofstream&
        {
            out << lvl << value << "\n";
            if (left)
                left->direct(out, lvl + '-');
            if (right)
                right->direct(out, lvl + '-');
            return out;
        }

        auto equal(std::shared_ptr<Node> rhs) const noexcept -> bool
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

        static auto remove(const T& value_, std::shared_ptr<Node>& thisNode) ->  bool
        {
            if (!thisNode)
                return false;

            if (value_ < thisNode->value)
                remove(value_, thisNode->left);
            if (value_ > thisNode->value)
                remove(value_, thisNode->right);
            if (value_ == thisNode->value) // если нашли нужный элемент
            {
                if (!thisNode->left && !thisNode->right) // если это последний лист
                {
                    thisNode = nullptr;  // удаляем его
                    return true;
                } else if (thisNode->left && !thisNode->right) // если есть путь налево, но нет направо
                {
                    thisNode = thisNode->left;
                    return true;
                } else if (!thisNode->left && thisNode->right) // если есть путь направо, но нет налево
                {
                    thisNode = thisNode->right;
                    return true;
                } else // если оба пути существуют
                {
                    std::shared_ptr<Node> newRight = thisNode->right;
                    thisNode = thisNode->left;
                    std::shared_ptr<Node> newThisNode = thisNode;
                    while (newThisNode->right)
                        newThisNode = newThisNode->right;
                    newThisNode->right = newRight;
                    return true;
                }
            }
        }

        static auto copy(std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs) -> std::shared_ptr<Node>
        {
            if (lhs->value != rhs->value) // если данные узлы не равны
                lhs->value = rhs->value;  // делаем их равными

            if (!lhs->left && rhs->left) // если левой ветви нет, а должна быть, выделяем под левый узел память
                lhs->left = std::make_shared<Node>(rhs->left->value); // и инициализируем нужным значением
            if (!lhs->right && rhs->right) // аналогично если правой ветки нет
                lhs->right = std::make_shared<Node>(rhs->right->value);

            if (lhs->left && !rhs->left) // если левая ветка есть, а ее быть не должно
                lhs->left = nullptr;
            if (lhs->right && !rhs->right) // аналогично если правая ветка есть, а ее быть не должно
                lhs->right = nullptr;

            if (lhs->left)
                lhs->left = copy(lhs->left, rhs->left);
            if (lhs->right)
                lhs->right = copy(lhs->right, rhs->right);

            return lhs;
        }

        ~Node()
        {
            left = nullptr;
            right = nullptr;
        }
    };

    BinarySearchTree() : root(nullptr), size_(0) {}
    BinarySearchTree(const std::initializer_list<T>& list);
    BinarySearchTree(BinarySearchTree&& rhs);
    BinarySearchTree(const BinarySearchTree& tree);

    auto size() const noexcept -> size_t;
    bool empty() const noexcept;
    auto insert(const T& value) -> bool;
    auto find(const T& value) const -> const T*;
    auto remove(const T& value) -> bool;

    friend auto operator << (std::ofstream& out, const BinarySearchTree<T>& tree) -> std::ofstream&
    {
        tree.root->direct(out, "");
        return out;
    }
    friend auto operator << (std::ostream& out, const BinarySearchTree<T>& tree) -> std::ostream&
    {
        tree.root->symmetric(out, "");
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
    std::shared_ptr<Node> root;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const std::initializer_list<T> &list) : size_(list.size()), root(nullptr)
{
    for (auto it = list.begin(); it != list.end(); ++it)
        insert(*it);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree &&rhs) : size_(rhs.size_), root(rhs.root)
{
    rhs.size_ = 0;
    rhs.root = nullptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &rhs) : size_(rhs.size_), root(std::make_shared<Node>(0))
{
    root = Node::copy(root, rhs.root);
}

template <typename T>
auto BinarySearchTree<T>::size() const noexcept -> size_t { return size_; }

template <typename T>
auto BinarySearchTree<T>::empty() const noexcept -> bool
{
    if (size())
        return false;
    else
        return true;
}

template <typename T>
auto BinarySearchTree<T>::insert(const T& value) -> bool try
{
    bool foundPlace = false;
    if (root == nullptr)
    {
        root = std::make_shared<Node>(value);
        return true;
    }
    std::shared_ptr<Node> thisNode = root;
    while (!foundPlace)
    {
        if (value == thisNode->value)
	        throw BinarySearchTree<T>::bad_argument("such element already exists.");
        if (value < thisNode->value)
        {
            if (!thisNode->left)
            {
                thisNode->left = std::make_shared<Node>(value);
                foundPlace = true;
            } else
                thisNode = thisNode->left;
        } else if (!thisNode->right)
        {
            thisNode->right = std::make_shared<Node>(value);
            foundPlace = true;
        } else
            thisNode = thisNode->right;
    }
    size_++;
    return foundPlace;
}
catch(BinarySearchTree<T>::bad_argument& err)
{
	std::cerr << "BinarySearchTree::insert(" << value <<  ") threw an exception" << std::endl;
	std::cerr << err.what() << std::endl;
	return false;
}

template <typename T>
auto BinarySearchTree<T>::find(const T& value) const -> const T* try
{
    if (!root)
	    throw BinarySearchTree<T>::bad_argument("your tree is empty.");
    std::shared_ptr<Node> thisNode = root;
    while(1)
    {
        if (value == thisNode->value)
            return &thisNode->value;
        else if (value < thisNode->value)
	    {
            if (thisNode->left)
                thisNode = thisNode->left;
            else
		        throw bad_argument("such element wasn't found.");
	    } else
        {
            if (thisNode->right)
                thisNode = thisNode->right;
            else
                throw bad_argument("such element wasn't found.");
        }
    }
}
catch(BinarySearchTree<T>::bad_argument& err)
{
	std::cerr << "BinarySearchTree::find(" << value << ") threw an exception" << std::endl;
    std::cerr << err.what() << std::endl;
	return nullptr;
}

template <typename T>
auto BinarySearchTree<T>::remove(const T& value) -> bool try
{
    bool foundValue = false;
    if (root)
        foundValue = Node::remove(value, root);
    else
        throw BinarySearchTree<T>::bad_argument("your tree is empty");
    if (foundValue)
    {
        size_--;
        return true;
    } else
        throw BinarySearchTree<T>::bad_argument("such element wasn't found");
}
catch(BinarySearchTree<T>::bad_argument& err)
{
    std::cerr << "BinarySearchTree::remove(" << value <<  ") threw an exception" << std::endl;
    std::cerr << err.what() << std::endl;
    return false;
}

template <typename T>
auto BinarySearchTree<T>::operator=(BinarySearchTree &&rhs) -> BinarySearchTree&
{
    if (this == &rhs)
        return *this;

    size_ = rhs.size_;
    rhs.size_ = 0;

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
    std::cerr << "ok\n";
    root = Node::copy(root, rhs.root);
    std::cerr << "ok2\n";
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
BinarySearchTree<T>::~BinarySearchTree()
{
    root = nullptr;
    size_ = 0;
}

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include "../include/BinarySearchTree.h"
#include "catch.hpp"

SCENARIO("if element already exists => return false")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{1, 3, 5, 7};
        WHEN("insert element")
        {
            THEN("elements can't be repeated")
            {
                REQURE(!tree.insert(1));
            }
        }   
    }    
}
SCENARIO("if element don't exists => return true")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{1, 3, 5, 7};
        WHEN("insert element")
        {
            THEN("element was inserted")
            {
                REQUIRE(tree.insert(10));
            }
        }   
    }    
}
SCENARIO("if inserting element < root->value, add it to the left side of root")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{3, 5};
        WHEN("insert element")
        {
            tree.insert(1);
            THEN("element must be in the root->left")
            {
                REQUIRE(tree->root->left->value == 1);
            }
        }
    }   
}
SCENARIO("if inserting element > root->value, add it to the right side of root")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{3, 1};
        WHEN("insert element")
        {
            tree.insert(5);
            THEN("element must be in the root->right")
            {
               REQUIRE(tree->root->right->value == 5);
            }
        }
    }   
}
SCENARIO("if element already exists, size must stay constant")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{1, 3, 5, 7};
        size_t size = tree.size();
        WHEN("insert element")
        {
            tree.insert(7);
            THEN("size hasn't changed")
            {
                REQUIRE(tree.size() == size);
            }
        }
    }
}
SCENARIO("if element doesn't exist, size must increase")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{1, 3, 5, 7};
        size_t size = tree.size();
        WHEN("insert element")
        {
            tree.insert(8);
            THEN("newSize == sizeBeforeInserting + 1")
            {
                REQUIRE(tree.size() == size + 1);
            }
        }
    }
}

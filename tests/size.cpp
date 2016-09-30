//
// Created by pca18 on 30.09.16.
//

#include "../include/BinarySearchTree.h"
#include "catch.h"

SCENARIO( "size of empty tree must be equal to 0")
{
    GIVEN("empty tree")
    {
        BinarySearchTree<int> tree;
        WHEN("decide size")
        {
            THEN("size must be equal to 0")
            {
                REQUIRE(tree.size() == 0);
            }
        }
    }
}
SCENARIO("size of non-empty tree mustn't be equal to 0")
{
    GIVEN("not empty tree")
    {
        BinarySearchTree<int> tree{2, 6, 4};
        WHEN("decide size")
        {
            THEN("size must be not equal to 0")
            {
                REQUIRE(tree.size() != 0);
            }
        }
    }
}
SCENARIO("size of constant tree must be equal to size of non-constant tree")
{
    GIVEN("2 trees: constant and non-constant")
    {
        BinarySearchTree<int> tree1{1, 3, 7};
        const BinarySearchTree<int> tree2{2, 6, 4};
        WHEN("compare sizes")
        {
            THEN("sizes must be equal")
            {
                REQUIRE(tree1.size() == tree2.size());
            }
        }
    }
}

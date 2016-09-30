#include "../include/BinarySearchTree.h"
#include "catch.hpp"

SCENARIO("if element doesn't exist in the tree, return nullptr")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{1, 2, 3, 4};
        WHEN("looking for element, that doesn't exist")
        {
            THEN("return nullptr")
            {
                REQUIRE(tree.find(10) == nullptr);
            }
        }
    }
}
SCENARIO("if element already exists in the tree, return pointer to this element")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{1, 2, 3, 4};
        WHEN("looking for element, that already exists")
        {
            THEN("return pointer to this element")
            {
                REQUIRE(*(tree.find(2)) == 2);
            }
        }
    }
}
SCENARIO("this method must work for constant tree and for non-constant tree")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree1{1, 2, 3};
        const BinarySearchTree<int> tree2{3, 4, 5};
        WHEN("looking for element in these trees")
        {
            THEN("method find works both for constant and non-constant tree")
            {
                bool f1 = false; bool f2 = false;
                if (tree1.find(2))
                    f1 = true;
                if (tree2.find(5))
                    f2 = true;
                f1 &= f2;
                REQUIRE(f1);
            }
        }
    }
}

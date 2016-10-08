#include "../include/BinarySearchTree.h"
#include "catch.hpp"

SCENARIO("if we want to delete an element, that doesn't exist - return false")
{
	GIVEN("some tree")
	{
		BinarySearchTree<int> tree{1, 2, 3};
		WHEN("remove element")
		{
			THEN("such element doesn't exist in the tree")
			{
				REQUIRE(!tree.remove(5));
			}
		}
	}
}
SCENARIO("remove element that has nothing on the left side AND nothing on the right side")
{
	GIVEN("some tree")
	{
		BinarySearchTree<int> tree{4, 2, 1, 3, 5};
		BinarySearchTree<int> tree2{4, 2, 1, 3};
		WHEN("remove element")
		{
			tree.remove(5);
			THEN("element was removed")
			{
				REQUIRE(tree2 == tree);
			}			
		}
	}
}
SCENARIO("remove element that has something on the left side AND nothing on the right side")
{
	GIVEN("some tree")
	{
		BinarySearchTree<int> tree{20, 10, 26, 9, 24, 27, 22, 23, 25, 21, 28};
		BinarySearchTree<int> tree2{20, 9, 26, 24, 27, 22, 23, 25, 21, 28};
		WHEN("remove element")
		{
			tree.remove(10);
			THEN("element was removed")
			{
				REQUIRE(tree2 == tree);
			}			
		}
	}
}
SCENARIO("remove element that has nothing on the left side AND something on the right side")
{
	GIVEN("some tree")
	{
		BinarySearchTree<int> tree{20, 10, 9, 26, 24, 27, 22, 23, 25, 21, 28};
		BinarySearchTree<int> tree2{20, 10, 9, 26, 24, 22, 23, 25, 21, 28};
		WHEN("remove element")
		{
			tree.remove(27);
			THEN("element was removed")
			{
				REQUIRE(tree2 == tree);
			}			
		}
	}
}
SCENARIO("remove element that has something on the left side AND something on the right side")
{
	GIVEN("some tree")
	{
		BinarySearchTree<int> tree{20, 10, 9, 26, 24, 27, 22, 23, 25, 21, 28};
		BinarySearchTree<int> tree2{20, 10, 9, 26, 27, 22, 23, 25, 21, 28};
		WHEN("remove element")
		{
			tree.remove(24);
			THEN("element was removed")
			{
				REQUIRE(tree2 == tree);
			}			
		}
	}
}
SCENARIO("remove root")
{
	GIVEN("some tree")
	{
		BinarySearchTree<int> tree{4, 2, 1, 3, 5};
		BinarySearchTree<int> tree2{2, 1, 3, 5};
		WHEN("remove root")
		{
			tree.remove(4);
			THEN("element was removed")
			{
				REQUIRE(tree2 == tree);
			}			
		}
	}
}
#pragma once

#include "Akinator.hpp"

#define AKINATOR_DATA_ "data/"

#define AKINATOR_BASE_ AKINATOR_DATA_ "base.txt"

#define AKINATOR_READ_BASE(tree) {				 \
	tree_status = AkinatorReadBase(tree);		\
	TREE_ERROR_CHECK(tree_status);				\
}

#define AKINATOR_SAVE_TREE(tree) { 				 \
	tree_status = SaveTreeToBase(tree);			\
	TREE_ERROR_CHECK(tree_status);				\
}

enum NodeStatus {
	NODE_STATUS_UNKNOWN,
	NODE_STATUS_LEAF,
	NODE_STATUS_LOCAL_ROOT,
};

BinaryTreeStatusCode AkinatorReadBase(Tree* tree);
BinaryTreeStatusCode AkinatorRunGame(Tree* tree);
BinaryTreeStatusCode SaveTreeToBase(Tree* tree);

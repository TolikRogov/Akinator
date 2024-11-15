#pragma once

#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include "Akinator_errors.hpp"
#include "STACK_LIBRARY.hpp"

typedef char* Data_t;

#define INIT_TREE(tree) Tree tree = {.info = {.name = #tree, .file_name = __FILE__, .line = __LINE__}};

#define BINARY_TREE_GRAPH_DUMP(tree, func_name, point) {	 																\
	tree_status = BinaryTreeGraphDump(tree, {.file = __FILE__, .line = __LINE__, .func = func_name, .pointer = point});		\
	TREE_ERROR_CHECK(tree_status);																	 					   \
}

#define TREE_HTML_DUMP_START() {				 \
	tree_status = BinaryTreeHtmlDumpStart();	\
	TREE_ERROR_CHECK(tree_status);				\
}

#define TREE_HTML_DUMP_FINISH() {				 \
	tree_status = BinaryTreeHtmlDumpFinish();	\
	TREE_ERROR_CHECK(tree_status);				\
}

#define TREE_CTOR(tree) {						 		 \
	tree_status = TreeCtor(tree);						\
	TREE_ERROR_CHECK(tree_status);						\
	BINARY_TREE_GRAPH_DUMP(tree, "TreeCtor", NULL);		\
}

#define TREE_DTOR(root) {						 		 \
	BINARY_TREE_GRAPH_DUMP(&tree, "TreeDtor", NULL); 	\
	TREE_HTML_DUMP_FINISH();							\
	tree_status = TreeDtor(root);						\
	TREE_ERROR_CHECK(tree_status);						\
}

struct Node_t {
	Data_t data;
	Node_t* left;
	Node_t* right;
	Node_t* parent;
};

struct TreeLogInfo {
	const char* name;
	const char* file_name;
	const size_t line;
};

struct Tree {
	Node_t* root;
	TreeLogInfo info;
};

enum TreeDumpCheck {
	TREE_FIRST_RUN,
	TREE_SECOND_RUN,
	TREE_ALREADY_ON,
};

const Data_t UNKNOWN_WHAT = "UNKNOWN WHAT";
const Data_t NONE 		  = "NONE";
const size_t NODE_DATA_MAX_LENGTH = 50;

BinaryTreeStatusCode TreeCtor(Tree* tree);
BinaryTreeStatusCode TreeDtor(Node_t* node);

BinaryTreeStatusCode BinaryTreeHtmlDumpStart();
BinaryTreeStatusCode BinaryTreeHtmlDumpFinish();

Node_t* CreateNode(Data_t data, Node_t* left, Node_t* right, Node_t* parent);
Node_t* FindTreeRoot(Node_t* node);
Node_t* FindNodeInTree(Node_t* node, Data_t data);

size_t NodeDepthInTree(Node_t* node, Stack_t* stk);

BinaryTreeStatusCode AkinatorDefinitionMode(Tree* tree);
BinaryTreeStatusCode AkinatorGuessingMode(Tree* tree);
BinaryTreeStatusCode AkinatorAskAboutNode(Node_t* node);
BinaryTreeStatusCode PrintPathToNode(Node_t* node);
BinaryTreeStatusCode IsRootUnknownWhat(Node_t* root);

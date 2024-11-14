#include "Akinator.hpp"

char TREE_DUMP = TREE_FIRST_RUN;

BinaryTreeStatusCode TreeCtor(Tree* tree) {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	tree->root = CreateNode(UNKNOWN_WHAT, NULL, NULL, NULL);

	if (TREE_DUMP == TREE_ALREADY_ON)
		return TREE_NO_ERROR;

	TREE_HTML_DUMP_START();
	TREE_DUMP = TREE_ALREADY_ON;

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode TreeDtor(Node_t* node) {

	if (node->left)  TreeDtor(node->left);
	if (node->right) TreeDtor(node->right);

	if (node) {
		free(node);
		node = NULL;
	}

	return TREE_NO_ERROR;
}

Node_t* CreateNode(Data_t data, Node_t* left, Node_t* right, Node_t* parent) {

	Node_t* node = (Node_t*)calloc(1, sizeof(*node));

	int data_size = StrLen(data);
	printf("Create node: %s(%d)\n", data, *data);
	node->data = (Data_t)calloc((size_t)data_size + 1, sizeof(char));
	for (int i = 0; i < data_size; i++) node->data[i] = data[i];
	node->data[data_size] = '\0';

	if (left)   { node->left = left;   left->parent = node;  }
	if (right)  { node->right = right; right->parent = node; }
	if (parent) { node->parent = parent; }

	return node;
}

BinaryTreeStatusCode IsRootUnknownWhat(Node_t* root) {

	if (root->left == NULL && \
		root->right == NULL && \
		StrCmp(root->data, UNKNOWN_WHAT) == 0)
		return TREE_ROOT_IS_UNKNOWN;

	return TREE_NO_ERROR;
}

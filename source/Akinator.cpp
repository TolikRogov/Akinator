#include "Akinator.hpp"

char TREE_DUMP = TREE_FIRST_RUN;

BinaryTreeStatusCode AkinatorComparingMode(Tree* tree) {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	PathArray path1 = {};
	tree_status = CreatePathToNode(tree, &path1);
	TREE_ERROR_CHECK(tree_status);

	PathArray path2 = {};
	tree_status = CreatePathToNode(tree, &path2);
	TREE_ERROR_CHECK(tree_status);

	if (path1.searched_node == path2.searched_node) {
		printf(GREEN("The similar!\n"));
		return TREE_NO_ERROR;
	}

	size_t size = (path1.size < path2.size ? path1.size : path2.size);

	printf(TEAL("\"%s\" and \"%s\":\n"), path1.searched_node->data, path2.searched_node->data);
	printf("\t" GREEN("They both: "));
	size_t i = 1;
	for (; i < size; i++) {
		if (path1.array[i] != path2.array[i])
			break;
		printf("- ");
		if (path1.array[i - 1]->right == path1.array[i])
			printf("not ");
		printf("%s ", path1.array[i - 1]->data);
	}
	printf("\n");

	printf("\t" RED("But \"%s\":")" ", path1.searched_node->data);
	for (size_t j = i - 1; j < path1.size; j++) {
		printf("- ");
		if (path1.array[j]->right == path1.array[j + 1])
			printf("not ");
		printf("%s ", path1.array[j]->data);
	}
	printf("\n");

	printf("\t" RED("And \"%s\":")" ", path2.searched_node->data);
	for (size_t j = i - 1; j < path2.size; j++) {
		printf("- ");
		if (path2.array[j]->right == path2.array[j + 1])
			printf("not ");
		printf("%s ", path2.array[j]->data);
	}

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode AkinatorDefinitionMode(Tree* tree) {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	PathArray path = {};
	tree_status = CreatePathToNode(tree, &path);
	TREE_ERROR_CHECK(tree_status);

	printf(GREEN("Definition of \"%s\":")" ", path.searched_node->data);

	for (size_t i = 0; i < path.size; i++) {
		printf("- ");
		if (path.array[i]->right == path.array[i + 1])
			printf("not ");
		printf("%s ", path.array[i]->data);
	}
	printf("\n");

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode CreatePathToNode(Tree* tree, PathArray* path) {

	char data[NODE_DATA_MAX_LENGTH] = {};
	printf(YELLOW("Enter object name:")" ");
	scanf("%s", data);

#ifdef PRINT_DEBUG
	printf("data: %s\n", data);
#endif

	path->searched_node = FindNodeInTree(tree->root, data);

	if (!path->searched_node)
		return TREE_NODE_NON_EXISTENT;

#ifdef PRINT_DEBUG
	printf(GREEN("I found it:") " %p\n", path->searched_node);
#endif

	path->array = (Node_t**)calloc(NodeDepthInTree(path->searched_node) + 1, sizeof(Node_t*));
	if (!path->array)
		return TREE_ALLOC_ERROR;

	FindPathToNode(path->searched_node, path);
	path->array[path->size] = path->searched_node;

	return TREE_NO_ERROR;
}

size_t NodeDepthInTree(Node_t* node) {

	if (!node->parent)
		return 0;

	return NodeDepthInTree(node->parent) + 1;
}

BinaryTreeStatusCode FindPathToNode(Node_t* node, PathArray* path) {

	if (!node->parent)
		return TREE_NO_ERROR;

	FindPathToNode(node->parent, path);

	path->array[path->size++] = node->parent;

#ifdef PRINT_DEBUG
	printf("node parent: %s\n", path->array[path->size-1]->data);
#endif

	return TREE_NO_ERROR;
}

Node_t* FindNodeInTree(Node_t* node, Data_t data) {

	Node_t* desired_node = NULL;

#define NEIGHBOUR(unit) if (unit && (desired_node = FindNodeInTree(unit, data))) return desired_node;

	NEIGHBOUR(node->left);
	NEIGHBOUR(node->right);

#undef NEIGHBOUR

	if (StrCmp(node->data, data) == 0)
		return node;

	return NULL;
}

BinaryTreeStatusCode AkinatorGuessingMode(Tree* tree) {

	AkinatorAskAboutNode(tree->root);

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode AkinatorAskAboutNode(Node_t* node) {

	if (!node) {
		printf(RED("Sorry, I dont know what you made!")"\n");
		return TREE_NO_ERROR;
	}

	printf(TEAL("This %s?") " [y/n]\n", node->data);
	int c = getchar();
	if (c != '\n') getchar();
	if (c == 'y') {
		if (!node->left) {
			printf(GREEN("I always know!") "\n");
			return TREE_NO_ERROR;
		}
		AkinatorAskAboutNode(node->left);
	}
	else if (c == 'n')
		AkinatorAskAboutNode(node->right);
	else
		AkinatorAskAboutNode(node);

	return TREE_NO_ERROR;
}

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
		if (node->data) {
			free(node->data);
			node->data = NULL;
		}

		free(node);
		node = NULL;
	}

	return TREE_NO_ERROR;
}

Node_t* CreateNode(Data_t data, Node_t* left, Node_t* right, Node_t* parent) {

	Node_t* node = (Node_t*)calloc(1, sizeof(*node));

	int data_size = AkinatorStrLen(data);
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

Node_t* FindTreeRoot(Node_t* node) {

	if (!node->parent)
		return node;

	return FindTreeRoot(node->parent);
}

#include "Akinator.hpp"

char TREE_DUMP = TREE_FIRST_RUN;

BinaryTreeStatusCode AkinatorDefinitionMode(Tree* tree) {

	char data[NODE_DATA_MAX_LENGTH] = {};
	printf(YELLOW("Enter searched element:")" ");
	scanf("%[^\n]", data);

#ifdef PRINT_DEBUG
	printf("data: %s\n", data);
#endif

	Node_t* searched_node = FindNodeInTree(tree->root, data);

	if (!searched_node) {
		printf(RED("Searched element wasn't found")"\n");
		return TREE_NO_ERROR;
	}

#ifdef PRINT_DEBUG
	printf(GREEN("I found it:") " %p\n", searched_node);
#endif

	printf(GREEN("Definiton of \"%s\"(%zu): "), searched_node->data, NodeDepthInTree(searched_node));
	PrintPathToNode(searched_node);

	return TREE_NO_ERROR;
}

size_t NodeDepthInTree(Node_t* node) {

	if (!node->parent)
		return 0;

	return NodeDepthInTree(node->parent) + 1;
}

BinaryTreeStatusCode PrintPathToNode(Node_t* node) {

	if (!node->parent)
		return TREE_NO_ERROR;

	printf(" - ");

	if (node->parent->right == node)
		printf("not ");

	printf("%s", node->parent->data);
	PrintPathToNode(node->parent);

	return TREE_NO_ERROR;
}

Node_t* FindNodeInTree(Node_t* node, Data_t data) {

	static Node_t* result = NULL;

	if (result && StrCmp(result->data, data) == 0)
		return result;

	if (node->left)  FindNodeInTree(node->left, data);

	if (StrCmp(node->data, data) == 0)
		return result = node;

	if (node->right) FindNodeInTree(node->right, data);

	return (result && StrCmp(result->data, data) == 0 ? result : NULL);
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

	int data_size = StrLen(data);
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

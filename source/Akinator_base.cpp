#include "Akinator_base.hpp"
#include "Akinator_dump.hpp"

static BinaryTreeStatusCode ReadAndCreateNode(Node_t* node, FILE* base_file) {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	if (!node)
		return TREE_NO_ERROR;

	static INIT_TREE(tree);
	tree.root = FindTreeRoot(node);
	BINARY_TREE_GRAPH_DUMP(&tree, "ReadAndCreateNode", node);

	int bracket = fgetc(base_file);
	static int bracket_checker = 1;
	int space_between_quote_and_bracket = 0;
	if (bracket == '{')
		bracket_checker++;
	else if (bracket == '}')
		bracket_checker--;
	else if (bracket == EOF && !bracket_checker)
		return TREE_NO_ERROR;
	else
		TREE_ERROR_CHECK(TREE_BASE_SYNTAX_ERROR);

#ifdef PRINT_DEBUG
	printf("(%d)%c", bracket, bracket);
#endif

	char cur_node[NODE_DATA_MAX_LENGTH] = {};
	fscanf(base_file, "\"%[^\"]\"", cur_node);

#ifdef PRINT_DEBUG
	if (*cur_node) printf("\"%s\"", cur_node);
#endif

	fscanf(base_file, "%*[^{}]%n", &space_between_quote_and_bracket);
	if (!space_between_quote_and_bracket) {
		bracket = fgetc(base_file);
#ifdef PRINT_DEBUG
		printf("%c(%d)", bracket, bracket);
#endif
		bracket_checker--;
		fscanf(base_file, "%*[^{}]");
	}
#ifdef PRINT_DEBUG
	printf("\n");
#endif

	if (!*cur_node) {
		fscanf(base_file, "%*[^{}]");
		ReadAndCreateNode(node->parent, base_file);
		return TREE_NO_ERROR;
	}

	Node_t* new_root = CreateNode(cur_node, NULL, NULL, node);

	if (!node->left || IsRootUnknownWhat(node->left)) {
		if (node->left && IsRootUnknownWhat(node->left)) {
			new_root->right = node->left;
			node->left->parent = new_root;
		}
		node->left = new_root;
	}
	else if (!node->right || IsRootUnknownWhat(node->right)) {
		if (node->right && IsRootUnknownWhat(node->right)) {
			new_root->right = node->right;
			node->right->parent = new_root;
		}
		node->right = new_root;
	}
	else
		TREE_ERROR_CHECK(TREE_BASE_SYNTAX_ERROR);

	if (bracket == '}') {
#ifdef PRINT_DEBUG
		printf("before closed bracket: %s\n", cur_node);
#endif
		ReadAndCreateNode(node, base_file);
		return TREE_NO_ERROR;
	}

	ReadAndCreateNode(new_root, base_file);

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode AkinatorReadBase(Tree* tree) {

	FILE* base_file = fopen(AKINATOR_BASE_, "r");
	if (!base_file)
		TREE_ERROR_CHECK(TREE_FILE_OPEN_ERROR);

	int bracket = fgetc(base_file);
	if (bracket != '{')
		return TREE_BASE_SYNTAX_ERROR;

	char cur_node[NODE_DATA_MAX_LENGTH] = {};
	fscanf(base_file, "\"%[^\"]\"", cur_node);
	tree->root = CreateNode(cur_node, NULL, UNKNOWN_WHAT_(tree->root), NULL);
	for (int i = 0; i < StrLen(cur_node); i++)
		tree->root->data[i] = cur_node[i];

	fscanf(base_file, "%[^{}]", cur_node);

	ReadAndCreateNode(tree->root, base_file);

	if (fclose(base_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	return TREE_NO_ERROR;
}

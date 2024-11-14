#include "Akinator_base.hpp"
#include "Akinator_dump.hpp"

static BinaryTreeStatusCode ReadAndCreateNode(Node_t* node, FILE* base_file) {

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
	printf("(%d)%c", bracket, bracket);

	char cur_node[NODE_DATA_MAX_LENGTH] = {};
	fscanf(base_file, "\"%[^\"]\"", cur_node);
	if (StrLen(cur_node)) printf("\"%s\"", cur_node);

	fscanf(base_file, "%*[^{}]%n", &space_between_quote_and_bracket);
	if (!space_between_quote_and_bracket) {
		bracket = fgetc(base_file);
		printf("%c(%d)", bracket, bracket);
		bracket_checker--;
		fscanf(base_file, "%*[^{}]");
	}
	printf("\n");

	if (!*cur_node)
		return TREE_NO_ERROR;

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
	tree->root = CreateNode(cur_node, NULL, tree->root, NULL);
	for (int i = 0; i < StrLen(cur_node); i++)
		tree->root->data[i] = cur_node[i];

	fscanf(base_file, "%[^{}]", cur_node);

	ReadAndCreateNode(tree->root, base_file);

	if (fclose(base_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	return TREE_NO_ERROR;
}

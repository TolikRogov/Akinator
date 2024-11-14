#include "Akinator_base.hpp"
#include "Akinator_dump.hpp"

static BinaryTreeStatusCode ReadAndCreateNode(Node_t* node, FILE* base_file) {

	int bracket = fgetc(base_file);
	static int bracket_checker = 1;
	if (bracket == '{')
		bracket_checker++;
	else if (bracket == '}')
		bracket_checker--;
	else if (bracket == EOF && !bracket_checker)
		return TREE_NO_ERROR;
	else
		TREE_ERROR_CHECK(TREE_BASE_SYNTAX_ERROR);

	char cur_node[NODE_DATA_MAX_LENGTH] = {};
	fscanf(base_file, "%[^{}]", cur_node);

	printf("(%c)(%d)\n", bracket, bracket);

	ReadAndCreateNode(node, base_file);

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
	fscanf(base_file, "\"%[^\"]", cur_node);
	tree->root = CreateNode(cur_node, NULL, tree->root, NULL);
	for (int i = 0; i < StrLen(cur_node); i++)
		tree->root->data[i] = cur_node[i];

	fscanf(base_file, "%[^{}]", cur_node);

	ReadAndCreateNode(tree->root, base_file);

	if (fclose(base_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	return TREE_NO_ERROR;
}

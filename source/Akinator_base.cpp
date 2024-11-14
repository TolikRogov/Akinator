#include "Akinator_base.hpp"
#include "Akinator_dump.hpp"

static BinaryTreeStatusCode ReadAndCreateNode(Node_t* node, FILE* base_file) {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	static Tree tree = {.root = node};
	BINARY_TREE_GRAPH_DUMP(&tree, "IN PROCESS", NULL);

	char node_data[100] = {};
	static char white_spaces[100] = {};
	static int figure_brackets_checker = 0;
	int symbol = fgetc(base_file);
	int checker_before_change = figure_brackets_checker;
	int cur_str_len = 0;

	if (symbol == '{')
		figure_brackets_checker++;
	else {
		figure_brackets_checker--;
		node->right = NULL;
		return TREE_NO_ERROR;
	}

	if (!figure_brackets_checker)
		return TREE_NO_ERROR;

	printf("figure brackets checker: (%d) - (%d)\n", figure_brackets_checker, figure_brackets_checker - checker_before_change);
	printf("symbol: (%c) - (%d)\n", symbol, symbol);

	fscanf(base_file, "\"%[^\"]%n", node_data, &cur_str_len);
	node->data = (char*)calloc((size_t)cur_str_len, sizeof(char));
	for (int i = 0; i < cur_str_len; i++)
		node->data[i] = node_data[i];
	printf("node_data: (%s)(%d)\n", node_data, *node_data);
	printf("node->data: (%s)(%d)\n", node->data, *node->data);
	fscanf(base_file, "%[^{}]", white_spaces);
	printf("white_spaces: (%s)(%d)\n", white_spaces, *white_spaces);
	getchar();

	if (figure_brackets_checker - checker_before_change > 0) {
		if (!*node_data) {
			// TODO: free empty node
			fscanf(base_file, "\"%[^\"]", white_spaces);
			printf("white_spaces: (%s)(%d)\n", white_spaces, *white_spaces);
			symbol = fgetc(base_file);
			if (symbol == '{')
				figure_brackets_checker++;
			else
				figure_brackets_checker--;
			fscanf(base_file, "%[^{}]", white_spaces);
			printf("white_spaces: (%s)(%d)\n", white_spaces, *white_spaces);
			getchar();
			node->parent->left = NULL;
			return TREE_NO_ERROR;
		}
		cur_str_len = 0;
		fscanf(base_file, "%[^{}]%n", white_spaces, &cur_str_len);
		printf("white_spaces: (%s)(%d)(len: %d)\n", white_spaces, *white_spaces, cur_str_len);
		getchar();

		node->left = CreateNode(NULL, NULL, NULL, node);
		ReadAndCreateNode(node->left, base_file);
	}
	// if (node->left) {
	// 	printf("node->data: (%s)(%d)\n", node->data, *node->data);
	// 	node->right = CreateNode(NULL, NULL, NULL, node);
	// 	//node->left = NULL;
	// 	printf("node right: %p\n", node->right);
	// 	ReadAndCreateNode(node->right, base_file);
	// }
	// else {
	fscanf(base_file, "%[^{}]", white_spaces);
	printf("white_spaces: (%s)(%d)\n", white_spaces, *white_spaces);
	node->right = CreateNode(NULL, NULL, NULL, node);
	ReadAndCreateNode(node->right, base_file);
	printf("HUISHE!\n");

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode AkinatorReadBase(Tree* tree) {

	FILE* base_file = fopen(AKINATOR_BASE_, "r");
	if (!base_file)
		TREE_ERROR_CHECK(TREE_FILE_OPEN_ERROR);

	ReadAndCreateNode(tree->root, base_file);

	if (fclose(base_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	return TREE_NO_ERROR;
}

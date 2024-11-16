#include "Akinator_base.hpp"
#include "Akinator_dump.hpp"

BinaryTreeStatusCode AkinatorRunGame(Tree* tree) {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	sf::SoundBuffer akinator_music;
	akinator_music.loadFromFile(MUSIC_ BG_MUSIC_);

	sf::Sound background;
	background.setBuffer(akinator_music);

	PRINTF_HEADER;
	int c = 0;
	while ((c = getchar()) != EOF) {
		background.play();
		if (c != '\n') getchar();
		else continue;
		switch (c) {
			CASE('c', AkinatorComparingMode(tree));
			CASE('d', AkinatorDefinitionMode(tree));
			CASE('g', AkinatorGuessingMode(tree));
			CASE('t', system(OPEN HTML_FILE_));
			CASE('q', {if (tree->status == TREE_HAS_BEEN_CHANGED) {
					   		printf(BLUE("Do you want to save your tree into the base? [y/n]:")" ");
							if ((c = getchar()) == 'y')
								AKINATOR_SAVE_TREE(tree);
					   }
					   TREE_DTOR(tree, tree->root);
					   printf("GG BRO!\n");
					   return TREE_NO_ERROR;})
			default: {
				printf(RED("UNKNOWN COMMAND!") "\n" YELLOW("TRY AGAIN") "\n");
				break;
			}
		}
		PRINTF_HEADER;
	}

	return TREE_NO_ERROR;
}

static BinaryTreeStatusCode WriteNodeToFile(Node_t* node, FILE* base_file) {

	size_t node_depth = NodeDepthInTree(node);

	for (size_t i = 0; i < node_depth; i++)
		fprintf(base_file, "\t");

	fprintf(base_file, "{\"%s\"", node->data);

	if (node->left)  { fprintf(base_file, "\n"); WriteNodeToFile(node->left, base_file); }
	if (node->right) { fprintf(base_file, "\n"); WriteNodeToFile(node->right, base_file); }

	if (node->left)	{
		fprintf(base_file, "\n");
		for (size_t i = 0; i < node_depth; i++)
			fprintf(base_file, "\t");

	}
	fprintf(base_file, "}");

	return TREE_NO_ERROR;
}

BinaryTreeStatusCode SaveTreeToBase(Tree* tree) {

	FILE* base_file = fopen(AKINATOR_BASE_, "w");
	if (!base_file)
		TREE_ERROR_CHECK(TREE_FILE_OPEN_ERROR);

	WriteNodeToFile(tree->root, base_file);

	printf(GREEN("Changes have been made to the database!")"\n");

	if (fclose(base_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	return TREE_NO_ERROR;
}

static BinaryTreeStatusCode ReadAndCreateNode(Node_t* node, FILE* base_file) {

	if (!node)
		return TREE_NO_ERROR;

#ifdef GENERATE_BASE_TREE_DUMP
	static INIT_TREE(tree);
	tree.root = FindTreeRoot(node);

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;
	BINARY_TREE_GRAPH_DUMP(&tree, "ReadAndCreateNode", node);
#endif

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

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	FILE* base_file = fopen(AKINATOR_BASE_, "r");
	if (!base_file)
		TREE_ERROR_CHECK(TREE_FILE_OPEN_ERROR);

	int bracket = fgetc(base_file);
	if (bracket != '{')
		return TREE_BASE_SYNTAX_ERROR;

	char cur_node[NODE_DATA_MAX_LENGTH] = {};
	fscanf(base_file, "\"%[^\"]\"", cur_node);
	tree->root = CreateNode(cur_node, NULL, UNKNOWN_WHAT_(tree->root), NULL);
	for (int i = 0; i < AkinatorStrLen(cur_node); i++)
		tree->root->data[i] = cur_node[i];

	fscanf(base_file, "%[^{}]", cur_node);

	ReadAndCreateNode(tree->root, base_file);

	BINARY_TREE_GRAPH_DUMP(tree, "AkinatorReadBase", NULL);

	if (fclose(base_file))
		TREE_ERROR_CHECK(TREE_FILE_CLOSE_ERROR);

	return TREE_NO_ERROR;
}

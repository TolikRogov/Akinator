#include "Akinator_dump.hpp"
#include "Akinator_base.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	INIT_TREE(tree);

	TREE_CTOR(&tree);

	BINARY_TREE_GRAPH_DUMP(&tree, "Start", NULL);
	AKINATOR_READ_BASE(&tree);
	BINARY_TREE_GRAPH_DUMP(&tree, "End", NULL);

	TREE_DTOR(tree.root);

#ifdef HTML_OPEN
	system(OPEN HTML_FILE_);
#endif

	return 0;
}

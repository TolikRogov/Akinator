#include "Akinator_dump.hpp"
#include "Akinator_base.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	INIT_TREE(tree);
	TREE_CTOR(&tree);

	AKINATOR_READ_BASE(&tree);

	AKINATOR_RUN_GAME(&tree);

	return 0;
}

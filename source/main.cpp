#include "Akinator_dump.hpp"
#include "Akinator_base.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	INIT_TREE(tree);
	TREE_CTOR(&tree);
	AKINATOR_READ_BASE(&tree);



	TREE_DTOR(tree.root);
#ifdef HTML_OPEN
	system(OPEN HTML_FILE_);
#endif
	return 0;
}

#include "Akinator_dump.hpp"
#include "Akinator.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	INIT_TREE(tree);

	TREE_CTOR(&tree);

	Node_t* node1 = CreateNode("Полторашка", NULL, NULL);
	Node_t* node2 = CreateNode("Бурцев", NULL, NULL);
	Node_t* node3 = CreateNode("Колдунов", NULL, NULL);
	Node_t* node4 = CreateNode("Овчос", NULL, NULL);
	Node_t* node5 = CreateNode("Чубаров", NULL, NULL);
	Node_t* node6 = CreateNode("Нефор", node3, node4);
	Node_t* node7 = CreateNode("Ведёт физос", node6, node5);
	Node_t* node8 = CreateNode("Ведёт дискру", node2, node7);
	Node_t* nodeRoot = CreateNode("Животное", node1, node8);
	tree.root = nodeRoot;

	BINARY_TREE_GRAPH_DUMP(&tree, "Start", node4);

	TREE_DTOR(tree.root);

#ifdef HTML_OPEN
	system(OPEN HTML_FILE_);
#endif

	return 0;
}

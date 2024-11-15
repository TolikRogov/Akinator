#include "Akinator_dump.hpp"
#include "Akinator_base.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	INIT_TREE(tree);
	TREE_CTOR(&tree);
	AKINATOR_READ_BASE(&tree);

	PRINTF_HEADER;
	int c = 0;
	while ((c = getchar()) != EOF) {
		if (c != '\n') getchar();
		else continue;
		switch (c) {
			CASE('c', AkinatorComparingMode(&tree));
			CASE('d', AkinatorDefinitionMode(&tree));
			CASE('g', AkinatorGuessingMode(&tree));
			CASE('t', system(OPEN HTML_FILE_));
			CASE('q', {TREE_DTOR(tree.root);
					   printf("GG BRO!\n");
					   return TREE_NO_ERROR;})
			default: {
				printf(RED("UNKNOWN COMMAND!") "\n" YELLOW("TRY AGAIN") "\n");
				break;
			}
		}
		PRINTF_HEADER;
	}

	return 0;
}

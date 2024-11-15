#include "Akinator_dump.hpp"
#include "Akinator_base.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	INIT_TREE(tree);
	TREE_CTOR(&tree);
	AKINATOR_READ_BASE(&tree);

#define PRINTF_HEADER {														 \
	printf("\n-----------------------------------------------------\n");	\
	printf(BLUE("For exit from program enter 'q'") "\n");					\
	printf(BLUE("For running guessing mode enter 'g'") "\n");				\
	printf(BLUE("For previewing akinator tree enter 't'") "\n");			\
	printf(BLUE("For getting definition enter 'd'") "\n");				 	 \
	printf("-----------------------------------------------------\n");		\
}

	PRINTF_HEADER;
	int c = 0;
	while ((c = getchar()) != EOF) {
		if (c != '\n') getchar();
		else continue;
		switch (c) {
			case 'd': {
				AkinatorDefinitionMode(&tree);
				break;
			}
			case 't': {
				system(OPEN HTML_FILE_);
				break;
			}
			case 'g': {
				AkinatorGuessingMode(&tree);
				break;
			}
			case 'q': {
				TREE_DTOR(tree.root);
				printf("GG BRO!\n");
				return TREE_NO_ERROR;
			}
			default: {
				printf(RED("UNKNOWN COMMAND!") "\n" YELLOW("TRY AGAIN") "\n");
				break;
			}
		}
		PRINTF_HEADER;
	}

#undef PRINTF_HEADER

	return 0;
}

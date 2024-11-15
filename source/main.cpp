#include "Akinator_dump.hpp"
#include "Akinator_base.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	INIT_TREE(tree);
	TREE_CTOR(&tree);
	AKINATOR_READ_BASE(&tree);

#define PRINTF_HEADER {														 \
	printf("\n-----------------------------------------------------\n");	\
	printf(BLUE("'g': start guessing game") "\n");							\
	printf(BLUE("'t': getting tree dump") "\n");							\
	printf(BLUE("'d': getting definition") "\n");				 			 \
	printf(BLUE("'q': exit from program") "\n");							\
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

#include "Akinator_dump.hpp"
#include "Akinator_base.hpp"

int main() {

	BinaryTreeStatusCode tree_status = TREE_NO_ERROR;

	INIT_TREE(tree);
	TREE_CTOR(&tree);
	AKINATOR_READ_BASE(&tree);

#define PRINTF_HEADER {														 \
	printf("\n" BLUE("For exit from program enter 'q'") "\n");				\
	printf(		BLUE("For run guessing mode enter 'g'") "\n");				\
	printf(		BLUE("For preview akinator tree enter 't'") "\n");			\
}

	PRINTF_HEADER;
	int c = 0;
	while ((c = getchar()) != EOF) {
		getchar();
		switch (c) {
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

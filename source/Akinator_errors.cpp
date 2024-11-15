#include "Akinator_errors.hpp"

const char* BinaryTreeErrorsMessenger(BinaryTreeStatusCode status) {
	switch(status) {
		case TREE_NO_ERROR:					return "TREE ERROR - NO ERROR";
		case TREE_ALLOC_ERROR:				return "TREE ERROR - MEMORY ALLOCATION ERROR";
		case TREE_NULL_POINTER:				return "TREE ERROR - POINTER IS NULL";

		case TREE_INVALID_TYPE:				return "TREE ERROR - INVALID TYPE OF INPUT ELEMENT";
		case TREE_BASE_SYNTAX_ERROR:		return "TREE ERROR - INVALID SYNTAX IN DATA BASE";
		case TREE_ROOT_IS_UNKNOWN:			return "TREE ERROR - ROOT IS UNKOWN";
		case TREE_NODE_NON_EXISTENT:		return "TREE ERROR - NODE IS NON EXISTENT";
		case TREE_NODE_ALREADY_EXISTENT:	return "TREE ERROR - NODE HAS ALREADY BEEN IN TREE";

		case TREE_FILE_OPEN_ERROR:			return "TREE ERROR - FILE WAS NOT OPENED";
		case TREE_FILE_CLOSE_ERROR:			return "TREE ERROR - FILE WAS NOT CLOSED";
		case TREE_DIR_CLOSE_ERROR:			return "TREE ERROR - DIRECTORY WAS NOT CLOSED";

		case TREE_UNDEFINED_ERROR:
		default: 							return "UNDEFINED ERROR";
	}
}

int StrCmp(const char* str1, const char* str2) {

	if (!str1 || !str2)
		return -1;

	size_t i = 0;
	for (; *(str1 + i) != '\0' && *(str2 + i) != '\0'; i++) {
		if (*(str1 + i) != *(str2 + i))
			break;
	}
	return (*(str1 + i) - *(str2 + i));
}

int AkinatorStrLen(const char* str) {

	if (!str)
		return -1;

	int i = 0;
	for (; *(str + i) != '\0'; i++) {}

	return i;
}

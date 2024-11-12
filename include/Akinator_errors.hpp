#pragma once

#include <stdio.h>

#define RED(str) 		"\033[31;1m" str "\033[0m"
#define YELLOW(str) 	"\033[33;4m" str "\033[0m"
#define GREEN(str) 		"\033[32;6m" str "\033[0m"

#define TREE_ERROR_CHECK(status) {																					 \
	if (status != TREE_NO_ERROR) {																					\
		fprintf(stderr, "\n\n" RED("Error (code %d): %s, ") YELLOW("File: %s, Function: %s, Line: %d\n\n"),   		\
					status, BinaryTreeErrorsMessenger(status), __FILE__, __PRETTY_FUNCTION__, __LINE__);			\
		fclose(stderr);																								\
		return status;																								\
	}																												\
}

enum BinaryTreeStatusCode {
	TREE_NO_ERROR,
	TREE_ALLOC_ERROR,
	TREE_NULL_POINTER,

	TREE_INVALID_TYPE,

	TREE_FILE_OPEN_ERROR,
	TREE_FILE_CLOSE_ERROR,
	TREE_DIR_CLOSE_ERROR,
};

const char* BinaryTreeErrorsMessenger(BinaryTreeStatusCode status);
int StrCmp(const char* str1, const char* str2);

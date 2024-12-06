#include "utils.h"
//#include <stdio.h>
//#include <string.h>

// implimentation of utils library for odds and ends

void CleanNewLineFromString(char* Name) {
	for (int i = 0; i < strlen(Name); i++)
		if (Name[i] == '\n')
			Name[i] = '\0';
}
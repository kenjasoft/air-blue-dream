#include "common.h"

char* readFile(const char* fileName) {
	char* buffer = 0;
	unsigned long length;
	FILE* file = fopen(fileName, "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);
		buffer = malloc(length + 1);
		if (buffer == NULL) return NULL;
		memset(buffer, 0, length + 1);
		fread(buffer, 1, length, file);
		fclose(file);
		buffer[length] = '\0';
	}
	return buffer;
}

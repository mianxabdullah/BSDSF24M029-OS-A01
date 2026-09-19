#include "../include/myfilefunctions.h"
#include <stdlib.h>
#include <string.h>

int wordCount(FILE* file, int* lines, int* words, int* chars) {
    *lines = 0; *words = 0; *chars = 0;
    int c, inWord = 0;

    while ((c = fgetc(file)) != EOF) {
        (*chars)++;
        if (c == '\n') (*lines)++;
        if (c == ' ' || c == '\n' || c == '\t') {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            (*words)++;
        }
    }
    return 0;
}

int mygrep(FILE* fp, const char* search_str, char*** matches) {
    char buffer[1024];
    char** results = malloc(100 * sizeof(char*));
    int count = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL && count < 100) {
        if (strstr(buffer, search_str) != NULL) {
            results[count] = malloc(strlen(buffer) + 1);
            strcpy(results[count], buffer);
            count++;
        }
    }

    *matches = results;
    return count;
}

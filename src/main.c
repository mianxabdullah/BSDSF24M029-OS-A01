#include <stdio.h>
#include <stdlib.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("--- Testing String Functions ---\n");
    char dest[100];

    printf("mystrlen(\"hello\") = %d\n", mystrlen("hello"));

    mystrcpy(dest, "hello world");
    printf("mystrcpy -> %s\n", dest);

    char dest2[10];
    mystrncpy(dest2, "hello world", 5);
    dest2[5] = '\0';
    printf("mystrncpy -> %s\n", dest2);

    char dest3[100] = "hello ";
    mystrcat(dest3, "world");
    printf("mystrcat -> %s\n", dest3);

    printf("\n--- Testing File Functions ---\n");
    FILE* fp = fopen("test.txt", "r");
    if (!fp) {
        printf("Could not open test.txt\n");
        return 1;
    }

    int lines, words, chars;
    wordCount(fp, &lines, &words, &chars);
    printf("Lines: %d, Words: %d, Chars: %d\n", lines, words, chars);

    rewind(fp);
    char** matches;
    int matchCount = mygrep(fp, "test", &matches);
    printf("mygrep found %d matching lines:\n", matchCount);
    for (int i = 0; i < matchCount; i++) {
        printf("  %s", matches[i]);
        free(matches[i]);
    }
    free(matches);

    fclose(fp);
    return 0;
}

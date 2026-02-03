/**
 * Solution 8.2: Word Count with Command Line Arguments
 * Week 8 - Advanced Arrays and Strings
 * 
 * Description: Word count program using command line arguments
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int countWords(FILE *file) {
    int words = 0;
    int inWord = 0;
    int ch;
    
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            words++;
        }
    }
    
    return words;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    /* argv[0] is the program name */
    /* argv[1] is the filename */
    /* FILE is a pointer to a FILE structure */
    /* fopen is a function to open a file */
    /* "r" is the mode to open the file in read mode */
    /* if the file is not found, fopen will return NULL */
    /* if the file is found, fopen will return a pointer to the file */
    /* if the file is not found, fopen will return NULL */
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", argv[1]);
        /* fclose a NULL pointer is a no-op - segmentation fault */
        return 1;
    }
    
    int wordCount = countWords(file);
    fclose(file);
    
    printf("File '%s' contains %d words.\n", argv[1], wordCount);
    
    return 0;
}
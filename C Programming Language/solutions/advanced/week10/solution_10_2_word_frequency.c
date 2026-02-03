/**
 * Solution 10.2: Word Frequency Counter
 * Week 10 - File Input/Output
 * 
 * Description: Word frequency counter
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

struct WordCount {
    char word[MAX_WORD_LENGTH];
    int count;
};

struct WordCount wordList[MAX_WORDS];
int wordCount = 0;

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int findWord(char *word) {
    for (int i = 0; i < wordCount; i++) {
        if (strcmp(wordList[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void addWord(char *word) {
    toLowerCase(word);
    
    int index = findWord(word);
    if (index != -1) {
        wordList[index].count++;
    } else if (wordCount < MAX_WORDS) {
        strcpy(wordList[wordCount].word, word);
        wordList[wordCount].count = 1;
        wordCount++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", argv[1]);
        return 1;
    }
    
    char word[MAX_WORD_LENGTH];
    
    while (fscanf(file, "%49s", word) == 1) {
        // Remove punctuation
        int len = strlen(word);
        while (len > 0 && !isalnum(word[len-1])) {
            word[len-1] = '\0';
            len--;
        }
        
        if (len > 0) {
            addWord(word);
        }
    }
    
    fclose(file);
    
    printf("Word Frequency Report\n");
    printf("=====================\n");
    
    for (int i = 0; i < wordCount; i++) {
        printf("%-20s: %d\n", wordList[i].word, wordList[i].count);
    }
    
    printf("\nTotal unique words: %d\n", wordCount);
    
    return 0;
}
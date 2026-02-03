/*
Write a C program to count how many words are in a sentence.
Assume words are separated by spaces.

Example Input:
Hello there my friend

Expected Output:
4
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* "Hello there my friend" */
/* The last character is not a space, is a NULL \0 character, so we need to add 1 to the count */
int countWords(char *sentence) {
    int count = 0;
    for (int i = 0; i < strlen(sentence); i++) {
        if (sentence[i] == ' ') {
            count++;
        }
    }
    return count + 1;
}

int main() {
    char sentence[100];
    printf("Enter a sentence: ");
    snprintf(sentence, sizeof(sentence), "Hello there my friend");
    for (int i = 0; i < strlen(sentence); i++) {
        printf("%c %d %X\n", sentence[i], sentence[i], sentence[i]);
    }
    printf("\n");
    printf("The number of words in the sentence is: %d\n", countWords(sentence));
    return 0;
}
/**
 * Solution 8.3: String Tokenizer
 * Week 8 - Advanced Arrays and Strings
 * 
 * Description: String tokenizer program
 */

#include <stdio.h>
#include <string.h>

void tokenizeString(char *str, char delimiter) {
    char *token = strtok(str, &delimiter);
    int count = 0;
    
    printf("Tokens:\n");
    while (token != NULL) {
        count++;
        printf("%d: %s\n", count, token);
        token = strtok(NULL, &delimiter);
    }
    
    printf("Total tokens: %d\n", count);
}

int main() {
    char str[200];
    char delimiter;
    
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    
    // Remove newline character
    str[strcspn(str, "\n")] = '\0';
    
    printf("Enter delimiter: ");
    scanf("%c", &delimiter);
    
    tokenizeString(str, delimiter);
    
    return 0;
}
/**
 * Solution 11.1: Dynamic String Manipulation
 * Week 11 - Dynamic Memory Management
 * 
 * Description: Dynamic string manipulation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* createString(const char* initial) {
    if (initial == NULL) {
        return NULL;
    }
    
    int len = strlen(initial);
    char* str = (char*)malloc((len + 1) * sizeof(char));
    
    if (str != NULL) {
        strcpy(str, initial);
    }
    
    return str;
}

char* concatenateStrings(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }
    
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    char* result = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    
    if (result != NULL) {
        strcpy(result, str1);
        strcat(result, str2);
    }
    
    return result;
}

char* resizeString(char* str, int newSize) {
    if (str == NULL || newSize <= 0) {
        return NULL;
    }
    
    char* newStr = (char*)realloc(str, newSize * sizeof(char));
    
    return newStr;
}

int main() {

    char* str1 = createString("Hello");
    char* str2 = createString(" World");
    
    if (str1 == NULL || str2 == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    
    char* combined = concatenateStrings(str1, str2);
    if (combined != NULL) {
        printf("Combined: %s\n", combined);
    }
    
    // Resize string to accommodate more text
    str1 = resizeString(str1, 100);
    if (str1 != NULL) {
        strcat(str1, " from C!");
        printf("Extended string 1: %s\n", str1);
    }
    
    // Free allocated memory
    free(str1);
    free(str2);
    free(combined);
    
    printf("Memory freed successfully!\n");
    
    return 0;
}
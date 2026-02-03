/*
 * Problem: Zigzag Conversion
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <stdlib.h>
#include <string.h>

char* convert(char* s, int numRows) {
    int len = strlen(s);
    if (numRows == 1 || numRows >= len) {
        char* result = (char*)malloc((len + 1) * sizeof(char));
        strcpy(result, s);
        return result;
    }
    
    char** rows = (char**)malloc(numRows * sizeof(char*));
    int* rowSizes = (int*)calloc(numRows, sizeof(int));
    int* rowCapacities = (int*)malloc(numRows * sizeof(int));
    
    for (int i = 0; i < numRows; i++) {
        rowCapacities[i] = len;
        rows[i] = (char*)malloc(rowCapacities[i] * sizeof(char));
        rowSizes[i] = 0;
    }
    
    int currentRow = 0;
    int goingDown = 0;
    
    for (int i = 0; i < len; i++) {
        rows[currentRow][rowSizes[currentRow]++] = s[i];
        if (currentRow == 0 || currentRow == numRows - 1) {
            goingDown = !goingDown;
        }
        currentRow += goingDown ? 1 : -1;
    }
    
    char* result = (char*)malloc((len + 1) * sizeof(char));
    int idx = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < rowSizes[i]; j++) {
            result[idx++] = rows[i][j];
        }
        free(rows[i]);
    }
    result[idx] = '\0';
    
    free(rows);
    free(rowSizes);
    free(rowCapacities);
    
    return result;
}
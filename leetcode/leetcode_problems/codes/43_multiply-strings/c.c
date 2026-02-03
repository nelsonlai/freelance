/*
 * Problem: Multiply Strings
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <stdlib.h>
#include <string.h>

char* multiply(char* num1, char* num2) {
    if (strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0) {
        char* result = (char*)malloc(2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    
    int m = strlen(num1);
    int n = strlen(num2);
    int* result = (int*)calloc(m + n, sizeof(int));
    
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j;
            int p2 = i + j + 1;
            int total = mul + result[p2];
            
            result[p2] = total % 10;
            result[p1] += total / 10;
        }
    }
    
    // Remove leading zeros
    int start = 0;
    while (start < m + n && result[start] == 0) {
        start++;
    }
    
    char* res = (char*)malloc((m + n - start + 1) * sizeof(char));
    int idx = 0;
    for (int i = start; i < m + n; i++) {
        res[idx++] = result[i] + '0';
    }
    res[idx] = '\0';
    
    free(result);
    return res;
}
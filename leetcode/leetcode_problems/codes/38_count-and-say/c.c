/*
 * Problem: Count and Say
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <stdlib.h>
#include <string.h>

char* countAndSay(int n) {
    if (n == 1) {
        char* result = (char*)malloc(2 * sizeof(char));
        strcpy(result, "1");
        return result;
    }
    
    char* result = (char*)malloc(10000 * sizeof(char));
    strcpy(result, "1");
    
    for (int i = 1; i < n; i++) {
        char* newResult = (char*)malloc(10000 * sizeof(char));
        int newIdx = 0;
        int j = 0;
        
        while (result[j] != '\0') {
            int count = 1;
            while (result[j + 1] != '\0' && result[j] == result[j + 1]) {
                count++;
                j++;
            }
            newResult[newIdx++] = count + '0';
            newResult[newIdx++] = result[j];
            j++;
        }
        newResult[newIdx] = '\0';
        
        free(result);
        result = newResult;
    }
    
    return result;
}
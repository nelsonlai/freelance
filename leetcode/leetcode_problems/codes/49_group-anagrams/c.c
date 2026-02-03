/*
 * Problem: Group Anagrams
 * Difficulty: Medium
 * Tags: array, string, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare_char(const void* a, const void* b) {
    return *(char*)a - *(char*)b;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    // Create sorted keys for each string
    char** keys = (char**)malloc(strsSize * sizeof(char*));
    int* indices = (int*)malloc(strsSize * sizeof(int));
    for (int i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        keys[i] = (char*)malloc((len + 1) * sizeof(char));
        strcpy(keys[i], strs[i]);
        qsort(keys[i], len, sizeof(char), compare_char);
        indices[i] = i;
    }
    
    // Sort indices by keys
    for (int i = 0; i < strsSize; i++) {
        for (int j = i + 1; j < strsSize; j++) {
            if (strcmp(keys[indices[i]], keys[indices[j]]) > 0) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
    
    // Count groups
    *returnSize = 0;
    if (strsSize > 0) {
        (*returnSize)++;
        for (int i = 1; i < strsSize; i++) {
            if (strcmp(keys[indices[i]], keys[indices[i-1]]) != 0) {
                (*returnSize)++;
            }
        }
    }
    
    // Allocate result
    char*** result = (char***)malloc(*returnSize * sizeof(char**));
    *returnColumnSizes = (int*)malloc(*returnSize * sizeof(int));
    
    // Build groups
    int groupIdx = 0;
    int start = 0;
    for (int i = 1; i <= strsSize; i++) {
        if (i == strsSize || strcmp(keys[indices[i]], keys[indices[start]]) != 0) {
            int count = i - start;
            (*returnColumnSizes)[groupIdx] = count;
            result[groupIdx] = (char**)malloc(count * sizeof(char*));
            for (int j = 0; j < count; j++) {
                int len = strlen(strs[indices[start + j]]);
                result[groupIdx][j] = (char*)malloc((len + 1) * sizeof(char));
                strcpy(result[groupIdx][j], strs[indices[start + j]]);
            }
            groupIdx++;
            start = i;
        }
    }
    
    // Free keys
    for (int i = 0; i < strsSize; i++) {
        free(keys[i]);
    }
    free(keys);
    free(indices);
    
    return result;
}
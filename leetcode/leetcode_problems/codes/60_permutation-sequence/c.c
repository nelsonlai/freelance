/*
 * Problem: Permutation Sequence
 * Difficulty: Hard
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <stdlib.h>
#include <string.h>

char* getPermutation(int n, int k) {
    int* nums = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        nums[i] = i + 1;
    }
    
    int* fact = (int*)malloc(n * sizeof(int));
    fact[0] = 1;
    for (int i = 1; i < n; i++) {
        fact[i] = fact[i - 1] * i;
    }
    
    k--; // Convert to 0-indexed
    char* result = (char*)malloc((n + 1) * sizeof(char));
    int pos = 0;
    
    for (int i = n - 1; i >= 0; i--) {
        int index = k / fact[i];
        result[pos++] = '0' + nums[index];
        
        // Remove element at index
        for (int j = index; j < n - 1; j++) {
            nums[j] = nums[j + 1];
        }
        
        k %= fact[i];
    }
    
    result[pos] = '\0';
    free(nums);
    free(fact);
    
    return result;
}
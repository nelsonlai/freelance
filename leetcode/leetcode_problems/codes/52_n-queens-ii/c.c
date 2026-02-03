/*
 * Problem: N-Queens II
 * Difficulty: Hard
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <stdbool.h>
#include <stdlib.h>

void backtrack(int* count, int row, int n, bool* cols, bool* diag1, bool* diag2) {
    if (row == n) {
        (*count)++;
        return;
    }
    
    for (int col = 0; col < n; col++) {
        int d1 = row - col + n - 1;
        int d2 = row + col;
        
        if (cols[col] || diag1[d1] || diag2[d2]) {
            continue;
        }
        
        cols[col] = true;
        diag1[d1] = true;
        diag2[d2] = true;
        
        backtrack(count, row + 1, n, cols, diag1, diag2);
        
        cols[col] = false;
        diag1[d1] = false;
        diag2[d2] = false;
    }
}

int totalNQueens(int n) {
    int count = 0;
    bool* cols = (bool*)calloc(n, sizeof(bool));
    bool* diag1 = (bool*)calloc(2 * n - 1, sizeof(bool));
    bool* diag2 = (bool*)calloc(2 * n - 1, sizeof(bool));
    
    backtrack(&count, 0, n, cols, diag1, diag2);
    
    free(cols);
    free(diag1);
    free(diag2);
    
    return count;
}
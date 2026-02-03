/*
 * Problem: N-Queens
 * Difficulty: Hard
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    bool* cols;
    bool* diag1;
    bool* diag2;
    char** board;
    int n;
    char*** result;
    int* resultSize;
    int* capacity;
    int** returnColumnSizes;
} BacktrackState;

void backtrack(BacktrackState* state, int row) {
    if (row == state->n) {
        if (*state->resultSize >= *state->capacity) {
            *state->capacity *= 2;
            state->result = (char***)realloc(state->result, *state->capacity * sizeof(char**));
            *state->returnColumnSizes = (int*)realloc(*state->returnColumnSizes, *state->capacity * sizeof(int));
        }
        
        state->result[*state->resultSize] = (char**)malloc(state->n * sizeof(char*));
        for (int i = 0; i < state->n; i++) {
            state->result[*state->resultSize][i] = (char*)malloc((state->n + 1) * sizeof(char));
            strcpy(state->result[*state->resultSize][i], state->board[i]);
        }
        (*state->returnColumnSizes)[*state->resultSize] = state->n;
        (*state->resultSize)++;
        return;
    }
    
    for (int col = 0; col < state->n; col++) {
        int d1 = row - col + state->n - 1;
        int d2 = row + col;
        
        if (state->cols[col] || state->diag1[d1] || state->diag2[d2]) {
            continue;
        }
        
        state->board[row][col] = 'Q';
        state->cols[col] = true;
        state->diag1[d1] = true;
        state->diag2[d2] = true;
        
        backtrack(state, row + 1);
        
        state->board[row][col] = '.';
        state->cols[col] = false;
        state->diag1[d1] = false;
        state->diag2[d2] = false;
    }
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int capacity = 16;
    char*** result = (char***)malloc(capacity * sizeof(char**));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    
    char** board = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        board[i] = (char*)malloc((n + 1) * sizeof(char));
        for (int j = 0; j < n; j++) {
            board[i][j] = '.';
        }
        board[i][n] = '\0';
    }
    
    bool* cols = (bool*)calloc(n, sizeof(bool));
    bool* diag1 = (bool*)calloc(2 * n - 1, sizeof(bool));
    bool* diag2 = (bool*)calloc(2 * n - 1, sizeof(bool));
    
    BacktrackState state = {
        .cols = cols,
        .diag1 = diag1,
        .diag2 = diag2,
        .board = board,
        .n = n,
        .result = result,
        .resultSize = returnSize,
        .capacity = &capacity,
        .returnColumnSizes = returnColumnSizes
    };
    
    backtrack(&state, 0);
    
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
    free(cols);
    free(diag1);
    free(diag2);
    
    return result;
}
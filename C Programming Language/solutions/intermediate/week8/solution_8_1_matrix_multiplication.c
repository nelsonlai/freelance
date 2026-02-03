/**
 * Solution 8.1: Matrix Multiplication
 * Week 8 - Advanced Arrays and Strings
 * 
 * Description: Matrix multiplication program
 */

#include <stdio.h>

void multiplyMatrices(int first[10][10], int second[10][10], int result[10][10], 
                     int r1, int c1, int r2, int c2) {
    // Initialize result matrix to zero
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
        }
    }
    
    // Multiply matrices
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }
}

void printMatrix(int matrix[10][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int first[10][10], second[10][10], result[10][10];
    int r1, c1, r2, c2;
    
    printf("Enter rows and columns for first matrix: ");
    scanf("%d %d", &r1, &c1);
    
    printf("Enter rows and columns for second matrix: ");
    scanf("%d %d", &r2, &c2);
    
    if (c1 != r2) {
        printf("Matrix multiplication not possible!\n");
        return 1;
    }
    
    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            scanf("%d", &first[i][j]);
        }
    }
    
    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < r2; i++) {
        for (int j = 0; j < c2; j++) {
            scanf("%d", &second[i][j]);
        }
    }
    
    multiplyMatrices(first, second, result, r1, c1, r2, c2);
    
    printf("Result matrix:\n");
    printMatrix(result, r1, c2);
    
    return 0;
}
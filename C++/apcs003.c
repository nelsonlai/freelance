/*
Given a 3×3 integer matrix, write code that prints the sum of 
the main diagonal and the secondary diagonal.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int main_diagonal_sum = 0;
    for (int i = 0; i < 3; i++) {
        main_diagonal_sum += matrix[i][i];
    }

    printf("Main diagonal sum: %d\n", main_diagonal_sum);
}

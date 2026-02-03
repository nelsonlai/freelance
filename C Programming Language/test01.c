/*
最接近的兩數（Closest Pair）
📘 題目敘述

輸入 N 個整數，找出差距最小的兩個數，並輸出差值。

📥 輸入格式

第一行：N（2 ≤ N ≤ 10⁵）
第二行：N 個整數（皆在 −10⁹ ~ 10⁹）

📤 輸出格式

最小差值

🧪 範例

輸入：

5
8 1 4 10 2
1 2 4 8 10
輸出：1

*/
#include <stdio.h>

void sortArray(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                // Swap using pointers
                int temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

int main() {
    int n;
    
    // Read number of elements
    scanf("%d", &n);
    
    int arr[n];
    
    // Read elements into array
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Sort the array
    sortArray(arr, n);
    
    // Find the minimum difference
    int min_diff = 2147483647; // Initialize to max int
    for (int i = 1; i < n; i++) {
        int diff = *(arr + i) - *(arr + i - 1);
        if (diff < min_diff) {
            min_diff = diff;
        }
    }
    
    // Output the minimum difference
    printf("%d\n", min_diff);
    
    return 0;
}

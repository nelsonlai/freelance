/**
 * Solution 6.1: Largest Element in Array
 * Week 6 - Arrays and String Basics
 * 
 * Description: Find the largest element in an array
 */

#include <stdio.h>

int main() {
    int n, largest;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    largest = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
    }
    
    printf("Largest element: %d\n", largest);
    
    return 0;
}
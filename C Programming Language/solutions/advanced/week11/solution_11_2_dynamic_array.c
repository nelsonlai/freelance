/**
 * Solution 11.2: Resizable Array Implementation
 * Week 11 - Dynamic Memory Management
 * 
 * Description: Resizable array implementation
 */

#include <stdio.h>
#include <stdlib.h>

struct DynamicArray {
    int* data;
    int size;
    int capacity;
};

struct DynamicArray* createArray(int initialCapacity) {
    struct DynamicArray* arr = (struct DynamicArray*)malloc(sizeof(struct DynamicArray));
    
    if (arr != NULL) {
        arr->data = (int*)malloc(initialCapacity * sizeof(int));
        if (arr->data != NULL) {
            arr->size = 0;
            arr->capacity = initialCapacity;
        } else {
            free(arr);
            arr = NULL;
        }
    }
    
    return arr;
}

int resize(struct DynamicArray* arr, int newCapacity) {
    if (arr == NULL || newCapacity <= 0) {
        return 0;
    }
    
    int* newData = (int*)realloc(arr->data, newCapacity * sizeof(int));
    if (newData == NULL) {
        return 0; // Reallocation failed
    }
    
    arr->data = newData;
    arr->capacity = newCapacity;
    
    if (arr->size > newCapacity) {
        arr->size = newCapacity;
    }
    
    return 1; // Success
}

int append(struct DynamicArray* arr, int value) {
    if (arr == NULL) {
        return 0;
    }
    
    if (arr->size >= arr->capacity) {
        // Double the capacity
        if (!resize(arr, arr->capacity * 2)) {
            return 0;
        }
    }
    
    arr->data[arr->size] = value;
    arr->size++;
    
    return 1;
}

void printArray(struct DynamicArray* arr) {
    if (arr == NULL) {
        printf("Array is NULL\n");
        return;
    }
    
    printf("Array (size: %d, capacity: %d): [", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void freeArray(struct DynamicArray* arr) {
    if (arr != NULL) {
        free(arr->data);
        free(arr);
    }
}

int main() {
    struct DynamicArray* arr = createArray(2);
    
    if (arr == NULL) {
        printf("Failed to create array!\n");
        return 1;
    }
    
    // Add elements
    for (int i = 1; i <= 10; i++) {
        append(arr, i * 10);
        printArray(arr);
    }
    
    // Manually resize
    printf("\nResizing to capacity 5...\n");
    resize(arr, 5);
    printArray(arr);
    
    freeArray(arr);
    printf("Array freed successfully!\n");
    
    return 0;
}
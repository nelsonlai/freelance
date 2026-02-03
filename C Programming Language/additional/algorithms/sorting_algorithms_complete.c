/**
 * Complete Sorting Algorithms Implementation
 * Comprehensive demonstration of various sorting algorithms with analysis
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Function prototypes
void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void merge_sort(int arr[], int left, int right);
void quick_sort(int arr[], int low, int high);
void heap_sort(int arr[], int n);
void counting_sort(int arr[], int n, int max_val);
void radix_sort(int arr[], int n);
void bucket_sort(float arr[], int n);
void shell_sort(int arr[], int n);

// Helper functions
void merge(int arr[], int left, int mid, int right);
int partition(int arr[], int low, int high);
int partition_random(int arr[], int low, int high);
void heapify(int arr[], int n, int i);
void build_max_heap(int arr[], int n);
int get_max(int arr[], int n);
void counting_sort_for_radix(int arr[], int n, int exp);
void print_array(int arr[], int n);
void copy_array(int source[], int dest[], int n);
double measure_time(void (*sort_func)(int[], int), int arr[], int n);
bool is_sorted(int arr[], int n);

void demonstrate_simple_sorts() {
    printf("=== Simple Sorting Algorithms ===\n");
    
    int original[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int n = sizeof(original) / sizeof(original[0]);
    int arr[8];
    
    printf("Original array: ");
    print_array(original, n);
    
    // Bubble Sort
    copy_array(original, arr, n);
    printf("\nBubble Sort:\n");
    printf("Before: ");
    print_array(arr, n);
    bubble_sort(arr, n);
    printf("After:  ");
    print_array(arr, n);
    
    // Selection Sort
    copy_array(original, arr, n);
    printf("\nSelection Sort:\n");
    printf("Before: ");
    print_array(arr, n);
    selection_sort(arr, n);
    printf("After:  ");
    print_array(arr, n);
    
    // Insertion Sort
    copy_array(original, arr, n);
    printf("\nInsertion Sort:\n");
    printf("Before: ");
    print_array(arr, n);
    insertion_sort(arr, n);
    printf("After:  ");
    print_array(arr, n);
}

void demonstrate_efficient_sorts() {
    printf("\n=== Efficient Sorting Algorithms ===\n");
    
    int original[] = {38, 27, 43, 3, 9, 82, 10, 1, 76, 15};
    int n = sizeof(original) / sizeof(original[0]);
    int arr[10];
    
    printf("Original array: ");
    print_array(original, n);
    
    // Merge Sort
    copy_array(original, arr, n);
    printf("\nMerge Sort:\n");
    printf("Before: ");
    print_array(arr, n);
    merge_sort(arr, 0, n - 1);
    printf("After:  ");
    print_array(arr, n);
    
    // Quick Sort
    copy_array(original, arr, n);
    printf("\nQuick Sort:\n");
    printf("Before: ");
    print_array(arr, n);
    quick_sort(arr, 0, n - 1);
    printf("After:  ");
    print_array(arr, n);
    
    // Heap Sort
    copy_array(original, arr, n);
    printf("\nHeap Sort:\n");
    printf("Before: ");
    print_array(arr, n);
    heap_sort(arr, n);
    printf("After:  ");
    print_array(arr, n);
}

void demonstrate_specialized_sorts() {
    printf("\n=== Specialized Sorting Algorithms ===\n");
    
    // Counting Sort
    int count_arr[] = {4, 2, 2, 8, 3, 3, 1, 7, 4, 1, 3};
    int count_n = sizeof(count_arr) / sizeof(count_arr[0]);
    
    printf("Counting Sort (for small range integers):\n");
    printf("Before: ");
    print_array(count_arr, count_n);
    counting_sort(count_arr, count_n, 8);
    printf("After:  ");
    print_array(count_arr, count_n);
    
    // Radix Sort
    int radix_arr[] = {170, 45, 75, 90, 2, 802, 24, 66};
    int radix_n = sizeof(radix_arr) / sizeof(radix_arr[0]);
    
    printf("\nRadix Sort (for integers):\n");
    printf("Before: ");
    print_array(radix_arr, radix_n);
    radix_sort(radix_arr, radix_n);
    printf("After:  ");
    print_array(radix_arr, radix_n);
    
    // Bucket Sort
    float bucket_arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int bucket_n = sizeof(bucket_arr) / sizeof(bucket_arr[0]);
    
    printf("\nBucket Sort (for floating point numbers in [0,1)):\n");
    printf("Before: ");
    for (int i = 0; i < bucket_n; i++) {
        printf("%.4f ", bucket_arr[i]);
    }
    printf("\n");
    bucket_sort(bucket_arr, bucket_n);
    printf("After:  ");
    for (int i = 0; i < bucket_n; i++) {
        printf("%.4f ", bucket_arr[i]);
    }
    printf("\n");
    
    // Shell Sort
    int shell_arr[] = {23, 29, 15, 19, 31, 7, 9, 5, 2};
    int shell_n = sizeof(shell_arr) / sizeof(shell_arr[0]);
    
    printf("\nShell Sort:\n");
    printf("Before: ");
    print_array(shell_arr, shell_n);
    shell_sort(shell_arr, shell_n);
    printf("After:  ");
    print_array(shell_arr, shell_n);
}

void demonstrate_performance_analysis() {
    printf("\n=== Performance Analysis ===\n");
    
    int sizes[] = {100, 500, 1000, 2000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    
    printf("Performance comparison (time in seconds):\n");
    printf("Size\tBubble\tSelection\tInsertion\tMerge\tQuick\tHeap\n");
    printf("----\t------\t---------\t---------\t-----\t-----\t----\n");
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int *arr = malloc(n * sizeof(int));
        int *temp = malloc(n * sizeof(int));
        
        // Generate random array
        srand(42);  // Fixed seed for consistent results
        for (int j = 0; j < n; j++) {
            arr[j] = rand() % 1000;
        }
        
        printf("%d\t", n);
        
        // Measure bubble sort
        copy_array(arr, temp, n);
        double time = measure_time_wrapper(bubble_sort, temp, n);
        printf("%.4f\t", time);
        
        // Measure selection sort
        copy_array(arr, temp, n);
        time = measure_time_wrapper(selection_sort, temp, n);
        printf("%.4f\t\t", time);
        
        // Measure insertion sort
        copy_array(arr, temp, n);
        time = measure_time_wrapper(insertion_sort, temp, n);
        printf("%.4f\t\t", time);
        
        // Measure merge sort
        copy_array(arr, temp, n);
        clock_t start = clock();
        merge_sort(temp, 0, n - 1);
        clock_t end = clock();
        time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%.4f\t", time);
        
        // Measure quick sort
        copy_array(arr, temp, n);
        start = clock();
        quick_sort(temp, 0, n - 1);
        end = clock();
        time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%.4f\t", time);
        
        // Measure heap sort
        copy_array(arr, temp, n);
        time = measure_time_wrapper(heap_sort, temp, n);
        printf("%.4f", time);
        
        printf("\n");
        
        free(arr);
        free(temp);
    }
}

void demonstrate_stability_analysis() {
    printf("\n=== Stability Analysis ===\n");
    
    // Create array with duplicate values to test stability
    struct KeyValue {
        int key;
        char value;
    };
    
    struct KeyValue arr[] = {{4, 'A'}, {2, 'B'}, {4, 'C'}, {2, 'D'}, {1, 'E'}};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array (key, value): ");
    for (int i = 0; i < n; i++) {
        printf("(%d,%c) ", arr[i].key, arr[i].value);
    }
    printf("\n");
    
    printf("\nStable sorts maintain relative order of equal elements:\n");
    printf("- Bubble Sort: Stable\n");
    printf("- Selection Sort: Unstable\n");
    printf("- Insertion Sort: Stable\n");
    printf("- Merge Sort: Stable\n");
    printf("- Quick Sort: Unstable (depends on partition)\n");
    printf("- Heap Sort: Unstable\n");
    printf("- Counting Sort: Stable\n");
    printf("- Radix Sort: Stable\n");
}

// Sorting Algorithm Implementations

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;  // Optimization: early termination
    }
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] > arr[largest])
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        
        heapify(arr, i, 0);
    }
}

void counting_sort(int arr[], int n, int max_val) {
    int *count = calloc(max_val + 1, sizeof(int));
    int *output = malloc(n * sizeof(int));
    
    // Count occurrences
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    
    // Cumulative count
    for (int i = 1; i <= max_val; i++) {
        count[i] += count[i - 1];
    }
    
    // Build output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    
    // Copy back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(count);
    free(output);
}

void counting_sort_for_radix(int arr[], int n, int exp) {
    int *output = malloc(n * sizeof(int));
    int count[10] = {0};
    
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(output);
}

void radix_sort(int arr[], int n) {
    int max = get_max(arr, n);
    
    for (int exp = 1; max / exp > 0; exp *= 10) {
        counting_sort_for_radix(arr, n, exp);
    }
}

void bucket_sort(float arr[], int n) {
    struct Node {
        float data;
        struct Node *next;
    };
    
    struct Node **buckets = calloc(n, sizeof(struct Node*));
    
    // Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int bucket_idx = (int)(n * arr[i]);
        
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->data = arr[i];
        new_node->next = NULL;
        
        if (!buckets[bucket_idx]) {
            buckets[bucket_idx] = new_node;
        } else {
            // Insert in sorted order
            if (new_node->data < buckets[bucket_idx]->data) {
                new_node->next = buckets[bucket_idx];
                buckets[bucket_idx] = new_node;
            } else {
                struct Node *current = buckets[bucket_idx];
                while (current->next && current->next->data < new_node->data) {
                    current = current->next;
                }
                new_node->next = current->next;
                current->next = new_node;
            }
        }
    }
    
    // Concatenate all buckets
    int index = 0;
    for (int i = 0; i < n; i++) {
        struct Node *current = buckets[i];
        while (current) {
            arr[index++] = current->data;
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(buckets);
}

void shell_sort(int arr[], int n) {
    // Start with a big gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            
            arr[j] = temp;
        }
    }
}

// Helper Functions

int get_max(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void copy_array(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

double measure_time_wrapper(void (*sort_func)(int[], int), int arr[], int n) {
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

bool is_sorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    printf("COMPLETE SORTING ALGORITHMS IMPLEMENTATION\n");
    printf("==========================================\n\n");
    
    demonstrate_simple_sorts();
    demonstrate_efficient_sorts();
    demonstrate_specialized_sorts();
    demonstrate_performance_analysis();
    demonstrate_stability_analysis();
    
    printf("\nSorting Algorithm Summary:\n");
    printf("=========================\n");
    printf("Algorithm     | Best Case | Average Case | Worst Case | Space | Stable\n");
    printf("--------------|-----------|--------------|------------|-------|--------\n");
    printf("Bubble Sort   | O(n)      | O(n²)        | O(n²)      | O(1)  | Yes\n");
    printf("Selection Sort| O(n²)     | O(n²)        | O(n²)      | O(1)  | No\n");
    printf("Insertion Sort| O(n)      | O(n²)        | O(n²)      | O(1)  | Yes\n");
    printf("Merge Sort    | O(n log n)| O(n log n)   | O(n log n) | O(n)  | Yes\n");
    printf("Quick Sort    | O(n log n)| O(n log n)   | O(n²)      | O(log n)| No\n");
    printf("Heap Sort     | O(n log n)| O(n log n)   | O(n log n) | O(1)  | No\n");
    printf("Counting Sort | O(n+k)    | O(n+k)       | O(n+k)     | O(k)  | Yes\n");
    printf("Radix Sort    | O(d(n+k)) | O(d(n+k))    | O(d(n+k))  | O(n+k)| Yes\n");
    printf("Bucket Sort   | O(n+k)    | O(n+k)       | O(n²)      | O(n)  | Yes\n");
    printf("Shell Sort    | O(n log n)| O(n^1.25)    | O(n²)      | O(1)  | No\n");
    
    return 0;
}


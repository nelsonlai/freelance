/*
 * C++ PROGRAMMING EXAMPLES EXAMPLES
 * 
 * This file demonstrates C++ programming concepts and techniques:
 * - Core concepts and syntax
 * - Practical examples and usage patterns
 * - Best practices and optimization techniques
 * - Real-world applications and scenarios
 * 
 * Learning Objectives:
 * - Understand fundamental C++ PROGRAMMING concepts
 * - Learn proper syntax and implementation
 * - Master different techniques and approaches
 * - Apply knowledge in practical scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and variables
 * - Familiarity with control structures
 * - Basic understanding of functions and classes
 * 
 * Key Topics Covered:
 * - Syntax and language features
 * - Implementation techniques
 * - Performance considerations
 * - Error handling and best practices
 * - Real-world applications
 */

/* Radix Sort
Time Complexity
Radix Sort runs in:

scss
Copy
Edit
O(d × (n + k))
Where:

n = number of elements

d = number of digits in the maximum number

k = range of digits (base, usually 10)

Space Complexity
O(n + k):

O(n) for the output array

O(k) for the count array (usually size 10 for base 10 digits)

https://visualgo.net/en/sorting

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// A utility function to get the maximum value in arr[]
int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

// A function to do counting sort of arr[] according to the digit represented by exp
void radixCount(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n); // output array
    int count[10] = {0};

    // Count occurrences of digits
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Convert count[i] to the actual position of this digit in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array (in reverse for stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the output[] back to arr[]
    arr = output;
}

// Main function to implement radix sort
void radixSort(vector<int>& arr) {
    int maxNum = getMax(arr);

    // Do counting sort for every digit (1s, 10s, 100s, etc.)
    for (int exp = 1; maxNum / exp > 0; exp *= 10)
        radixCount(arr, exp);
}

// Utility function to print the array
void printArray(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

// Test
int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    cout << "Original array: ";
    printArray(arr);

    radixSort(arr);

    cout << "Sorted array: ";
    printArray(arr);
    return 0;
}
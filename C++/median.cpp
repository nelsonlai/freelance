/*
 * MEDIAN OF TWO SORTED ARRAYS ALGORITHM
 * 
 * This file demonstrates the efficient algorithm for finding the median
 * of two sorted arrays using binary search approach:
 * - O(log(min(m,n))) time complexity solution
 * - Binary search on the smaller array
 * - Partition-based median finding
 * - Edge case handling for array boundaries
 * 
 * Learning Objectives:
 * - Understand the median of two sorted arrays problem
 * - Learn binary search application in complex problems
 * - Master partition-based algorithms
 * - Apply efficient algorithm design principles
 * - Develop problem-solving skills with advanced algorithms
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of arrays and binary search
 * - Familiarity with mathematical concepts (median)
 * - Basic understanding of algorithm complexity
 * 
 * Key Topics Covered:
 * - Median calculation algorithms
 * - Binary search optimization
 * - Array partitioning techniques
 * - Edge case handling
 * - Time complexity optimization
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <climits>   // For INT_MIN and INT_MAX constants
using namespace std; // Using standard namespace

/*
 * MEDIAN OF TWO SORTED ARRAYS - BINARY SEARCH APPROACH
 * 
 * This function finds the median of two sorted arrays using binary search.
 * The key insight is to partition both arrays such that the left half
 * contains the same number of elements as the right half.
 * 
 * Algorithm:
 * 1. Ensure the first array is smaller (swap if necessary)
 * 2. Use binary search on the smaller array to find the partition point
 * 3. Calculate corresponding partition in the larger array
 * 4. Check if the partition is correct (all left elements <= all right elements)
 * 5. Adjust search range based on comparison
 * 6. Return median based on total number of elements (odd/even)
 * 
 * @param nums1 First sorted array
 * @param m Size of first array
 * @param nums2 Second sorted array
 * @param n Size of second array
 * @return Median of the combined arrays
 */
double findMedianSortedArrays(int nums1[], int m, int nums2[], int n) {
    // Ensure nums1 is the smaller array for optimization
    // This reduces the binary search space to O(log(min(m,n)))
    if (m > n) {
        return findMedianSortedArrays(nums2, n, nums1, m);
    }

    // Binary search on the smaller array (nums1)
    int left = 0, right = m;  // Search range for partition point in nums1
    
    while (left <= right) {
        // Calculate partition points
        int i = (left + right) / 2;        // Partition point in nums1
        int j = (m + n + 1) / 2 - i;       // Corresponding partition point in nums2

        // Handle edge cases for array boundaries
        int maxLeftA  = (i == 0) ? INT_MIN : nums1[i - 1];  // Max element in left part of nums1
        int minRightA = (i == m) ? INT_MAX : nums1[i];       // Min element in right part of nums1
        int maxLeftB  = (j == 0) ? INT_MIN : nums2[j - 1];  // Max element in left part of nums2
        int minRightB = (j == n) ? INT_MAX : nums2[j];       // Min element in right part of nums2

        // Check if partition is correct
        if (maxLeftA <= minRightB && maxLeftB <= minRightA) {
            // Partition is correct, calculate median
            if ((m + n) % 2 == 0) {
                // Even total elements: median is average of two middle elements
                return (max(maxLeftA, maxLeftB) + min(minRightA, minRightB)) / 2.0;
            } else {
                // Odd total elements: median is the maximum of left parts
                return max(maxLeftA, maxLeftB);
            }
        } else if (maxLeftA > minRightB) {
            // Partition is too far right, search left half
            right = i - 1;
        } else {
            // Partition is too far left, search right half
            left = i + 1;
        }
    }

    return -1.0; // Should never happen for valid input
}

/*
 * MAIN FUNCTION - MEDIAN ALGORITHM DEMONSTRATION
 * 
 * This function demonstrates the median finding algorithm with test cases.
 * It shows how the algorithm works with different array sizes and values.
 */
int main() {
    cout << "=== MEDIAN OF TWO SORTED ARRAYS DEMONSTRATION ===" << endl << endl;
    
    /*
     * TEST CASE 1: ODD TOTAL ELEMENTS
     * 
     * Array 1: [1, 3] (2 elements)
     * Array 2: [2] (1 element)
     * Combined: [1, 2, 3] (3 elements)
     * Expected median: 2 (middle element)
     */
    cout << "Test Case 1 - Odd total elements:" << endl;
    int nums1[] = {1, 3};  // First sorted array
    int nums2[] = {2};     // Second sorted array
    int m = sizeof(nums1) / sizeof(nums1[0]);  // Calculate size of nums1
    int n = sizeof(nums2) / sizeof(nums2[0]);  // Calculate size of nums2
    
    cout << "Array 1: [1, 3], Array 2: [2]" << endl;
    cout << "Median: " << findMedianSortedArrays(nums1, m, nums2, n) << endl;
    cout << "Expected: 2.0" << endl << endl;
    
    /*
     * TEST CASE 2: EVEN TOTAL ELEMENTS
     * 
     * Array 1: [1, 2] (2 elements)
     * Array 2: [3, 4] (2 elements)
     * Combined: [1, 2, 3, 4] (4 elements)
     * Expected median: 2.5 (average of middle elements: (2+3)/2)
     */
    cout << "Test Case 2 - Even total elements:" << endl;
    int nums3[] = {1, 2};  // First sorted array
    int nums4[] = {3, 4};  // Second sorted array
    m = sizeof(nums3) / sizeof(nums3[0]);  // Calculate size of nums3
    n = sizeof(nums4) / sizeof(nums4[0]);  // Calculate size of nums4
    
    cout << "Array 1: [1, 2], Array 2: [3, 4]" << endl;
    cout << "Median: " << findMedianSortedArrays(nums3, m, nums4, n) << endl;
    cout << "Expected: 2.5" << endl << endl;
    
    // Return 0 to indicate successful program execution
    return 0;
}
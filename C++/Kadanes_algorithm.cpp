/*
 * KADANE'S ALGORITHM IMPLEMENTATION
 * 
 * This file demonstrates Kadane's algorithm for finding the maximum subarray sum:
 * - Dynamic programming approach
 * - Optimal subarray problem solution
 * - Time complexity O(n) implementation
 * - Subarray tracking and extraction
 * - Modern C++ features (structured bindings)
 * 
 * Learning Objectives:
 * - Understand the maximum subarray problem
 * - Learn Kadane's algorithm implementation
 * - Master dynamic programming concepts
 * - Apply optimal subarray techniques
 * - Develop problem-solving skills with algorithms
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of arrays and vectors
 * - Familiarity with loops and conditionals
 * - Basic understanding of algorithms and complexity
 * 
 * Key Topics Covered:
 * - Kadane's algorithm
 * - Dynamic programming
 * - Subarray problems
 * - Time complexity optimization
 * - Modern C++ features
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <vector>    // For vector container
using namespace std; // Using standard namespace

/*
 * KADANE'S ALGORITHM - MAXIMUM SUBARRAY SUM
 * 
 * This function implements Kadane's algorithm to find the maximum sum of any contiguous subarray.
 * It also tracks the indices of the subarray to return both the sum and the actual subarray.
 * 
 * Algorithm:
 * 1. Initialize maxSum and currentSum to first element
 * 2. For each element, decide whether to start a new subarray or extend current one
 * 3. Update maxSum if current subarray sum is greater
 * 4. Track start and end indices of the maximum subarray
 * 
 * @param nums The input array of integers
 * @return A pair containing (maxSum, subarray) where subarray is the actual maximum subarray
 */
pair<int, vector<int>> maxSubarraySum(const vector<int>& nums) {
    // Handle edge case: empty array
    if (nums.empty()) return {0, {}};

    // Initialize variables for tracking maximum subarray
    int maxSum = nums[0];      // Maximum sum found so far
    int currentSum = nums[0];  // Sum of current subarray
    int start = 0;             // Start index of maximum subarray
    int end = 0;               // End index of maximum subarray
    int tempStart = 0;         // Temporary start for current subarray

    // Iterate through array starting from second element
    for (int i = 1; i < nums.size(); ++i) {
        // If current sum is negative, start a new subarray from current element
        if (currentSum < 0) {
            currentSum = nums[i];  // Start new subarray with current element
            tempStart = i;         // Update temporary start index
        } else {
            // Extend current subarray by adding current element
            currentSum += nums[i];
        }

        // Update maximum sum and indices if current subarray is better
        if (currentSum > maxSum) {
            maxSum = currentSum;    // Update maximum sum
            start = tempStart;      // Update start index
            end = i;                // Update end index
        }
    }

    // Extract the actual subarray using the found indices
    vector<int> subarray(nums.begin() + start, nums.begin() + end + 1);
    
    // Return both the maximum sum and the subarray
    return {maxSum, subarray};
}

/*
 * MAIN FUNCTION - KADANE'S ALGORITHM DEMONSTRATION
 * 
 * This function demonstrates Kadane's algorithm with a sample array.
 * It shows both the maximum sum and the actual subarray that produces this sum.
 */
int main() {
    // Sample array for testing Kadane's algorithm
    vector<int> nums = {-2, 11, -4, 13, -5, 2};
    
    // Apply Kadane's algorithm using structured binding (C++17 feature)
    auto [maxSum, subarray] = maxSubarraySum(nums);

    // Display the results
    cout << "Maximum Sum: " << maxSum << endl;
    cout << "Subsequence: ";
    
    // Print the actual subarray that produces the maximum sum
    for (int num : subarray) {
        cout << num << " ";
    }
    cout << endl;

    // Return 0 to indicate successful program execution
    return 0;
}
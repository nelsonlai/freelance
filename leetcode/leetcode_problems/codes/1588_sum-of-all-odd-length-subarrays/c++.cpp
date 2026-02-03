/*
 * Problem: Sum of All Odd Length Subarrays
 * Difficulty: Easy
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            int left = i + 1;
            int right = n - i;
            int oddLeft = (left + 1) / 2;
            int oddRight = (right + 1) / 2;
            int evenLeft = left / 2;
            int evenRight = right / 2;
            
            result += arr[i] * (oddLeft * oddRight + evenLeft * evenRight);
        }
        
        return result;
    }
};
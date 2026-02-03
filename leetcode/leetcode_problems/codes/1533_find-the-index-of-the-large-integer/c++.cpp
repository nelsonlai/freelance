/*
 * Problem: Find the Index of the Large Integer
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares the sum of arr[l..r] with the sum of arr[x..y] 
 *     // return 1 if sum(arr[l..r]) > sum(arr[x..y])
 *     // return 0 if sum(arr[l..r]) == sum(arr[x..y])
 *     // return -1 if sum(arr[l..r]) < sum(arr[x..y])
 *     int compareSub(int l, int r, int x, int y);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class Solution {
public:
    int getIndex(ArrayReader &reader) {
        int n = reader.length();
        int left = 0, right = n - 1;
        
        while (left < right) {
            int mid = (left + right) / 2;
            int length = right - left + 1;
            
            if (length % 2 == 1) {
                int cmp = reader.compareSub(left, mid - 1, mid + 1, right);
                if (cmp == 0) {
                    return mid;
                } else if (cmp > 0) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                int cmp = reader.compareSub(left, mid, mid + 1, right);
                if (cmp > 0) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
        }
        
        return left;
    }
};
/**
 * Problem: Find the Index of the Large Integer
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Binary search - compare left and right halves, narrow down to the half with larger sum
 * Time Complexity: O(log n) where n is array length
 * Space Complexity: O(1)
 */

/**
 * // This is ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * interface ArrayReader {
 *     // Compares the sum of arr[l..r] with the sum of arr[x..y] 
 *     // return 1 if sum(arr[l..r]) > sum(arr[x..y])
 *     // return 0 if sum(arr[l..r]) == sum(arr[x..y])
 *     // return -1 if sum(arr[l..r]) < sum(arr[x..y])
 *     public int compareSub(int l, int r, int x, int y);
 *
 *     // Returns the length of the array
 *     public int length();
 * }
 */

class Solution {
    public int getIndex(ArrayReader reader) {
        int n = reader.length();
        int left = 0, right = n - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
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
}
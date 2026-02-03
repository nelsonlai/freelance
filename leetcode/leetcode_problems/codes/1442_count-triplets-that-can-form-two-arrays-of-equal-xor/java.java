/**
 * Problem: Count Triplets That Can Form Two Arrays of Equal XOR
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: If a[i]^...^a[j-1] == a[j]^...^a[k], then prefix[i] == prefix[k+1]
 * Time Complexity: O(n^2) where n is length of arr
 * Space Complexity: O(n) for prefix
 */

class Solution {
    public int countTriplets(int[] arr) {
        int n = arr.length;
        int[] prefix = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] ^ arr[i];
        }
        
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int k = i + 1; k < n; k++) {
                if (prefix[i] == prefix[k + 1]) {
                    count += k - i;
                }
            }
        }
        
        return count;
    }
}
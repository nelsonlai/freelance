/*
 * Problem: Permutation Sequence
 * Difficulty: Hard
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Collections.Generic;
using System.Text;

public class Solution {
    public string GetPermutation(int n, int k) {
        List<int> nums = new List<int>();
        for (int i = 1; i <= n; i++) {
            nums.Add(i);
        }
        
        int[] fact = new int[n];
        fact[0] = 1;
        for (int i = 1; i < n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        
        k--; // Convert to 0-indexed
        StringBuilder result = new StringBuilder();
        
        for (int i = n - 1; i >= 0; i--) {
            int index = k / fact[i];
            result.Append(nums[index]);
            nums.RemoveAt(index);
            k %= fact[i];
        }
        
        return result.ToString();
    }
}
/**
 * Problem: Permutation Sequence
 * Difficulty: Hard
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String getPermutation(int n, int k) {
        List<Integer> nums = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            nums.add(i);
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
            result.append(nums.remove(index));
            k %= fact[i];
        }
        
        return result.toString();
    }
}
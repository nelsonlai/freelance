/**
 * Problem: Count Subarrays With More Ones Than Zeros
 * Difficulty: Medium
 * Tags: array, hash, prefix sum, binary indexed tree
 * 
 * Approach: Use prefix sum and BIT/Fenwick tree to count valid subarrays
 * Time Complexity: O(n log n) where n is length
 * Space Complexity: O(n)
 */

class FenwickTree {
    private int size;
    private int[] tree;
    
    public FenwickTree(int size) {
        this.size = size;
        this.tree = new int[size + 1];
    }
    
    public void update(int index, int delta) {
        index++;
        while (index <= size) {
            tree[index] += delta;
            index += index & -index;
        }
    }
    
    public int query(int index) {
        index++;
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= index & -index;
        }
        return result;
    }
}

class Solution {
    public int subarraysWithMoreOnesThanZeroes(int[] nums) {
        int n = nums.length;
        int MOD = 1000000007;
        
        // Convert to prefix sum: 1 -> +1, 0 -> -1
        int[] prefix = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + (nums[i] == 1 ? 1 : -1);
        }
        
        // Normalize prefix values for BIT (shift to non-negative)
        int minPrefix = Integer.MAX_VALUE;
        for (int p : prefix) {
            minPrefix = Math.min(minPrefix, p);
        }
        int shift = -minPrefix + 1;
        
        // Use BIT to count valid subarrays
        int maxVal = 0;
        for (int p : prefix) {
            maxVal = Math.max(maxVal, p + shift);
        }
        FenwickTree bit = new FenwickTree(maxVal + 1);
        
        long result = 0;
        bit.update(0 + shift, 1);  // prefix[0] = 0
        
        for (int i = 1; i <= n; i++) {
            // Count how many prefix[j] < prefix[i] where j < i
            int count = bit.query(prefix[i] + shift - 1);
            result = (result + count) % MOD;
            bit.update(prefix[i] + shift, 1);
        }
        
        return (int) result;
    }
}
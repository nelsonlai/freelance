/**
 * Problem: Dot Product of Two Sparse Vectors
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class SparseVector {
    private Map<Integer, Integer> nonZero;
    
    SparseVector(int[] nums) {
        nonZero = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] != 0) {
                nonZero.put(i, nums[i]);
            }
        }
    }
    
	// Return the dotProduct of two sparse vectors
    public int dotProduct(SparseVector vec) {
        int result = 0;
        for (Map.Entry<Integer, Integer> entry : nonZero.entrySet()) {
            int idx = entry.getKey();
            int val = entry.getValue();
            if (vec.nonZero.containsKey(idx)) {
                result += val * vec.nonZero.get(idx);
            }
        }
        return result;
    }
}

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1 = new SparseVector(nums1);
// SparseVector v2 = new SparseVector(nums2);
// int ans = v1.dotProduct(v2);
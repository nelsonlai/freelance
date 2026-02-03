/**
 * Problem: Non-decreasing Subsequences
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public List<List<Integer>> findSubsequences(int[] nums) {
        Set<List<Integer>> result = new HashSet<>();
        backtrack(0, nums, new ArrayList<>(), result);
        return new ArrayList<>(result);
    }
    
    private void backtrack(int index, int[] nums, List<Integer> sequence, Set<List<Integer>> result) {
        if (sequence.size() >= 2) {
            result.add(new ArrayList<>(sequence));
        }
        
        for (int i = index; i < nums.length; i++) {
            if (sequence.isEmpty() || nums[i] >= sequence.get(sequence.size() - 1)) {
                sequence.add(nums[i]);
                backtrack(i + 1, nums, sequence, result);
                sequence.remove(sequence.size() - 1);
            }
        }
    }
}
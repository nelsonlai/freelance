/**
 * Problem: Combination Sum III
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<List<Integer>> combinationSum3(int k, int n) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(1, k, n, new ArrayList<>(), result);
        return result;
    }
    
    private void backtrack(int start, int k, int remaining, List<Integer> path, List<List<Integer>> result) {
        if (path.size() == k && remaining == 0) {
            result.add(new ArrayList<>(path));
            return;
        }
        
        if (path.size() >= k || remaining < 0) {
            return;
        }
        
        for (int i = start; i <= 9; i++) {
            path.add(i);
            backtrack(i + 1, k, remaining - i, path, result);
            path.remove(path.size() - 1);
        }
    }
}
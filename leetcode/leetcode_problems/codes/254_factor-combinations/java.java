/**
 * Problem: Factor Combinations
 * Difficulty: Medium
 * Tags: general
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<List<Integer>> getFactors(int n) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(2, n, new ArrayList<>(), result);
        return result;
    }
    
    private void backtrack(int start, int target, List<Integer> path, List<List<Integer>> result) {
        if (target == 1 && path.size() > 1) {
            result.add(new ArrayList<>(path));
            return;
        }
        
        for (int i = start; i * i <= target; i++) {
            if (target % i == 0) {
                path.add(i);
                backtrack(i, target / i, path, result);
                path.remove(path.size() - 1);
            }
        }
        
        if (target >= start) {
            path.add(target);
            backtrack(target, 1, path, result);
            path.remove(path.size() - 1);
        }
    }
}
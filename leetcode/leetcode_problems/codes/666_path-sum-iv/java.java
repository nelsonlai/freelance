/**
 * Problem: Path Sum IV
 * Difficulty: Medium
 * Tags: array, tree, hash, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int pathSum(int[] nums) {
        Map<String, Integer> tree = new HashMap<>();
        for (int num : nums) {
            int depth = num / 100;
            int pos = (num / 10) % 10;
            int val = num % 10;
            tree.put(depth + "," + pos, val);
        }
        
        int[] result = {0};
        dfs(tree, 1, 1, 0, result);
        return result[0];
    }
    
    private void dfs(Map<String, Integer> tree, int depth, int pos, int pathSum, int[] result) {
        String key = depth + "," + pos;
        if (!tree.containsKey(key)) {
            return;
        }
        
        pathSum += tree.get(key);
        
        String leftKey = (depth + 1) + "," + (2 * pos - 1);
        String rightKey = (depth + 1) + "," + (2 * pos);
        
        if (!tree.containsKey(leftKey) && !tree.containsKey(rightKey)) {
            result[0] += pathSum;
            return;
        }
        
        if (tree.containsKey(leftKey)) {
            dfs(tree, depth + 1, 2 * pos - 1, pathSum, result);
        }
        if (tree.containsKey(rightKey)) {
            dfs(tree, depth + 1, 2 * pos, pathSum, result);
        }
    }
}
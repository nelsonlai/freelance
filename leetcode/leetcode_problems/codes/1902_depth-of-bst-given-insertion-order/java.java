/**
 * Problem: Depth of BST Given Insertion Order
 * Difficulty: Medium
 * Tags: array, tree, search, binary search tree
 * 
 * Approach: Use TreeMap-like structure with binary search to track depths
 * Time Complexity: O(n log n) worst case
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int maxDepthBST(int[] order) {
        Map<Integer, Integer> depths = new HashMap<>();
        List<Integer> sortedKeys = new ArrayList<>();
        int maxDepth = 0;
        
        for (int val : order) {
            int pos = Collections.binarySearch(sortedKeys, val);
            if (pos < 0) {
                pos = -pos - 1;
            }
            
            int depth = 1;
            if (pos > 0) {
                int leftKey = sortedKeys.get(pos - 1);
                depth = Math.max(depth, depths.get(leftKey) + 1);
            }
            if (pos < sortedKeys.size()) {
                int rightKey = sortedKeys.get(pos);
                depth = Math.max(depth, depths.get(rightKey) + 1);
            }
            
            sortedKeys.add(pos, val);
            depths.put(val, depth);
            maxDepth = Math.max(maxDepth, depth);
        }
        
        return maxDepth;
    }
}
/**
 * Problem: Erect the Fence
 * Difficulty: Hard
 * Tags: array, tree, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int[][] outerTrees(int[][] trees) {
        Arrays.sort(trees, (a, b) -> a[0] == b[0] ? a[1] - b[1] : a[0] - b[0]);
        
        List<int[]> lower = new ArrayList<>();
        for (int[] tree : trees) {
            while (lower.size() >= 2 && cross(lower.get(lower.size()-2), lower.get(lower.size()-1), tree) < 0) {
                lower.remove(lower.size() - 1);
            }
            lower.add(tree);
        }
        
        List<int[]> upper = new ArrayList<>();
        for (int i = trees.length - 1; i >= 0; i--) {
            while (upper.size() >= 2 && cross(upper.get(upper.size()-2), upper.get(upper.size()-1), trees[i]) < 0) {
                upper.remove(upper.size() - 1);
            }
            upper.add(trees[i]);
        }
        
        Set<int[]> result = new HashSet<>();
        for (int i = 0; i < lower.size() - 1; i++) {
            result.add(lower.get(i));
        }
        for (int i = 0; i < upper.size() - 1; i++) {
            result.add(upper.get(i));
        }
        
        return result.toArray(new int[result.size()][]);
    }
    
    private int cross(int[] o, int[] a, int[] b) {
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]);
    }
}
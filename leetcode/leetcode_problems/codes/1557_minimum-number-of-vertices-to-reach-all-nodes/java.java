/**
 * Problem: Minimum Number of Vertices to Reach All Nodes
 * Difficulty: Medium
 * Tags: array, graph
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<Integer> findSmallestSetOfVertices(int n, List<List<Integer>> edges) {
        Set<Integer> hasIncoming = new HashSet<>();
        for (List<Integer> edge : edges) {
            hasIncoming.add(edge.get(1));
        }
        
        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (!hasIncoming.contains(i)) {
                result.add(i);
            }
        }
        return result;
    }
}
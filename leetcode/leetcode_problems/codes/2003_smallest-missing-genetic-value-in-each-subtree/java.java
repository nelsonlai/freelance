/**
 * Problem: Smallest Missing Genetic Value in Each Subtree
 * Difficulty: Hard
 * Tags: array, tree, graph, DFS
 * 
 * Approach: DFS to collect values in each subtree, find smallest missing value
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int[] smallestMissingValueSubtree(int[] parents, int[] nums) {
        int n = parents.length;
        List<List<Integer>> children = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            children.add(new ArrayList<>());
        }
        
        // Build tree
        for (int i = 1; i < n; i++) {
            children.get(parents[i]).add(i);
        }
        
        int[] result = new int[n];
        Arrays.fill(result, 1);
        
        // Find node with value 1 (if exists)
        int nodeWithOne = -1;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                nodeWithOne = i;
                break;
            }
        }
        
        if (nodeWithOne == -1) {
            return result;
        }
        
        // Collect all values in path from nodeWithOne to root
        Set<Integer> visited = new HashSet<>();
        int current = nodeWithOne;
        int missing = 1;
        
        while (current != -1) {
            // DFS to collect all values in subtree of current
            Set<Integer> subtreeValues = new HashSet<>();
            Stack<Integer> stack = new Stack<>();
            stack.push(current);
            
            while (!stack.isEmpty()) {
                int node = stack.pop();
                if (visited.contains(node)) {
                    continue;
                }
                visited.add(node);
                subtreeValues.add(nums[node]);
                
                for (int child : children.get(node)) {
                    if (!visited.contains(child)) {
                        stack.push(child);
                    }
                }
            }
            
            // Find smallest missing value
            while (subtreeValues.contains(missing)) {
                missing++;
            }
            
            result[current] = missing;
            current = (current < n) ? parents[current] : -1;
        }
        
        return result;
    }
}
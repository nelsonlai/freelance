/**
 * Problem: Sequence Reconstruction
 * Difficulty: Medium
 * Tags: array, graph, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public boolean sequenceReconstruction(int[] nums, List<List<Integer>> sequences) {
        Map<Integer, List<Integer>> graph = new HashMap<>();
        Map<Integer, Integer> inDegree = new HashMap<>();
        
        for (List<Integer> seq : sequences) {
            for (int i = 0; i < seq.size() - 1; i++) {
                graph.putIfAbsent(seq.get(i), new ArrayList<>());
                graph.get(seq.get(i)).add(seq.get(i + 1));
                inDegree.put(seq.get(i + 1), inDegree.getOrDefault(seq.get(i + 1), 0) + 1);
                inDegree.putIfAbsent(seq.get(i), 0);
            }
        }
        
        Queue<Integer> queue = new LinkedList<>();
        for (int num : nums) {
            if (inDegree.getOrDefault(num, 0) == 0) {
                queue.offer(num);
            }
        }
        
        List<Integer> result = new ArrayList<>();
        while (!queue.isEmpty()) {
            if (queue.size() > 1) {
                return false;
            }
            int node = queue.poll();
            result.add(node);
            
            if (graph.containsKey(node)) {
                for (int neighbor : graph.get(node)) {
                    inDegree.put(neighbor, inDegree.get(neighbor) - 1);
                    if (inDegree.get(neighbor) == 0) {
                        queue.offer(neighbor);
                    }
                }
            }
        }
        
        if (result.size() != nums.length) {
            return false;
        }
        
        for (int i = 0; i < nums.length; i++) {
            if (result.get(i) != nums[i]) {
                return false;
            }
        }
        
        return true;
    }
}
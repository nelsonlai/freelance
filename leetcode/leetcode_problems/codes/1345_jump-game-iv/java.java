/**
 * Problem: Jump Game IV
 * Difficulty: Hard
 * Tags: array, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int minJumps(int[] arr) {
        int n = arr.length;
        if (n == 1) {
            return 0;
        }
        
        Map<Integer, List<Integer>> valueToIndices = new HashMap<>();
        for (int i = 0; i < n; i++) {
            valueToIndices.putIfAbsent(arr[i], new ArrayList<>());
            valueToIndices.get(arr[i]).add(i);
        }
        
        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> visited = new HashSet<>();
        queue.offer(0);
        visited.add(0);
        int steps = 0;
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int curr = queue.poll();
                
                if (curr == n - 1) {
                    return steps;
                }
                
                // Check neighbors
                if (curr - 1 >= 0 && !visited.contains(curr - 1)) {
                    visited.add(curr - 1);
                    queue.offer(curr - 1);
                }
                if (curr + 1 < n && !visited.contains(curr + 1)) {
                    visited.add(curr + 1);
                    queue.offer(curr + 1);
                }
                
                // Check same values
                if (valueToIndices.containsKey(arr[curr])) {
                    for (int neighbor : valueToIndices.get(arr[curr])) {
                        if (!visited.contains(neighbor)) {
                            visited.add(neighbor);
                            queue.offer(neighbor);
                        }
                    }
                    valueToIndices.remove(arr[curr]);
                }
            }
            steps++;
        }
        
        return steps;
    }
}
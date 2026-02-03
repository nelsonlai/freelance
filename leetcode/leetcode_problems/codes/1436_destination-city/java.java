/**
 * Problem: Destination City
 * Difficulty: Easy
 * Tags: array, string, graph, hash
 * 
 * Approach: Find city that appears only as destination (not as source)
 * Time Complexity: O(n) where n is number of paths
 * Space Complexity: O(n) for sources set
 */

import java.util.*;

class Solution {
    public String destCity(List<List<String>> paths) {
        Set<String> sources = new HashSet<>();
        for (List<String> path : paths) {
            sources.add(path.get(0));
        }
        
        for (List<String> path : paths) {
            if (!sources.contains(path.get(1))) {
                return path.get(1);
            }
        }
        
        return "";
    }
}
/**
 * Problem: Evaluate Division
 * Difficulty: Medium
 * Tags: array, string, graph, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public double[] calcEquation(List<List<String>> equations, double[] values, List<List<String>> queries) {
        Map<String, Map<String, Double>> graph = new HashMap<>();
        
        for (int i = 0; i < equations.size(); i++) {
            String a = equations.get(i).get(0);
            String b = equations.get(i).get(1);
            double value = values[i];
            
            graph.putIfAbsent(a, new HashMap<>());
            graph.putIfAbsent(b, new HashMap<>());
            graph.get(a).put(b, value);
            graph.get(b).put(a, 1.0 / value);
        }
        
        double[] results = new double[queries.size()];
        for (int i = 0; i < queries.size(); i++) {
            results[i] = dfs(queries.get(i).get(0), queries.get(i).get(1), graph, new HashSet<>());
        }
        
        return results;
    }
    
    private double dfs(String start, String end, Map<String, Map<String, Double>> graph, Set<String> visited) {
        if (!graph.containsKey(start) || !graph.containsKey(end)) {
            return -1.0;
        }
        
        if (graph.get(start).containsKey(end)) {
            return graph.get(start).get(end);
        }
        
        visited.add(start);
        for (Map.Entry<String, Double> entry : graph.get(start).entrySet()) {
            String neighbor = entry.getKey();
            double value = entry.getValue();
            if (!visited.contains(neighbor)) {
                double result = dfs(neighbor, end, graph, visited);
                if (result != -1.0) {
                    return value * result;
                }
            }
        }
        visited.remove(start);
        
        return -1.0;
    }
}
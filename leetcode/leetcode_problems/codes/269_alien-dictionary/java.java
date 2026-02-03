/**
 * Problem: Alien Dictionary
 * Difficulty: Hard
 * Tags: array, string, graph, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String alienOrder(String[] words) {
        Map<Character, Set<Character>> graph = new HashMap<>();
        Map<Character, Integer> indegree = new HashMap<>();
        
        for (String word : words) {
            for (char c : word.toCharArray()) {
                indegree.put(c, 0);
            }
        }
        
        for (int i = 0; i < words.length - 1; i++) {
            String word1 = words[i];
            String word2 = words[i + 1];
            
            if (word1.length() > word2.length() && word1.startsWith(word2)) {
                return "";
            }
            
            for (int j = 0; j < Math.min(word1.length(), word2.length()); j++) {
                if (word1.charAt(j) != word2.charAt(j)) {
                    char from = word1.charAt(j);
                    char to = word2.charAt(j);
                    
                    graph.putIfAbsent(from, new HashSet<>());
                    if (!graph.get(from).contains(to)) {
                        graph.get(from).add(to);
                        indegree.put(to, indegree.get(to) + 1);
                    }
                    break;
                }
            }
        }
        
        Queue<Character> queue = new LinkedList<>();
        for (char c : indegree.keySet()) {
            if (indegree.get(c) == 0) {
                queue.offer(c);
            }
        }
        
        StringBuilder result = new StringBuilder();
        while (!queue.isEmpty()) {
            char c = queue.poll();
            result.append(c);
            
            if (graph.containsKey(c)) {
                for (char neighbor : graph.get(c)) {
                    indegree.put(neighbor, indegree.get(neighbor) - 1);
                    if (indegree.get(neighbor) == 0) {
                        queue.offer(neighbor);
                    }
                }
            }
        }
        
        return result.length() == indegree.size() ? result.toString() : "";
    }
}
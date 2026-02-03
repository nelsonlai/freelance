/**
 * Problem: Top K Frequent Words
 * Difficulty: Medium
 * Tags: array, string, graph, hash, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public List<String> topKFrequent(String[] words, int k) {
        Map<String, Integer> count = new HashMap<>();
        for (String word : words) {
            count.put(word, count.getOrDefault(word, 0) + 1);
        }
        
        PriorityQueue<Map.Entry<String, Integer>> heap = new PriorityQueue<>(
            (a, b) -> a.getValue().equals(b.getValue()) ? 
                b.getKey().compareTo(a.getKey()) : a.getValue() - b.getValue()
        );
        
        for (Map.Entry<String, Integer> entry : count.entrySet()) {
            heap.offer(entry);
            if (heap.size() > k) {
                heap.poll();
            }
        }
        
        List<String> result = new ArrayList<>();
        while (!heap.isEmpty()) {
            result.add(heap.poll().getKey());
        }
        Collections.reverse(result);
        
        return result;
    }
}
/**
 * Problem: Rearrange String k Distance Apart
 * Difficulty: Hard
 * Tags: string, greedy, hash, sort, queue, heap
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public String rearrangeString(String s, int k) {
        if (k == 0) {
            return s;
        }
        
        Map<Character, Integer> count = new HashMap<>();
        for (char c : s.toCharArray()) {
            count.put(c, count.getOrDefault(c, 0) + 1);
        }
        
        PriorityQueue<Map.Entry<Character, Integer>> heap = 
            new PriorityQueue<>((a, b) -> b.getValue() - a.getValue());
        heap.addAll(count.entrySet());
        
        StringBuilder result = new StringBuilder();
        Queue<Map.Entry<Character, Integer>> waitQueue = new LinkedList<>();
        
        while (!heap.isEmpty()) {
            Map.Entry<Character, Integer> entry = heap.poll();
            result.append(entry.getKey());
            entry.setValue(entry.getValue() - 1);
            
            if (entry.getValue() > 0) {
                waitQueue.offer(entry);
            }
            
            if (waitQueue.size() >= k) {
                heap.offer(waitQueue.poll());
            }
        }
        
        return waitQueue.isEmpty() && result.length() == s.length() ? result.toString() : "";
    }
}
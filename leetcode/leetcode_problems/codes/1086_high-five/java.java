/**
 * Problem: High Five
 * Difficulty: Easy
 * Tags: array, hash, sort, queue, heap
 * 
 * Approach: Group by student, keep top 5 scores, calculate average
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for scores
 */

import java.util.*;

class Solution {
    public int[][] highFive(int[][] items) {
        Map<Integer, PriorityQueue<Integer>> scores = new HashMap<>();
        
        for (int[] item : items) {
            int studentId = item[0];
            int score = item[1];
            scores.putIfAbsent(studentId, new PriorityQueue<>());
            PriorityQueue<Integer> heap = scores.get(studentId);
            heap.offer(score);
            if (heap.size() > 5) {
                heap.poll();
            }
        }
        
        List<int[]> result = new ArrayList<>();
        for (int studentId : new TreeSet<>(scores.keySet())) {
            PriorityQueue<Integer> heap = scores.get(studentId);
            int sum = 0;
            while (!heap.isEmpty()) {
                sum += heap.poll();
            }
            result.add(new int[]{studentId, sum / 5});
        }
        
        return result.toArray(new int[result.size()][]);
    }
}
/**
 * Problem: Course Schedule III
 * Difficulty: Hard
 * Tags: array, greedy, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int scheduleCourse(int[][] courses) {
        Arrays.sort(courses, (a, b) -> a[1] - b[1]);
        PriorityQueue<Integer> heap = new PriorityQueue<>((a, b) -> b - a);
        int time = 0;
        
        for (int[] course : courses) {
            time += course[0];
            heap.offer(course[0]);
            
            if (time > course[1]) {
                time -= heap.poll();
            }
        }
        
        return heap.size();
    }
}
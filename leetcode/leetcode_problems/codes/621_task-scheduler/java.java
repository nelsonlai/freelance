/**
 * Problem: Task Scheduler
 * Difficulty: Medium
 * Tags: array, greedy, hash, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int leastInterval(char[] tasks, int n) {
        int[] count = new int[26];
        for (char task : tasks) {
            count[task - 'A']++;
        }
        
        Arrays.sort(count);
        int maxCount = count[25];
        int maxCountTasks = 0;
        for (int c : count) {
            if (c == maxCount) {
                maxCountTasks++;
            }
        }
        
        return Math.max(tasks.length, (maxCount - 1) * (n + 1) + maxCountTasks);
    }
}
/**
 * Problem: Process Tasks Using Servers
 * Difficulty: Medium
 * Tags: array, queue, heap
 * 
 * Approach: Use two heaps - available servers and busy servers
 * Time Complexity: O(m log n) where m is tasks, n is servers
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int[] assignTasks(int[] servers, int[] tasks) {
        PriorityQueue<int[]> available = new PriorityQueue<>((a, b) -> 
            a[0] != b[0] ? Integer.compare(a[0], b[0]) : Integer.compare(a[1], b[1]));
        for (int i = 0; i < servers.length; i++) {
            available.offer(new int[]{servers[i], i});
        }
        
        PriorityQueue<int[]> busy = new PriorityQueue<>((a, b) -> 
            a[0] != b[0] ? Integer.compare(a[0], b[0]) : 
            (a[1] != b[1] ? Integer.compare(a[1], b[1]) : Integer.compare(a[2], b[2])));
        
        int[] result = new int[tasks.length];
        long time = 0;
        
        for (int i = 0; i < tasks.length; i++) {
            time = Math.max(time, i);
            
            while (!busy.isEmpty() && busy.peek()[0] <= time) {
                int[] server = busy.poll();
                available.offer(new int[]{server[1], server[2]});
            }
            
            if (!available.isEmpty()) {
                int[] server = available.poll();
                result[i] = server[1];
                busy.offer(new int[]{(int)(time + tasks[i]), server[0], server[1]});
            } else {
                int[] server = busy.poll();
                time = server[0];
                result[i] = server[2];
                busy.offer(new int[]{(int)(time + tasks[i]), server[1], server[2]});
            }
        }
        
        return result;
    }
}
/**
 * Problem: Parallel Courses III
 * Difficulty: Hard
 * Tags: array, graph, dp, topological sort
 * 
 * Approach: Topological sort with DP - calculate max time to complete each course
 * Time Complexity: O(n + m) where n is courses, m is relations
 * Space Complexity: O(n + m)
 */

import java.util.*;

class Solution {
    public int minimumTime(int n, int[][] relations, int[] time) {
        List<List<Integer>> graph = new ArrayList<>();
        int[] inDegree = new int[n + 1];
        
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int[] relation : relations) {
            int prev = relation[0];
            int next = relation[1];
            graph.get(prev).add(next);
            inDegree[next]++;
        }
        
        // dp[i] = minimum time to complete course i
        int[] dp = new int[n + 1];
        Queue<Integer> queue = new LinkedList<>();
        
        // Start with courses that have no prerequisites
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 0) {
                queue.offer(i);
                dp[i] = time[i - 1];
            }
        }
        
        while (!queue.isEmpty()) {
            int course = queue.poll();
            
            for (int nextCourse : graph.get(course)) {
                dp[nextCourse] = Math.max(dp[nextCourse], dp[course] + time[nextCourse - 1]);
                inDegree[nextCourse]--;
                if (inDegree[nextCourse] == 0) {
                    queue.offer(nextCourse);
                }
            }
        }
        
        int result = 0;
        for (int i = 1; i <= n; i++) {
            result = Math.max(result, dp[i]);
        }
        
        return result;
    }
}
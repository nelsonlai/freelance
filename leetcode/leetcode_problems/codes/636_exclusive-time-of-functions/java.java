/**
 * Problem: Exclusive Time of Functions
 * Difficulty: Medium
 * Tags: array, string, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int[] exclusiveTime(int n, List<String> logs) {
        int[] result = new int[n];
        Stack<Integer> stack = new Stack<>();
        int prevTime = 0;
        
        for (String log : logs) {
            String[] parts = log.split(":");
            int funcId = Integer.parseInt(parts[0]);
            String status = parts[1];
            int time = Integer.parseInt(parts[2]);
            
            if (status.equals("start")) {
                if (!stack.isEmpty()) {
                    result[stack.peek()] += time - prevTime;
                }
                stack.push(funcId);
                prevTime = time;
            } else {
                result[stack.pop()] += time - prevTime + 1;
                prevTime = time + 1;
            }
        }
        
        return result;
    }
}
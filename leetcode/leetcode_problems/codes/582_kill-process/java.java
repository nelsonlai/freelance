/**
 * Problem: Kill Process
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public List<Integer> killProcess(List<Integer> pid, List<Integer> ppid, int kill) {
        Map<Integer, List<Integer>> children = new HashMap<>();
        for (int i = 0; i < ppid.size(); i++) {
            children.computeIfAbsent(ppid.get(i), k -> new ArrayList<>()).add(pid.get(i));
        }
        
        List<Integer> result = new ArrayList<>();
        Stack<Integer> stack = new Stack<>();
        stack.push(kill);
        
        while (!stack.isEmpty()) {
            int process = stack.pop();
            result.add(process);
            if (children.containsKey(process)) {
                stack.addAll(children.get(process));
            }
        }
        
        return result;
    }
}
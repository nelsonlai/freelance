/**
 * Problem: Smallest Greater Multiple Made of Two Digits
 * Difficulty: Medium
 * Tags: math, BFS
 * 
 * Approach: BFS to find smallest number > k made of only digit1 and digit2
 * Time Complexity: O(2^log(k)) in worst case
 * Space Complexity: O(2^log(k))
 */

import java.util.*;

class Solution {
    public int findInteger(int k, int digit1, int digit2) {
        Set<Integer> digits = new HashSet<>();
        if (digit1 != digit2) {
            digits.add(digit1);
            digits.add(digit2);
        } else {
            digits.add(digit1);
        }
        
        Queue<Long> queue = new LinkedList<>();
        queue.offer(0L);
        Set<Long> visited = new HashSet<>();
        visited.add(0L);
        
        while (!queue.isEmpty()) {
            long num = queue.poll();
            
            for (int digit : digits) {
                long nextNum = num * 10 + digit;
                if (nextNum > k) {
                    return (int) nextNum;
                }
                
                if (nextNum > 0 && !visited.contains(nextNum)) {
                    visited.add(nextNum);
                    queue.offer(nextNum);
                }
            }
        }
        
        return -1;
    }
}
/**
 * Problem: Dota2 Senate
 * Difficulty: Medium
 * Tags: string, greedy, queue
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String predictPartyVictory(String senate) {
        Queue<Integer> rQueue = new LinkedList<>();
        Queue<Integer> dQueue = new LinkedList<>();
        
        for (int i = 0; i < senate.length(); i++) {
            if (senate.charAt(i) == 'R') {
                rQueue.offer(i);
            } else {
                dQueue.offer(i);
            }
        }
        
        while (!rQueue.isEmpty() && !dQueue.isEmpty()) {
            int rIdx = rQueue.poll();
            int dIdx = dQueue.poll();
            
            if (rIdx < dIdx) {
                rQueue.offer(rIdx + senate.length());
            } else {
                dQueue.offer(dIdx + senate.length());
            }
        }
        
        return rQueue.isEmpty() ? "Dire" : "Radiant";
    }
}
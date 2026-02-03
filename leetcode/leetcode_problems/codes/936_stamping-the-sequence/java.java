/**
 * Problem: Stamping The Sequence
 * Difficulty: Hard
 * Tags: array, string, greedy, stack, queue
 * 
 * Approach: Work backwards - find positions where stamp can be placed, greedily stamp
 * Time Complexity: O(n * m) where n is target length, m is stamp length
 * Space Complexity: O(n) for result and visited array
 */

import java.util.*;

class Solution {
    public int[] movesToStamp(String stamp, String target) {
        int n = target.length(), m = stamp.length();
        char[] targetArr = target.toCharArray();
        List<Integer> result = new ArrayList<>();
        boolean[] visited = new boolean[n];
        
        boolean changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i <= n - m; i++) {
                if (!visited[i] && canStamp(stamp, targetArr, i)) {
                    visited[i] = true;
                    result.add(i);
                    changed = true;
                    for (int j = 0; j < m; j++) {
                        targetArr[i + j] = '?';
                    }
                }
            }
        }
        
        for (char c : targetArr) {
            if (c != '?') {
                return new int[0];
            }
        }
        
        Collections.reverse(result);
        return result.stream().mapToInt(i -> i).toArray();
    }
    
    private boolean canStamp(String stamp, char[] target, int pos) {
        boolean changed = false;
        for (int i = 0; i < stamp.length(); i++) {
            if (target[pos + i] == '?') {
                continue;
            }
            if (target[pos + i] != stamp.charAt(i)) {
                return false;
            }
            changed = true;
        }
        return changed;
    }
}
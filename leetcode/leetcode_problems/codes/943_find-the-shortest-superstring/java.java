/**
 * Problem: Find the Shortest Superstring
 * Difficulty: Hard
 * Tags: array, string, tree, dp
 * 
 * Approach: Traveling Salesman Problem with DP - find optimal order to concatenate words
 * Time Complexity: O(n^2 * (2^n + m)) where n is number of words, m is average word length
 * Space Complexity: O(n * 2^n) for DP table
 */

import java.util.*;

class Solution {
    public String shortestSuperstring(String[] words) {
        int n = words.length;
        
        // Calculate overlap between words
        int[][] overlap = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    for (int k = Math.min(words[i].length(), words[j].length()); k > 0; k--) {
                        if (words[i].endsWith(words[j].substring(0, k))) {
                            overlap[i][j] = k;
                            break;
                        }
                    }
                }
            }
        }
        
        // DP: dp[mask][i] = maximum overlap ending with word i using mask
        int[][] dp = new int[1 << n][n];
        int[][] parent = new int[1 << n][n];
        for (int[] row : parent) Arrays.fill(row, -1);
        
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) continue;
                int prevMask = mask ^ (1 << i);
                if (prevMask == 0) continue;
                for (int j = 0; j < n; j++) {
                    if ((prevMask & (1 << j)) != 0) {
                        int val = dp[prevMask][j] + overlap[j][i];
                        if (val > dp[mask][i]) {
                            dp[mask][i] = val;
                            parent[mask][i] = j;
                        }
                    }
                }
            }
        }
        
        // Find best ending word
        int last = 0;
        int maxVal = dp[(1 << n) - 1][0];
        for (int i = 1; i < n; i++) {
            if (dp[(1 << n) - 1][i] > maxVal) {
                maxVal = dp[(1 << n) - 1][i];
                last = i;
            }
        }
        
        // Reconstruct path
        List<Integer> path = new ArrayList<>();
        int mask = (1 << n) - 1;
        while (last != -1) {
            path.add(last);
            int newMask = mask ^ (1 << last);
            last = parent[mask][last];
            mask = newMask;
        }
        Collections.reverse(path);
        
        // Build result
        StringBuilder result = new StringBuilder(words[path.get(0)]);
        for (int i = 1; i < path.size(); i++) {
            int overlapLen = overlap[path.get(i-1)][path.get(i)];
            result.append(words[path.get(i)].substring(overlapLen));
        }
        
        return result.toString();
    }
}
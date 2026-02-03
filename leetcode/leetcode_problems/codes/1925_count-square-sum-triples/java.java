/**
 * Problem: Count Square Sum Triples
 * Difficulty: Easy
 * Tags: math
 * 
 * Approach: Check all triplets (a, b, c) where a^2 + b^2 = c^2
 * Time Complexity: O(n^2) where n is limit
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int countTriples(int n) {
        int count = 0;
        Set<Integer> squares = new HashSet<>();
        for (int i = 1; i <= n; i++) {
            squares.add(i * i);
        }
        
        for (int a = 1; a <= n; a++) {
            for (int b = a; b <= n; b++) {
                int cSquared = a * a + b * b;
                if (squares.contains(cSquared)) {
                    int c = (int) Math.sqrt(cSquared);
                    if (c <= n) {
                        count += (a == b) ? 1 : 2;
                    }
                }
            }
        }
        
        return count;
    }
}